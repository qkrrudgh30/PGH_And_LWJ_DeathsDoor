#include "PreCompile.h"
#include "GameEngineFBXAnimationRenderer.h"
#include "GameEngineMaterial.h"
#include "GameEngineVertexShader.h"

GameEngineFBXAnimationRenderer::GameEngineFBXAnimationRenderer() 
{
	
}

GameEngineFBXAnimationRenderer::~GameEngineFBXAnimationRenderer() 
{
	Animations.clear();
}


// _Index
// 애니메이션을 가진 fbx의 AnimationDatas(vector)의 index를 의미한다.

void FBXRendererAnimation::Init(int _Index)
{
	// GameENgineFBXAnimation의 행렬 정보가 완전해지는것은 
	// CalFbxExBoneFrameTransMatrix가 호출되고 난 후입니다.
	// 애니메이션의 행렬이 계산되는겁니다.
	Aniamtion->AnimationMatrixLoad(Mesh, _Index);
	FBXAnimationData = Aniamtion->GetAnimationData(_Index);
	Start = 0;
	End = FBXAnimationData->TimeEndCount;
	FrameTime = 0.02f;

}

void FBXRendererAnimation::Update()
{

}

void FBXRendererAnimation::Reset()
{
	Start = 0;
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, std::string _Material)
{
	GameEngineMaterial* Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material);
}

void GameEngineFBXAnimationRenderer::SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex /*= 0*/)
{
	GameEngineMaterial* Mat = GameEngineMaterial::Find(_Material);

	if (nullptr == Mat)
	{
		MsgBoxAssert("존재하지 않는 머티리얼 입니다.");
		return;
	}

	if (false == Mat->GetVertexShader()->IsStructuredBuffer("ArrAniMationMatrix"))
	{
		MsgBoxAssert("FBX 애니메이션 랜더러에 애니메이션이 불가능한 머티리얼을 세팅했습니다.");
		return;
	}

	GameEngineFBXRenderer::SetFBXMesh(_Name, _Material, _MeshIndex, _SubSetIndex);
}

void GameEngineFBXAnimationRenderer::CreateFBXAnimation(const std::string& _AnimationName
	, const std::string& _AnimationFBX, int _Index)
{
	// 본을 가진 fbx가 세팅되어 있는지 검사한다.
	if (nullptr == GetFBXMesh())
	{
		MsgBoxAssert("골격 FBX가 세팅되어 있지 않습니다.");
		return;
	}

	// 여기있는 함수를 외부에서 호출하면 됩니다.

	if (Animations.end() != Animations.find(_AnimationName))
	{
		MsgBoxAssertString("이미 존재하는 이름의 애니메이션입니다." + _AnimationName);
		return;
	}

	GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Find(_AnimationFBX);

	if (nullptr == Animation)
	{
		MsgBoxAssertString("GameEngineFBXAnimation이 존재하지 않습니다. " + _AnimationFBX);
		return;
	}

	std::shared_ptr<FBXRendererAnimation> NewAnimation = std::make_shared<FBXRendererAnimation>();

	NewAnimation->Mesh = GetFBXMesh();
	NewAnimation->Aniamtion = Animation;
	NewAnimation->ParentRenderer = this;

	NewAnimation->Init(_Index);

	// 이순간 애니메이션 프레임 행렬에 대한 계산이 이때 이뤄지는데.
	// 이건 느릴것이기 때문에 아마 추후 분명히.
	// 다른 툴이나 함수로 한번 로드하고 우리 포맷으로 저장하는 일을 해야할겁니다.

	RenderOptionInst.IsAnimation = 1;

	Animations.insert(std::make_pair(_AnimationName, NewAnimation));

	Animation;
}

void GameEngineFBXAnimationRenderer::ChangeAnimation(const std::string& _AnimationName)
{
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>>::iterator FindIter = Animations.find(_AnimationName);

	if (Animations.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다.");
		return;
	}

	CurAnimation = FindIter->second;
}