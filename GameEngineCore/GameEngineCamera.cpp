#include "PreCompile.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInstancing.h"
#include "GameEngineStructuredBuffer.h"
#include <GameEngineBase/GameEngineWindow.h>



GameEngineCamera::GameEngineCamera() 
{
	// 윈도우가 여러분들 생각하기 가장 쉬운 비율이라서 여기서 하는거고.
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::PersPective;
	Near = 0.1f;
	Far = 1000.0f;
	Fov = 60.0f;

	ViewPortDesc.TopLeftX = 0;
	ViewPortDesc.TopLeftY = 0;
	ViewPortDesc.Width = Size.x;
	ViewPortDesc.Height = Size.y;
	ViewPortDesc.MinDepth = 0.0f;
	ViewPortDesc.MaxDepth = 1.0f;
}

GameEngineCamera::~GameEngineCamera() 
{
}

bool ZSort(GameEngineRenderer* _Left, GameEngineRenderer* _Right)
{
	return _Left->GetTransform().GetWorldPosition().z > _Right->GetTransform().GetWorldPosition().z;
}

GameEngineInstancing* GameEngineCamera::GetInstancing(const std::string& _Name)
{
	GameEngineRenderingPipeLine* Instancing = GameEngineRenderingPipeLine::Find(_Name);
	return GetInstancing(Instancing);
}

void GameEngineCamera::Render(float _DeltaTime)
{
	CameraRenderTarget->Clear();
	CameraRenderTarget->Setting();

	// 순서적으로보면 레스터라이저 단계이지만 변경이 거의 없을거기 때문에.
	GameEngineDevice::GetContext()->RSSetViewports(1, &ViewPortDesc);

	// 랜더하기 전에 
	View.LookAtLH(
		GetActor()->GetTransform().GetLocalPosition(), 
		GetActor()->GetTransform().GetForwardVector(), 
		GetActor()->GetTransform().GetUpVector());

	switch (Mode)
	{
	case CAMERAPROJECTIONMODE::PersPective:
		Projection.PerspectiveFovLH(Fov, Size.x, Size.y, Near, Far);
		break;
	case CAMERAPROJECTIONMODE::Orthographic:
		Projection.OrthographicLH(Size.x, Size.y, Near, Far);
		break;
	default:
		break;
	}

	float4 WindowSize = GameEngineWindow::GetInst()->GetScale();

	// 인스턴싱정보를 초기화해요.
	{
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();
		for (; StartIter != EndIter; ++StartIter)
		{
			StartIter->second.DataInsert = 0;
		}
	}

	{
		// 랜더링 하면서 인스턴싱 데이터를 수집하고
		// 수집하면서 ++DataInsert
		// 랜더링 하기 전에
		for (std::pair<const int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
		{
			float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);

			std::list<GameEngineRenderer*>& RenderList = Group.second;
			RenderList.sort(ZSort);

			for (GameEngineRenderer* const Renderer : Group.second)
			{
				if (false == Renderer->IsUpdate())
				{
					continue;
				}

				Renderer->renderOption.DeltaTime = _DeltaTime;
				Renderer->renderOption.SumDeltaTime = _DeltaTime;
				Renderer->GetTransform().SetView(View);
				Renderer->GetTransform().SetProjection(Projection);
				Renderer->GetTransform().CalculateWorldViewProjection();

				// 인스턴싱 정보 수집
				Renderer->Render(ScaleTime);
			}
		}
	}

	// 다끝나면 인스턴싱을 랜더링
	{
		// 쉐이더 리소스 세팅이 다른애들이 있으면
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator StartIter = InstancingMap.begin();
		std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator EndIter = InstancingMap.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			if (GameEngineInstancing::MinInstancingCount > StartIter->second.Count)
			{
				continue;
			}

			GameEngineRenderingPipeLine* Pipe = StartIter->first;
			GameEngineInstancing& Instancing = StartIter->second;

			Instancing.InstancingBufferChangeData();
			Instancing.ShaderResources.AllResourcesSetting();
			Instancing.InstancingPipeLine->RenderingInstancing(Instancing.DataInsert, Instancing.Buffer);
		}
	}
}

void GameEngineCamera::SetCameraOrder(CAMERAORDER _Order)
{
	GetActor()->GetLevel()->PushCamera(this, _Order);
}

void GameEngineCamera::Start()
{
	CameraRenderTarget = GameEngineRenderTarget::Create();

	CameraRenderTarget->CreateRenderTargetTexture(GameEngineWindow::GetScale(), DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, float4::ZERO);

	CameraRenderTarget->SettingDepthTexture(GameEngineDevice::GetBackBuffer()->GetDepthTexture());
	// CameraRenderTarget->CreateDepthTexture()
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->RenderingOrder].push_back(_Renderer);
}


GameEngineInstancing* GameEngineCamera::GetInstancing(GameEngineRenderingPipeLine* _Pipe)
{
	if (nullptr == _Pipe)
	{
		MsgBoxAssert("존재하지 않는 파이프라인의 인스턴싱 데이터를 가져올수 없습니다.");
	}

	std::unordered_map<GameEngineRenderingPipeLine*, GameEngineInstancing>::iterator FindIter
		= InstancingMap.find(_Pipe);

	// 여태까지 인스턴싱을 켜거나 시도하지 않았던 녀석인데
	// 이제부터 인스턴싱을 할거니까 달라고 할수도 있죠?
	if (FindIter == InstancingMap.end())
	{
		GameEngineInstancing& Instancing = InstancingMap[_Pipe];
		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		// InstancingMap[_Pipe].
		Instancing.InstancingPipeLine = GameEngineRenderingPipeLine::Create();
		Instancing.InstancingPipeLine->Copy(_Pipe);
		Instancing.InstancingPipeLine->SetVertexShader(_Pipe->GetVertexShader()->GetInstancingShader());

		Instancing.ShaderResources.ResourcesCheck(Instancing.InstancingPipeLine);
		Instancing.ShaderResources.AllConstantBufferNew();

		Instancing.Size = Buffer->GetLayOutDesc()->InstancingSize;
		Instancing.Buffer = GameEngineInstancingBuffer::Create(GameEngineInstancing::StartInstancingCount, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(GameEngineInstancing::StartInstancingCount * Instancing.Size);
		Instancing.MaxDataCount = GameEngineInstancing::StartInstancingCount;

		// 엔진에서 책임진다.
		if (Instancing.ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
		{
			GameEngineStructuredBufferSetter* Setter = Instancing.ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

			if (nullptr != Setter->Res)
			{
				Setter->Resize(Instancing.MaxDataCount);
			}
			else
			{
				MsgBoxAssert("인스턴싱용 구조화 버퍼가 만들어지지 않았습니다.");
			}
		}



		FindIter = InstancingMap.find(_Pipe);
	}

	return &FindIter->second;
}


void GameEngineCamera::PushInstancing(GameEngineRenderingPipeLine* _Pipe, int Count)
{
	if (false == _Pipe->GetVertexShader()->IsInstancing())
	{
		MsgBoxAssert("인스턴싱이 불가능한 랜더러 입니다.")
	}

	// Camera->gameenginepipeline

	GameEngineInstancing& Instancing = InstancingMap[_Pipe];

	Instancing.Count += Count;

	if (GameEngineInstancing::MinInstancingCount <= Instancing.Count
		&& nullptr == Instancing.Buffer)
	{

		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		// InstancingMap[_Pipe].
		Instancing.InstancingPipeLine = GameEngineRenderingPipeLine::Create();
		Instancing.InstancingPipeLine->Copy(_Pipe);
		Instancing.InstancingPipeLine->SetVertexShader(_Pipe->GetVertexShader()->GetInstancingShader());

		// 스트럭처드 버퍼가 만들어졌을뿐
		Instancing.ShaderResources.ResourcesCheck(Instancing.InstancingPipeLine);
		Instancing.ShaderResources.AllConstantBufferNew();


		// 이 단계 다음에 어떤 상수버퍼를 가지고있고 그걸 세팅해야한다는 정보가 만들어진다.
		// 세팅을 해줘야.

		Instancing.Size = Buffer->GetLayOutDesc()->InstancingSize;
		Instancing.Buffer = GameEngineInstancingBuffer::Create(GameEngineInstancing::StartInstancingCount, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(GameEngineInstancing::StartInstancingCount * Instancing.Size);
	}
	else if(nullptr != Instancing.Buffer
		&& Instancing.Count > Instancing.Buffer->GetBufferCount())
	{
		//           105                           100
		GameEngineVertexBuffer* Buffer = _Pipe->GetVertexBuffer();
		int NextBufferSize = static_cast<int>(Instancing.Count * 1.5);
		Instancing.Buffer->BufferCreate(NextBufferSize, Buffer->GetLayOutDesc()->InstancingSize);
		Instancing.DataBuffer.resize(NextBufferSize * Instancing.Size);

		if (Instancing.ShaderResources.IsStructuredBuffer("AllInstancingTransformData"))
		{
			GameEngineStructuredBufferSetter* Setter = Instancing.ShaderResources.GetStructuredBuffer("AllInstancingTransformData");

			if (nullptr != Setter->Res)
			{
				Setter->Resize(Instancing.MaxDataCount);
			}
			else
			{
				MsgBoxAssert("인스턴싱용 구조화 버퍼가 만들어지지 않았습니다.");
			}
		}

	}
}

int GameEngineCamera::PushInstancingIndex(GameEngineRenderingPipeLine* _Pipe)
{
	int InsertCount = InstancingMap[_Pipe].DataInsert;
	return PushInstancingData(_Pipe, &InsertCount, sizeof(int));
}


int GameEngineCamera::PushInstancingData(GameEngineRenderingPipeLine* _Pipe, void* _DataPtr, int _Size)
{
	int DataOffset = InstancingMap[_Pipe].DataInsert * _Size;

	// 넣어주다가 사이즈가 오버되면 어떻하지?
	// 아니다.
	// PushInstancing에서 이미 버퍼는 충분한 사이즈만큼 늘어나 있어야 한다.

	char* DataPtr = &InstancingMap[_Pipe].DataBuffer[DataOffset];
	memcpy_s(DataPtr, InstancingMap[_Pipe].DataBuffer.size() - DataOffset, _DataPtr, _Size);
	DataOffset += _Size;

	int ResultIndex = InstancingMap[_Pipe].DataInsert;

	++InstancingMap[_Pipe].DataInsert;

	return ResultIndex;
}


void GameEngineCamera::Release(float _DelataTime)
{
	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			(*GroupStart)->ReleaseUpdate(_DelataTime);
			if (true == (*GroupStart)->IsDeath())
			{
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}

float4 GameEngineCamera::GetMouseScreenPosition() 
{
	POINT P;

	GetCursorPos(&P);

	ScreenToClient(GameEngineWindow::GetHWND(), &P);

	return { static_cast<float>(P.x), static_cast<float>(P.y) };
}

void GameEngineCamera::Update(float _DeltaTime) 
{
	float4 MousePos = GetMouseWorldPosition();
	MousePos.w = 0.0f;
	MouseDir = MousePos - PrevMouse;
	PrevMouse = MousePos;
}

// 뷰포트에 있는거죠?
float4 GameEngineCamera::GetMouseWorldPosition()
{
	float4 Pos = GetMouseScreenPosition();

	float4x4 ViewPort;
	ViewPort.ViewPort(Size.x, Size.y, 0, 0, 0, 1);
	ViewPort.Inverse();

	float4x4 ProjectionInvers = Projection.InverseReturn();

	Pos = Pos * ViewPort;
	Pos = Pos * ProjectionInvers;
	// 마우스는 뷰포트의 좌표다?

	return Pos;
}


float4 GameEngineCamera::GetMouseWorldPositionToActor()
{
	return GetTransform().GetWorldPosition() + GetMouseWorldPosition();
}

void GameEngineCamera::ChangeRenderingOrder(GameEngineRenderer* _Renderer, int _ChangeOrder)
{
	// 0번째에서 삭제되고
	AllRenderer_[_Renderer->GetRenderingOrder()].remove(_Renderer);

	_Renderer->RenderingOrder = _ChangeOrder;

	// 10000번째로 이동한다.
	AllRenderer_[_Renderer->GetRenderingOrder()].push_back(_Renderer);
}

void GameEngineCamera::OverRenderer(GameEngineCamera* _NextCamera) 
{
	if (nullptr == _NextCamera)
	{
		MsgBoxAssert("next camera is nullptr! fuck you");
		return;
	}

	std::map<int, std::list<GameEngineRenderer*>>::iterator StartGroupIter = AllRenderer_.begin();
	std::map<int, std::list<GameEngineRenderer*>>::iterator EndGroupIter = AllRenderer_.end();

	for (; StartGroupIter != EndGroupIter; ++StartGroupIter)
	{
		std::list<GameEngineRenderer*>& Group = StartGroupIter->second;
		std::list<GameEngineRenderer*>::iterator GroupStart = Group.begin();
		std::list<GameEngineRenderer*>::iterator GroupEnd = Group.end();

		for (; GroupStart != GroupEnd; )
		{
			GameEngineActor* Root = (*GroupStart)->GetRoot<GameEngineActor>();

			if (true == Root->IsLevelOver)
			{
				_NextCamera->AllRenderer_[StartGroupIter->first].push_back(*GroupStart);
				GroupStart = Group.erase(GroupStart);
			}
			else
			{
				++GroupStart;
			}

		}
	}
}