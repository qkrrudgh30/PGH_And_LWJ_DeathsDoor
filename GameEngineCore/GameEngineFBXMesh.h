#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>
#include "GameEngineVertexs.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"


// 지금설명하기 힘듬.
class FbxExIW
{
public:
	int Index;
	double Weight;
};


class FbxExMaterialSettingData
{
public:
	std::string Name;
	// 픽셀쉐이더에서 그냥 최종색상에 곱해주면 되는 색상.
	float4			 DifColor;
	float4			 AmbColor; // 빛
	float4			 SpcColor; // 빛
	float4			 EmvColor; // 빛
	float			 SpecularPower;		// 빛의 강도
	float			 TransparencyFactor;	// 빛의 강도
	float			 Shininess;			// 빛의 강도
	std::string DifTexturePath;	// 텍스처경로 
	std::string NorTexturePath; // 텍스처경로
	std::string SpcTexturePath; // 텍스처경로

	std::string DifTextureName;	// 텍스처경로 
	std::string NorTextureName; // 텍스처경로
	std::string SpcTextureName; // 텍스처경로

public:
	void Write(GameEngineFile* _File) const
	{
		_File->Write(Name);
		_File->Write(AmbColor); // 빛
		_File->Write(SpcColor); // 빛
		_File->Write(EmvColor); // 빛
		_File->Write(SpecularPower);
		_File->Write(TransparencyFactor);
		_File->Write(Shininess);
		_File->Write(DifTexturePath);	// 텍스처
		_File->Write(NorTexturePath); // 텍스처
		_File->Write(SpcTexturePath); // 텍스처
		_File->Write(DifTextureName);	// 텍스처
		_File->Write(NorTextureName); // 텍스처
		_File->Write(SpcTextureName); // 텍스처

	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(Name);
		_File->Read(AmbColor); // 빛
		_File->Read(SpcColor); // 빛
		_File->Read(EmvColor); // 빛
		_File->Read(SpecularPower);
		_File->Read(TransparencyFactor);
		_File->Read(Shininess);
		_File->Read(DifTexturePath);	// 텍스처
		_File->Read(NorTexturePath); // 텍스처
		_File->Read(SpcTexturePath); // 텍스처
		_File->Read(DifTextureName);	// 텍스처
		_File->Read(NorTextureName); // 텍스처
		_File->Read(SpcTextureName); // 텍스처
	}


public:
	FbxExMaterialSettingData() {}
	~FbxExMaterialSettingData() {}
};

struct FbxExMeshInfo
{
	std::string Name;
	fbxsdk::FbxMesh* Mesh;
	bool bTriangulated;

	unsigned __int64 UniqueId;
	int FaceNum;
	int VertexNum;
	int MaterialNum;

	// 애니메이션과 연결되는 매쉬인가?
	bool bIsSkeletalMesh;
	std::string SkeletonRoot;
	int SkeletonElemNum;

	bool bIsLodGroup;
	std::string LODGroupName;
	int LodLevel;
	int MorphNum;

	FbxExMeshInfo()
	{
		Name;
		UniqueId = 0;
		FaceNum = 0;
		VertexNum = 0;
		bTriangulated = false;
		MaterialNum = 0;
		bIsSkeletalMesh = false;
		SkeletonRoot;
		SkeletonElemNum = 0;
		bIsLodGroup = false;
		LODGroupName;
		LodLevel = -1;
		MorphNum = 0;
	}
};


struct FbxRenderUnit
{
public:
	int Index;
	int IsLodLv;
	bool IsLod;

	//       자신의 정보를 
	//       들고 있던 node
	//       의 mesh
	//       이매쉬에서  이점들을 빼냈다라고 보면 됩니다.
	//       얻어온 점들에 대한 모든 정보이고.
	//       만약 필요하다면 더 얻어야 할수도 있다.
	std::map<FbxMesh*, std::vector<GameEngineVertex>*> FbxVertexMap;

	//       애니메이션이 있다면 채워져 있을겁니다.
	std::map<FbxMesh*, std::map<int, std::vector<FbxExIW>>> MapWI;

	std::vector<GameEngineVertex> Vertexs;

	std::vector<std::vector<std::vector<unsigned int>>> Indexs;

	std::vector<std::vector<FbxExMaterialSettingData>> MaterialData;


	std::vector<GameEngineVertexBuffer*> GameEngineVertexBuffers;
	std::vector<std::vector<GameEngineIndexBuffer*>> GameEngineIndexBuffers;
	// std::vector<std::vector<std::shared_ptr<DirectMesh>>> m_Mesh;


	// FbxMeshSet(const FbxMeshSet& _Other) = delete;
	// FbxMeshSet(FbxMeshSet&& _Other) noexcept = delete;
	// FbxMeshSet& operator=(const FbxMeshSet& _Other) = delete;
	// FbxMeshSet& operator=(FbxMeshSet&& _Other) noexcept = delete;

	FbxRenderUnit() :
		IsLod(false),
		IsLodLv(-1)
	{
	}

	~FbxRenderUnit()
	{
		//for (size_t i = 0; i < GameEngineVertexBuffers.size(); i++)
		//{
		//	if (nullptr == GameEngineVertexBuffers[i])
		//	{
		//		continue;
		//	}
		//	delete GameEngineVertexBuffers[i];
		//	GameEngineVertexBuffers[i] = nullptr;
		//}

		//// 서브셋 때문에
		//for (size_t i = 0; i < GameEngineIndexBuffers.size(); i++)
		//{
		//	for (size_t j = 0; j < GameEngineIndexBuffers[i].size(); j++)
		//	{
		//		if (nullptr == GameEngineIndexBuffers[i][j])
		//		{
		//			continue;
		//		}
		//		delete GameEngineIndexBuffers[i][j];
		//		GameEngineIndexBuffers[i][j] = nullptr;
		//	}
		//}

	}
};


// 설명 :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineRes<GameEngineFBXMesh>
{
public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static GameEngineFBXMesh* Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineFBXMesh* Load(const std::string& _Path, const std::string& _Name);


protected:
	std::vector<FbxExMeshInfo> MeshInfos;
	std::vector<FbxRenderUnit> RenderUnitInfos;

private:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	void MeshLoad();

	void MeshNodeCheck();
	fbxsdk::FbxNode* RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode);
	fbxsdk::FbxNode* FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind);
	fbxsdk::FbxNode* RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind);

	void VertexBufferCheck();
	fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* Node);
	bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);
	void FbxRenderUnitMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnit* _RenderData);
	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
	std::string MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);

};

