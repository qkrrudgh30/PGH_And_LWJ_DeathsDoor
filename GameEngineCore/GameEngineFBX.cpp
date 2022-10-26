#include "PreCompile.h"
#include "GameEngineFBX.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineFBX::GameEngineFBX() 
	:
	Manager(nullptr),
	IOSetting(nullptr),
	Importer(nullptr),
	Scene(nullptr),
	RootNode(nullptr)
{
}




float4x4 GameEngineFBX::FbxMatTofloat4x4(const fbxsdk::FbxAMatrix& _BaseTrans)
{
	float4x4 Mat;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			Mat.Arr2D[y][x] = (float)_BaseTrans.Get(y, x);
		}
	}

	return Mat;
}

fbxsdk::FbxAMatrix GameEngineFBX::float4x4ToFbxAMatrix(const float4x4& _MATRIX)
{
	fbxsdk::FbxAMatrix mat;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mat.mData[y].mData[x] = _MATRIX.Arr2D[y][x];
		}
	}

	return mat;
}

float4 GameEngineFBX::FbxVecTofloat4(const fbxsdk::FbxVector4& _BaseVector)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseVector.mData[0];
	Vec.Arr1D[1] = (float)_BaseVector.mData[1];
	Vec.Arr1D[2] = (float)_BaseVector.mData[2];
	Vec.Arr1D[3] = (float)_BaseVector.mData[3];

	return Vec;

}

float4 GameEngineFBX::FbxVecToTransform(const fbxsdk::FbxVector4& _BaseVector)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseVector.mData[0];
	Vec.Arr1D[1] = (float)_BaseVector.mData[1];
	Vec.Arr1D[2] = -(float)_BaseVector.mData[2];
	Vec.Arr1D[3] = (float)_BaseVector.mData[3];
	return Vec;
}

float4 GameEngineFBX::FbxQuaternionTofloat4(const fbxsdk::FbxQuaternion& _BaseQ)
{
	float4 Vec;
	Vec.Arr1D[0] = (float)_BaseQ.mData[0];
	Vec.Arr1D[1] = (float)_BaseQ.mData[1];
	Vec.Arr1D[2] = -(float)_BaseQ.mData[2];
	Vec.Arr1D[3] = -(float)_BaseQ.mData[3];
	return Vec;
}


GameEngineFBX::~GameEngineFBX() 
{
	if (nullptr != Scene)
	{
		Scene->Destroy();
		Scene = nullptr;
	}
	if (nullptr != Importer)
	{
		Importer->Destroy();
		Importer = nullptr;
	}
	if (nullptr != IOSetting)
	{
		IOSetting->Destroy();
		IOSetting = nullptr;
	}
	if (nullptr != Manager)
	{
		Manager->Destroy();
		Manager = nullptr;
	}
}

// FBXSDK 
bool GameEngineFBX::CreateFBXSystemInitialize(const std::string& _Path)
{
	Manager = fbxsdk::FbxManager::Create();

	if (nullptr == Manager)
	{
		MsgBoxAssert("FBX 매니저 생성에 실패했습니다.");
		return false;
	}

	// FBX파일을 읽는 방법을 정의한다.
	// IO적인 측면에서 정의내리는 단계.
	// these defines are used for hierarchical properties names 구조도를 타고 읽겠다.
	IOSetting = fbxsdk::FbxIOSettings::Create(Manager, IOSROOT);

	// 실제 FBX파일의 정보를 우리에게 함수들로 제공해주는 클래스 Import
	Importer = fbxsdk::FbxImporter::Create(Manager, "");

	if (false == 
		Importer->Initialize(GameEngineString::AnsiToUTF8Return(_Path).c_str(), -1, IOSetting))
	{
		Importer->Destroy();
		IOSetting->Destroy();
		MsgBoxAssert("FBX 로드 이니셜라이즈 실패.");
		return false;
	}

	Scene = fbxsdk::FbxScene::Create(Manager, "");

	if (nullptr == Scene)
	{
		MsgBoxAssert("FBX 씬생성 실패.");
		return false;
	}

	// Scene의 내용을 채워준다.
	if (false == Importer->Import(Scene))
	{
		MsgBoxAssert("FBX 임포트 실패.");
		return false;
	}

	return true;
}


// 현재 FBX의 바라보는 방향을 구해오고
// RootNode를 구한다.
void GameEngineFBX::FBXConvertScene()
{
	AxisVector = { 0.0f, 0.0f, 0.0f, 1.0f };

	fbxsdk::FbxAxisSystem::EFrontVector FrontVector = (fbxsdk::FbxAxisSystem::EFrontVector)-fbxsdk::FbxAxisSystem::eParityOdd;
	fbxsdk::FbxAxisSystem::EUpVector UpVector = fbxsdk::FbxAxisSystem::eYAxis;
	fbxsdk::FbxAxisSystem::ECoordSystem CooreSystem = fbxsdk::FbxAxisSystem::ECoordSystem::eRightHanded;

	fbxsdk::FbxAxisSystem EngineAxisSystem(UpVector, FrontVector, CooreSystem);
	// fbxsdk::FbxAxisSystem EngineAxisSystem(fbxsdk::FbxAxisSystem::EPreDefinedAxisSystem::eDirectX);

	fbxsdk::FbxAxisSystem SourceAxisSystem = Scene->GetGlobalSettings().GetAxisSystem();

	// 이건 이제 컨버트 해줘야 하는겁니다.
	if (SourceAxisSystem != EngineAxisSystem)
	{
		// 먼저 루트를 지워.
		fbxsdk::FbxRootNodeUtility::RemoveAllFbxRoots(Scene);
		// 루트가 새롭게 만들어진다.
		EngineAxisSystem.ConvertScene(Scene);

		// 매쉬의 기존 매트릭스를 가져옵니다.
		fbxsdk::FbxAMatrix SourceMatrix;
		SourceAxisSystem.GetMatrix(SourceMatrix);

		fbxsdk::FbxAMatrix EngineMatrix;
		EngineAxisSystem.GetMatrix(EngineMatrix);

		ConvertMatrix = SourceMatrix.Inverse() * EngineMatrix;
	}

	int OriginUpSign = 0;
	int OriginFrontSign = 0;
	int EngineUpSign = 0;
	int EngineFrontSign = 0;

	fbxsdk::FbxAxisSystem::EFrontVector OriginFrontVector = SourceAxisSystem.GetFrontVector(OriginFrontSign);
	fbxsdk::FbxAxisSystem::EFrontVector EngineFrontVector = EngineAxisSystem.GetFrontVector(EngineFrontSign);

	fbxsdk::FbxAxisSystem::EUpVector OriginUpVector = SourceAxisSystem.GetUpVector(OriginUpSign);
	fbxsdk::FbxAxisSystem::EUpVector EngineUpVector = EngineAxisSystem.GetUpVector(EngineUpSign);

	fbxsdk::FbxAxisSystem::ECoordSystem  OriginCoordSystem = SourceAxisSystem.GetCoorSystem();
	fbxsdk::FbxAxisSystem::ECoordSystem  EngineCoordSystem = EngineAxisSystem.GetCoorSystem();

	if (OriginUpVector == EngineUpVector && OriginUpSign == EngineUpSign)
	{
		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == EngineUpVector && OriginUpSign != EngineUpSign)
	{
		if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
		{
			AxisVector.mData[1] += 180;
		}
		else
		{
			AxisVector.mData[0] += 180;
		}

		if (OriginFrontSign != EngineFrontSign && OriginCoordSystem == EngineCoordSystem)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += 180;
		}
	}
	else if (OriginUpVector == fbxsdk::FbxAxisSystem::EUpVector::eXAxis)
	{
		//origin up vector 가 x up vector 일때를 아직 만나보지를 못했다.

		AxisVector.mData[1] += OriginUpSign * 90;
	}
	else
	{
		AxisVector.mData[0] += OriginUpSign * 90;
		if (OriginUpSign != EngineFrontSign)
		{
			AxisVector.mData[static_cast<int>(OriginUpVector) - 1] += OriginUpSign * 180;
		}
	}

	JointMatrix.SetR(AxisVector);

	if (true == JointMatrix.IsIdentity())
	{
		JointMatrix = ConvertMatrix;
	}

	// 애니메이션도 행렬의 집합인데.
	Scene->GetAnimationEvaluator()->Reset();

	// 핵심인 루트노드를 얻어와야 한다.
	RootNode = Scene->GetRootNode();

	if (nullptr == RootNode)
	{
		MsgBoxAssert("루트노드생성에 실패했습니다.");
	}

	fbxsdk::FbxGeometryConverter Con(Manager);

	// 기본적으로 모든 FBX는 랜더링을 위한 삼각측량이 안되어있는 상태인데
	// 이 삼각측량 함수를 통해서 각 버텍스들을 우리가 사용할 수 있는 구조로 만들어준다.
	if (false == Con.Triangulate(Scene, true))
	{
		MsgBoxAssert("삼각화에 실패했습니다.");
	}

	return;
}

std::vector<FBXNodeInfo> GameEngineFBX::CheckAllNode()
{
	std::vector<FBXNodeInfo> AllNode;

	RecursiveAllNode(RootNode);

	return AllNode;
}

void GameEngineFBX::FBXInfoDebugFunction(fbxsdk::FbxNode* _RootNode)
{
	if (nullptr == _RootNode)
	{
		return;
	}

	std::string Name = _RootNode->GetName();
}

void GameEngineFBX::RecursiveAllNode(fbxsdk::FbxNode* _Node, std::function<void(fbxsdk::FbxNode*)> _Function /*= nullptr*/)
{
	// 노드의 정보들을 얻어올수가 있습니다.
	// fbxsdk::FbxNodeAttribute* Info = _Node->GetNodeAttribute();
	if (nullptr != _Function)
	{
		_Function(_Node);
	}

	//FBXNodeInfo& NewNodeInfo = _AllNode.emplace_back();
	//NewNodeInfo.Name = _Node->GetName();
	//NewNodeInfo.Node = _Node;

	int Count = _Node->GetChildCount();

	for (int i = 0; i < Count; i++)
	{
		fbxsdk::FbxNode* Node = _Node->GetChild(i);
		RecursiveAllNode(Node);
	}

}