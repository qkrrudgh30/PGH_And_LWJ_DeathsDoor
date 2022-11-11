#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>
#include "GameEngineVertexs.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineMesh.h"
#include "GameEngineStructuredBuffer.h"
#include <map>


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

// 사람
// 대검
struct FbxRenderUnitInfo
{
public:
	int VectorIndex;
	int IsLodLv;
	bool IsLod;

	float4 MinBoundBox;
	float4 MaxBoundBox;
	float4 BoundScaleBox;

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

	// 머리
	// 다리 
	// 몸통
	std::vector<std::vector<unsigned int>> Indexs;

	std::vector<FbxExMaterialSettingData> MaterialData;


	std::shared_ptr<GameEngineVertexBuffer> VertexBuffer;
	std::vector< std::shared_ptr<GameEngineIndexBuffer>> IndexBuffers;

	std::vector<std::shared_ptr<GameEngineMesh>> Meshs;

	FbxRenderUnitInfo() :
		IsLod(false),
		IsLodLv(-1),
		VertexBuffer(nullptr)
	{
	}

	~FbxRenderUnitInfo()
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



struct JointPos
{
	float4 Scale;
	float4 Rotation; // 쿼터니온.
	float4 Translation;

	float4 GlobalScale;
	float4 GlobalRotation;
	float4 GlobalTranslation;

	float4x4 Offset;
	float4x4 SotredOffset;
	float4x4 Local;
	float4x4 Global;

	float Length;
	float XSize;
	float YSize;
	float ZSize;

	void Write(GameEngineFile* _File) const
	{
		_File->Write(Scale);
		_File->Write(Rotation); // 쿼터니온.
		_File->Write(Translation);
		_File->Write(GlobalScale);
		_File->Write(GlobalRotation);
		_File->Write(GlobalTranslation);
		_File->Write(Offset);
		_File->Write(SotredOffset);
		_File->Write(Local);
		_File->Write(Global);
		_File->Write(Length);
		_File->Write(XSize);
		_File->Write(YSize);
		_File->Write(ZSize);
	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(Scale);
		_File->Read(Rotation); // 쿼터니온.
		_File->Read(Translation);
		_File->Read(GlobalScale);
		_File->Read(GlobalRotation);
		_File->Read(GlobalTranslation);
		_File->Read(Offset);
		_File->Read(SotredOffset);
		_File->Read(Local);
		_File->Read(Global);
		_File->Read(Length);
		_File->Read(XSize);
		_File->Read(YSize);
		_File->Read(ZSize);
	}

	void BuildMatrix()
	{
		Global = float4x4::Transformation(GlobalScale, GlobalRotation, GlobalTranslation);
		Local = float4x4::Transformation(Scale, Rotation, Translation);
		Offset = Global.InverseReturn();
	}

	void SetScale(fbxsdk::FbxVector4& scale)
	{
		Scale.x = (float)scale.mData[0];
		Scale.y = (float)scale.mData[1];
		Scale.z = (float)scale.mData[2];
		Scale.w = 0.0f;
	}

	void SetRotation(fbxsdk::FbxQuaternion& quaternion)
	{
		Rotation.x = (float)quaternion.mData[0];
		Rotation.y = (float)quaternion.mData[1];
		Rotation.z = -(float)quaternion.mData[2];
		Rotation.w = -(float)quaternion.mData[3];
	}

	void SetTranslation(fbxsdk::FbxVector4& translation)
	{
		Translation.x = (float)translation.mData[0];
		Translation.y = (float)translation.mData[1];
		Translation.z = -(float)translation.mData[2];
		Translation.w = 0.0f;
	}

	void SetGlobalScale(fbxsdk::FbxVector4& scale)
	{
		GlobalScale.x = (float)scale.mData[0];
		GlobalScale.y = (float)scale.mData[1];
		GlobalScale.z = (float)scale.mData[2];
		GlobalScale.w = 0.0f;
	}

	void SetGlobalRotation(fbxsdk::FbxQuaternion& quaternion)
	{
		GlobalRotation.x = (float)quaternion.mData[0];
		GlobalRotation.y = (float)quaternion.mData[1];
		GlobalRotation.z = -(float)quaternion.mData[2];
		GlobalRotation.w = -(float)quaternion.mData[3];
	}

	void SetGlobalTranslation(fbxsdk::FbxVector4& translation)
	{
		GlobalTranslation.x = (float)translation.mData[0];
		GlobalTranslation.y = (float)translation.mData[1];
		GlobalTranslation.z = -(float)translation.mData[2];
		GlobalTranslation.w = 0.0f;
	}

	void SetFromMatrix(const float4x4& InMatrix)
	{
		float4x4 M = InMatrix;

		// Get the 3D scale from the matrix
		Scale = M.ExtractScaling();
		Scale.w = 0.0;

		// If there is negative scaling going on, we handle that here
		if (InMatrix.Determinant() < 0.f)
		{
			// Assume it is along X and modify transform accordingly. 
			// It doesn't actually matter which axis we choose, the 'appearance' will be the same
			float4 FloatMinus1_111(-1.f, 1.f, 1.f, 1.f);
			Scale *= FloatMinus1_111;// VectorMultiply(Scale, FloatMinus1_111);
			float4 XAxis = -float4(M.Arr2D[0][0], M.Arr2D[0][1], M.Arr2D[0][2], 0.0f);
			M.Arr2D[0][0] = XAxis.x;
			M.Arr2D[0][1] = XAxis.w;
			M.Arr2D[0][2] = XAxis.z;
		}

		Rotation = float4::MatrixToQuaternion(M);
		Translation = float4(InMatrix.Arr2D[3][0], InMatrix.Arr2D[3][1], InMatrix.Arr2D[3][2], 0.0f);

		// Normalize rotation
		__m128 Temp1 = _mm_mul_ps(Rotation.DirectVector, Rotation.DirectVector);
		__m128 Temp2 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(1, 0, 3, 2));	// (Z,W,X,Y).
		Temp1 = _mm_add_ps(Temp1, Temp2);								// (X*X + Z*Z, Y*Y + W*W, Z*Z + X*X, W*W + Y*Y)
		Temp2 = _mm_shuffle_ps(Temp1, Temp1, _MM_SHUFFLE(0, 3, 2, 1));
		__m128 SquareSum = _mm_add_ps(Temp1, Temp2);
		const __m128 NonZeroMask = _mm_cmpge_ps(SquareSum, _mm_setr_ps(1.e-8f, 1.e-8f, 1.e-8f, 1.e-8f));
		const __m128 OneHalf = _mm_setr_ps(0.5f, 0.5f, 0.5f, 0.5f);
		const __m128 VecDivBy2 = _mm_mul_ps(SquareSum, OneHalf);

		// Initial estimate
		const __m128 x0 = _mm_rsqrt_ps(SquareSum);

		// First iteration
		__m128 x1 = _mm_mul_ps(x0, x0);
		x1 = _mm_sub_ps(OneHalf, _mm_mul_ps(VecDivBy2, x1));
		x1 = _mm_add_ps(_mm_mul_ps(x0, x1), x0);

		// Second iteration
		__m128 x2 = _mm_mul_ps(x1, x1);
		x2 = _mm_sub_ps(OneHalf, _mm_mul_ps(VecDivBy2, x2));
		const __m128 InvLength = _mm_add_ps(_mm_mul_ps(x1, x2), x1);

		const __m128 NormalizedVector = _mm_mul_ps(InvLength, Rotation.DirectVector);
		__m128 DefaultValue = _mm_setr_ps(0.0f, 0.0f, 0.0f, 1.0f);
		Rotation.DirectVector = _mm_xor_ps(DefaultValue, _mm_and_ps(NonZeroMask, _mm_xor_ps(NormalizedVector, DefaultValue)));
	}

	void ToMatrixInternal(__m128& OutDiagonals, __m128& OutAdds, __m128& OutSubtracts) const
	{
		const __m128 RotationX2Y2Z2 = _mm_add_ps(Rotation.DirectVector, Rotation.DirectVector);	// x2, y2, z2
		const __m128 RotationXX2YY2ZZ2 = _mm_mul_ps(RotationX2Y2Z2, Rotation.DirectVector);	// xx2, yy2, zz2		

		// The diagonal terms of the rotation matrix are:
		//   (1 - (yy2 + zz2)) * scale
		//   (1 - (xx2 + zz2)) * scale
		//   (1 - (xx2 + yy2)) * scale
		const __m128 yy2_xx2_xx2 = _mm_shuffle_ps(RotationXX2YY2ZZ2, RotationXX2YY2ZZ2, _MM_SHUFFLE(0, 0, 0, 1));
		const __m128 zz2_zz2_yy2 = _mm_shuffle_ps(RotationXX2YY2ZZ2, RotationXX2YY2ZZ2, _MM_SHUFFLE(0, 1, 2, 2));
		const __m128 DiagonalSum = _mm_add_ps(yy2_xx2_xx2, zz2_zz2_yy2);
		const __m128 Diagonals = _mm_sub_ps(float4::ONE.DirectVector, DiagonalSum);
		OutDiagonals = _mm_mul_ps(Diagonals, Scale.DirectVector);

		// Grouping the non-diagonal elements in the rotation block by operations:
		//    ((x*y2,y*z2,x*z2) + (w*z2,w*x2,w*y2)) * scale.xyz and
		//    ((x*y2,y*z2,x*z2) - (w*z2,w*x2,w*y2)) * scale.yxz
		// Rearranging so the LHS and RHS are in the same order as for +
		//    ((x*y2,y*z2,x*z2) - (w*z2,w*x2,w*y2)) * scale.yxz

		// RotBase = x*y2, y*z2, x*z2
		// RotOffset = w*z2, w*x2, w*y2
		const __m128 x_y_x = _mm_shuffle_ps(Rotation.DirectVector, Rotation.DirectVector, _MM_SHUFFLE(0, 0, 1, 0)); // 1, 2, 2, 0
		const __m128 y2_z2_z2 = _mm_shuffle_ps(RotationX2Y2Z2, RotationX2Y2Z2, _MM_SHUFFLE(0, 2, 2, 1));
		const __m128 RotBase = _mm_mul_ps(x_y_x, y2_z2_z2);

		const __m128 w_w_w = _mm_shuffle_ps(Rotation.DirectVector, Rotation.DirectVector, _MM_SHUFFLE(3, 3, 3, 3));
		const __m128 z2_x2_y2 = _mm_shuffle_ps(RotationX2Y2Z2, RotationX2Y2Z2, _MM_SHUFFLE(0, 1, 0, 2));
		const __m128 RotOffset = _mm_mul_ps(w_w_w, z2_x2_y2);

		// Adds = (RotBase + RotOffset)*Scale3D :  (x*y2 + w*z2) * Scale3D.X , (y*z2 + w*x2) * Scale3D.Y, (x*z2 + w*y2) * Scale3D.Z
		// Subtracts = (RotBase - RotOffset)*Scale3DYZX :  (x*y2 - w*z2) * Scale3D.Y , (y*z2 - w*x2) * Scale3D.Z, (x*z2 - w*y2) * Scale3D.X
		const __m128 Adds = _mm_add_ps(RotBase, RotOffset);
		OutAdds = _mm_mul_ps(Adds, Scale.DirectVector);
		const __m128 Scale3DYZXW = _mm_shuffle_ps(Scale.DirectVector, Scale.DirectVector, _MM_SHUFFLE(3, 0, 2, 1));
		const __m128 Subtracts = _mm_sub_ps(RotBase, RotOffset);
		OutSubtracts = _mm_mul_ps(Subtracts, Scale3DYZXW);
	}

	float4x4 ToMatrixWithScale()
	{
		float4x4 OutMatrix;
		__m128 DiagonalsXYZ;
		__m128 Adds;
		__m128 Subtracts;

		ToMatrixInternal(DiagonalsXYZ, Adds, Subtracts);
		union { __m128 v; __m128i i; } tmp;
		tmp.i = _mm_setr_epi32((unsigned int)0xffffffff, (unsigned int)0xffffffff, (unsigned int)0xffffffff, (unsigned int)0x00000000);
		const __m128 DiagonalsXYZ_W0 = _mm_and_ps(DiagonalsXYZ, tmp.v);

		// OutMatrix.M[0][0] = (1.0f - (yy2 + zz2)) * Scale.X;    // Diagonal.X
		// OutMatrix.M[0][1] = (xy2 + wz2) * Scale.X;             // Adds.X
		// OutMatrix.M[0][2] = (xz2 - wy2) * Scale.X;             // Subtracts.Z
		// OutMatrix.M[0][3] = 0.0f;                              // DiagonalsXYZ_W0.W
		const __m128 AddX_DC_DiagX_DC = _mm_shuffle_ps(Adds, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 0, 0, 0));
		const __m128 SubZ_DC_DiagW_DC = _mm_shuffle_ps(Subtracts, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 3, 0, 2));
		const __m128 Row0 = _mm_shuffle_ps(AddX_DC_DiagX_DC, SubZ_DC_DiagW_DC, _MM_SHUFFLE(2, 0, 0, 2));

		// OutMatrix.M[1][0] = (xy2 - wz2) * Scale.Y;             // Subtracts.X
		// OutMatrix.M[1][1] = (1.0f - (xx2 + zz2)) * Scale.Y;    // Diagonal.Y
		// OutMatrix.M[1][2] = (yz2 + wx2) * Scale.Y;             // Adds.Y
		// OutMatrix.M[1][3] = 0.0f;                            // DiagonalsXYZ_W0.W
		const __m128 SubX_DC_DiagY_DC = _mm_shuffle_ps(Subtracts, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 1, 0, 0));
		const __m128 AddY_DC_DiagW_DC = _mm_shuffle_ps(Adds, DiagonalsXYZ_W0, _MM_SHUFFLE(0, 3, 0, 1));
		const __m128 Row1 = _mm_shuffle_ps(SubX_DC_DiagY_DC, AddY_DC_DiagW_DC, _MM_SHUFFLE(2, 0, 2, 0));

		// OutMatrix.M[2][0] = (xz2 + wy2) * Scale.Z;             // Adds.Z
		// OutMatrix.M[2][1] = (yz2 - wx2) * Scale.Z;             // Subtracts.Y
		// OutMatrix.M[2][2] = (1.0f - (xx2 + yy2)) * Scale.Z;    // Diagonals.Z
		// OutMatrix.M[2][3] = 0.0f;                              // DiagonalsXYZ_W0.W
		const __m128 AddZ_DC_SubY_DC = _mm_shuffle_ps(Adds, Subtracts, _MM_SHUFFLE(0, 1, 0, 2));
		const __m128 Row2 = _mm_shuffle_ps(AddZ_DC_SubY_DC, DiagonalsXYZ_W0, _MM_SHUFFLE(3, 2, 2, 0));

		_mm_store_ps(&(OutMatrix.Arr2D[0][0]), Row0);
		_mm_store_ps(&(OutMatrix.Arr2D[1][0]), Row1);
		_mm_store_ps(&(OutMatrix.Arr2D[2][0]), Row2);

		// OutMatrix.M[3][0] = Translation.X;
		// OutMatrix.M[3][1] = Translation.Y;
		// OutMatrix.M[3][2] = Translation.Z;
		// OutMatrix.M[3][3] = 1.0f;
		__m128 Temp1 = _mm_movehl_ps(float4::ONE.DirectVector, Translation.DirectVector);

		const __m128 Row3 = _mm_shuffle_ps(Translation.DirectVector, Temp1, _MM_SHUFFLE(3, 0, 1, 0));
		_mm_store_ps(&(OutMatrix.Arr2D[3][0]), Row3);

		return OutMatrix;
	}

	void Reset()
	{
		Scale = float4::ONE;
		Rotation = float4::ZERO;
		Translation = float4::ZERO;

		Offset.Identity();
	}

	JointPos()
	{
		Scale = float4::ONE;
		Rotation = float4::ZERO;
		Translation = float4::ZERO;

		Offset.Identity();
	}
};


class FbxClusterData
{
public:
	fbxsdk::FbxCluster* Cluster;
	fbxsdk::FbxMesh* Mesh;
	std::string LinkName;

public:
	FbxClusterData()
		: Mesh(nullptr)
		, Cluster(nullptr)
		, LinkName("")
	{

	}
};



struct Bone
{
	std::string Name;

	unsigned int Flags;
	int			 NumChildren;
	int			 Index;
	int			 ParentIndex;
	JointPos	 BonePos;

	Bone()
	{
		Name = "";
		Flags = 0;
		NumChildren = 0;
		Index = -1;
		ParentIndex = 0;
		BonePos.Reset();
	}

	void Write(GameEngineFile* _File) const
	{
		_File->Write(Name);
		_File->Write(Flags);
		_File->Write(NumChildren);
		_File->Write(Index);
		_File->Write(ParentIndex);
		_File->Write(BonePos);
	}

	void Read(GameEngineFile* _File)
	{
		_File->Read(Name);
		_File->Read(Flags);
		_File->Read(NumChildren);
		_File->Read(Index);
		_File->Read(ParentIndex);
		_File->Read(BonePos);
	}
};


class GameEngineMesh;
class GameEngineFBXAnimation;
// 설명 :
class GameEngineFBXMesh : public GameEngineFBX, public GameEngineRes<GameEngineFBXMesh>
{
	friend GameEngineFBXAnimation;

public:
	// constrcuter destructer
	GameEngineFBXMesh();
	~GameEngineFBXMesh();

	// delete Function
	GameEngineFBXMesh(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh(GameEngineFBXMesh&& _Other) noexcept = delete;
	GameEngineFBXMesh& operator=(const GameEngineFBXMesh& _Other) = delete;
	GameEngineFBXMesh& operator=(GameEngineFBXMesh&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFBXMesh> Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static std::shared_ptr<GameEngineFBXMesh> Load(const std::string& _Path, const std::string& _Name);

	std::shared_ptr<GameEngineMesh> GetGameEngineMesh(size_t _MeshIndex, size_t _SubIndex);

	const FbxExMaterialSettingData& GetMaterialSettingData(size_t _MeshIndex, size_t _SubIndex);

	size_t GetRenderUnitCount()
	{
		return RenderUnitInfos.size();
	}

	size_t GetSubSetCount(size_t _RenderUnitIndex)
	{
		return RenderUnitInfos[_RenderUnitIndex].Indexs.size();
	}

	size_t GetMeshInfosCount()
	{
		return MeshInfos.size();
	}

	size_t GetBoneCount(size_t _Index)
	{
		return AllBones[_Index].size();
	}


	// Bone 찾아주는 함수
	Bone* FindBone(size_t MeshIndex, size_t _BoneIndex);
	Bone* FindBone(size_t MeshIndex, std::string _Name);

	std::shared_ptr<GameEngineStructuredBuffer> GetAnimationStructuredBuffer(size_t _Index);

protected:
	// 매쉬가 있어
	std::vector<FbxExMeshInfo> MeshInfos;

	// 매쉬의 버텍스가 이렇이렇게 되어있어.
	std::vector<FbxRenderUnitInfo> RenderUnitInfos;

	std::vector<std::vector<Bone>> AllBones; // 본정보체
	std::vector<std::shared_ptr<GameEngineStructuredBuffer>> AllBoneStructuredBuffers; // 본정보체

	std::vector<std::map<std::string, Bone*>> AllFindMap;
	std::vector<std::vector<FbxClusterData>> ClusterData;

private:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	void MeshLoad();

	// 매쉬 정보 획득
	void MeshNodeCheck();
	fbxsdk::FbxNode* RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode);
	fbxsdk::FbxNode* FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind);
	fbxsdk::FbxNode* RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind);

	// 버텍스 정보
	void VertexBufferCheck();
	fbxsdk::FbxAMatrix ComputeTotalMatrix(fbxsdk::FbxNode* Node);
	bool IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix);
	void FbxRenderUnitInfoMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnitInfo* _RenderData);
	float4 MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName);
	float MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);
	std::string MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName);

	void LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index);
	void LoadUV(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int VertexCount, int _Index);
	void LoadUVInformation(fbxsdk::FbxMesh* pMesh, std::vector<GameEngineVertex>& _ArrVtx);

	// Bone 정보
	bool ImportBone();
	bool RetrievePoseFromBindPose(fbxsdk::FbxScene* pScene, const std::vector<fbxsdk::FbxNode*>& NodeArray, fbxsdk::FbxArray<fbxsdk::FbxPose*>& PoseArray);
	void BuildSkeletonSystem(fbxsdk::FbxScene* pScene, std::vector<fbxsdk::FbxCluster*>& ClusterArray, std::vector<fbxsdk::FbxNode*>& OutSortedLinks);
	fbxsdk::FbxNode* GetRootSkeleton(fbxsdk::FbxScene* pScene, fbxsdk::FbxNode* Link);
	void RecursiveBuildSkeleton(fbxsdk::FbxNode* Link, std::vector<fbxsdk::FbxNode*>& OutSortedLinks);
	bool IsNull(fbxsdk::FbxNode* Link);
	bool IsBone(fbxsdk::FbxNode* Link);

	// 애니메이션 버텍스 정보
	void LoadSkinAndCluster();
	void ImportCluster();
	void LoadAnimationVertexData(FbxRenderUnitInfo* _DrawData, const std::vector<FbxClusterData>& vecClusterData);
	void DrawSetWeightAndIndexSetting(FbxRenderUnitInfo* _DrawSet, fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxCluster* _Cluster, int _BoneIndex);
	void CalAnimationVertexData(FbxRenderUnitInfo& _DrawSet);

	// 스트럭처드 버퍼 생성로직.
	void CreateGameEngineStructuredBuffer();

};

