#include "PreCompile.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXMesh::GameEngineFBXMesh()
{
}

GameEngineFBXMesh::~GameEngineFBXMesh()
{
	//for (size_t i = 0; i < AllBoneStructuredBuffers.size(); i++)
	//{
	//	delete AllBoneStructuredBuffers[i];
	//}

	AllBoneStructuredBuffers.clear();
}



std::shared_ptr<GameEngineFBXMesh> GameEngineFBXMesh::Load(const std::string& _Path, const std::string& _Name)
{
	std::shared_ptr<GameEngineFBXMesh> NewRes = CreateResName(_Name);
	NewRes->SetPath(_Path);
	NewRes->LoadMesh(_Path, _Name);
	return NewRes;
}

void GameEngineFBXMesh::LoadMesh(const std::string& _Path, const std::string& _Name)
{
	FBXInit(_Path);
	// 버텍스 정보를 가진 노드를 조사한다.
	MeshLoad();
	// Bone을 조사한다.
}

void GameEngineFBXMesh::MeshLoad()
{
	MeshNodeCheck();

	VertexBufferCheck();

	ImportBone();

	CreateGameEngineStructuredBuffer();

	AllBones; // 본정보체
	AllFindMap;
	RenderUnitInfos;
	MeshInfos;
}

Bone* GameEngineFBXMesh::FindBone(size_t MeshIndex, size_t _BoneIndex)
{
	// m_vecRefBones 벡터로 들고 있는애

	if (AllBones.size() <= MeshIndex)
	{
		MsgBoxAssert("존재하지 않는 매쉬의 본을 가져오려고 했습니다.");
		return nullptr;
	}

	if (AllBones[MeshIndex].size() <= _BoneIndex)
	{
		MsgBoxAssert("존재하는 본의 범위를 넘겼습니다.");
		return nullptr;
	}

	return &AllBones[MeshIndex][_BoneIndex];

}
Bone* GameEngineFBXMesh::FindBone(size_t MeshIndex, std::string _Name)
{
	if (0 == AllBones.size())
	{
		ImportBone();
	}

	if (0 == AllBones[MeshIndex].size())
	{
		return nullptr;
	}

	if (0 == AllFindMap[MeshIndex].size())
	{
		MsgBoxAssert("본을 찾는 작업을 하지 않은 매쉬입니다");
	}

	if (AllFindMap[MeshIndex].end() == AllFindMap[MeshIndex].find(_Name))
	{
		return nullptr;
	}

	return AllFindMap[MeshIndex][_Name];

}

bool GameEngineFBXMesh::IsOddNegativeScale(const fbxsdk::FbxAMatrix& TotalMatrix)
{
	fbxsdk::FbxVector4 Scale = TotalMatrix.GetS();
	int NegativeNum = 0;

	if (Scale[0] < 0) NegativeNum++;
	if (Scale[1] < 0) NegativeNum++;
	if (Scale[2] < 0) NegativeNum++;

	return NegativeNum == 1 || NegativeNum == 3;
}

// 이 매쉬 노드의 기본 행렬 정보를 얻어오는것
fbxsdk::FbxAMatrix GameEngineFBXMesh::ComputeTotalMatrix(fbxsdk::FbxNode* Node)
{
	fbxsdk::FbxAMatrix Geometry;
	fbxsdk::FbxVector4 Translation, Rotation, Scaling;
	Translation = Node->GetGeometricTranslation(fbxsdk::FbxNode::eSourcePivot);
	Rotation = Node->GetGeometricRotation(fbxsdk::FbxNode::eSourcePivot);
	Scaling = Node->GetGeometricScaling(fbxsdk::FbxNode::eSourcePivot);
	Geometry.SetT(Translation);
	Geometry.SetR(Rotation);
	Geometry.SetS(Scaling);

	fbxsdk::FbxAMatrix& GlobalTransform = Scene->GetAnimationEvaluator()->GetNodeGlobalTransform(Node);
	return GlobalTransform * Geometry;
}



float4 GameEngineFBXMesh::MaterialColor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _ColorName, const char* _FactorName)
{
	FbxDouble3 vResult(0, 0, 0);
	double dFactor = 0;
	FbxProperty ColorPro = pMtrl->FindProperty(_ColorName);
	FbxProperty FactorPro = pMtrl->FindProperty(_FactorName);

	if (true == ColorPro.IsValid() && true == FactorPro.IsValid())
	{
		vResult = ColorPro.Get<FbxDouble3>();
		dFactor = FactorPro.Get<FbxDouble>();

		if (dFactor != 1)
		{
			vResult[0] *= dFactor;
			vResult[1] *= dFactor;
			vResult[2] *= dFactor;
		}
	}

	return float4((float)vResult[0], (float)vResult[1], (float)vResult[2]);
}


float GameEngineFBXMesh::MaterialFactor(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName)
{
	double dFactor = 0;
	FbxProperty FactorPro = pMtrl->FindProperty(_FactorName);

	if (true == FactorPro.IsValid())
	{
		dFactor = FactorPro.Get<FbxDouble>();
	}

	return (float)dFactor;
}



std::string GameEngineFBXMesh::MaterialTex(fbxsdk::FbxSurfaceMaterial* pMtrl, const char* _FactorName)
{
	fbxsdk::FbxProperty TexturePro = pMtrl->FindProperty(_FactorName);

	std::string Str;
	if (true == TexturePro.IsValid())
	{
		fbxsdk::FbxObject* pFileTex = TexturePro.GetFbxObject();

		int iTexCount = TexturePro.GetSrcObjectCount<FbxFileTexture>();

		if (iTexCount > 0)
		{
			FbxFileTexture* pFileTex = TexturePro.GetSrcObject<FbxFileTexture>(0);

			if (nullptr != pFileTex)
			{
				Str = pFileTex->GetFileName();
			}
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}

	return Str;
}


void GameEngineFBXMesh::FbxRenderUnitInfoMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnitInfo* _RenderData)
{
	int MtrlCount = _Node->GetMaterialCount();

	if (MtrlCount > 0)
	{
		std::vector<FbxExMaterialSettingData>& MatrialSet = _RenderData->MaterialData;

		for (int i = 0; i < MtrlCount; i++)
		{
			fbxsdk::FbxSurfaceMaterial* pMtrl = _Node->GetMaterial(i);

			if (nullptr == pMtrl)
			{
				MsgBoxAssert("if (nullptr == pMtrl) 메테리얼 정보가 존재하지 않습니다");
				continue;
			}

			FbxExMaterialSettingData& MatData = MatrialSet.emplace_back();
			MatData.Name = pMtrl->GetName();
			// fbxsdk::FbxSurfaceMaterial::sDiffuse = 0x00007ff61122bf40 "DiffuseColor"
			// fbxsdk::FbxSurfaceMaterial::sDiffuseFactor = 0x00007ff61122bf50 "DiffuseFactor"
			MatData.DifColor = MaterialColor(pMtrl, "DiffuseColor", "DiffuseFactor");
			MatData.AmbColor = MaterialColor(pMtrl, "AmbientColor", "AmbientFactor");
			MatData.SpcColor = MaterialColor(pMtrl, "SpecularColor", "SpecularFactor");
			MatData.EmvColor = MaterialColor(pMtrl, "EmissiveColor", "EmissiveFactor");
			MatData.SpecularPower = MaterialFactor(pMtrl, "SpecularFactor");
			// fbxsdk::FbxSurfaceMaterial::sShininess = 0x00007ff61122bf80 "ShininessExponent"
			// fbxsdk::FbxSurfaceMaterial::sTransparencyFactor = 0x00007ff61122bfd8 "TransparencyFactor"
			MatData.Shininess = MaterialFactor(pMtrl, "ShininessExponent");
			MatData.TransparencyFactor = MaterialFactor(pMtrl, "TransparencyFactor");

			MatData.DifTexturePath = MaterialTex(pMtrl, "DiffuseColor");
			MatData.NorTexturePath = MaterialTex(pMtrl, "NormalMap");
			MatData.SpcTexturePath = MaterialTex(pMtrl, "SpecularColor");

			MatData.DifTextureName = GameEnginePath::GetFileName(MatData.DifTexturePath);
			MatData.NorTextureName = GameEnginePath::GetFileName(MatData.NorTexturePath);
			MatData.SpcTextureName = GameEnginePath::GetFileName(MatData.SpcTexturePath);
		}

	}
	else {
		MsgBoxAssert("매쉬는 존재하지만 재질은 존재하지 않습니다.");
	}

}


void GameEngineFBXMesh::LoadBinormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementBinormalCount();

	if (0 == iCount)
	{
		return;

	}

	FbxGeometryElementBinormal* pElement = _Mesh->GetElementBinormal();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}

	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
		}
	}

	FbxVector4 BiNormal = pElement->GetDirectArray().GetAt(iDataIndex);

	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	BiNormal = conversionMeshMatrix.MultT(BiNormal);


	_ArrVtx[_Index].BINORMAL.x = (float)BiNormal.mData[0];
	_ArrVtx[_Index].BINORMAL.y = (float)BiNormal.mData[1];
	_ArrVtx[_Index].BINORMAL.z = -(float)BiNormal.mData[2];
	_ArrVtx[_Index].BINORMAL.w = (float)BiNormal.mData[3];
	_ArrVtx[_Index].BINORMAL.Normalize3D();
}

void GameEngineFBXMesh::LoadTangent(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementTangentCount();

	if (0 == iCount)
	{
		return;
	}
	FbxGeometryElementTangent* pElement = _Mesh->GetElementTangent();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}
	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
		}
	}

	FbxVector4 Tangent = pElement->GetDirectArray().GetAt(iDataIndex);


	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	Tangent = conversionMeshMatrix.MultT(Tangent);


	_ArrVtx[_Index].TANGENT.x = (float)Tangent.mData[0];
	_ArrVtx[_Index].TANGENT.y = (float)Tangent.mData[1];
	_ArrVtx[_Index].TANGENT.z = -(float)Tangent.mData[2];
	_ArrVtx[_Index].TANGENT.w = (float)Tangent.mData[3];
	_ArrVtx[_Index].TANGENT.Normalize3D();
}

void GameEngineFBXMesh::LoadNormal(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int _Index)
{
	int iCount = _Mesh->GetElementNormalCount();

	if (0 == iCount)
	{
		MsgBoxAssert("GetElementNormalCount가 여러개 입니다.");
	}


	FbxGeometryElementNormal* pElement = _Mesh->GetElementNormal();
	int iDataIndex = VtxId;

	if (pElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	{
		if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(VtxId);
		}
		else
		{
			iDataIndex = VtxId;
		}
	}
	else if (pElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	{
		if (FbxGeometryElement::eDirect == pElement->GetReferenceMode())
		{
			iDataIndex = _Index;
		}
		else if (FbxGeometryElement::eIndexToDirect == pElement->GetReferenceMode())
		{
			iDataIndex = pElement->GetIndexArray().GetAt(_Index);
		}
		else {
			MsgBoxAssert("맵핑 방식중 처리할수 없는 방식입니다.");
		}
	}

	FbxVector4 Normal = pElement->GetDirectArray().GetAt(iDataIndex);

	fbxsdk::FbxAMatrix conversionMeshMatrix = _MeshMatrix.Transpose();
	Normal = conversionMeshMatrix.MultT(Normal);

	_ArrVtx[_Index].NORMAL.x = (float)Normal.mData[0];
	_ArrVtx[_Index].NORMAL.y = (float)Normal.mData[1];
	_ArrVtx[_Index].NORMAL.z = -(float)Normal.mData[2];
	_ArrVtx[_Index].NORMAL.w = (float)Normal.mData[3];
	// _ArrVtx[_Index].Normal.w = 0.0f;
	_ArrVtx[_Index].NORMAL.Normalize3D();
}

void GameEngineFBXMesh::LoadUV(fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxAMatrix _MeshMatrix, std::vector<GameEngineVertex>& _ArrVtx, int VtxId, int VertexCount, int _Index)
{
	// pMesh->GetTextureUVIndex(PolygonIndex, PositionInPolygon), VtxId, ControlPointIndex

	int iCount = _Mesh->GetElementUVCount();

	if (0 == iCount)
	{
		return;
	}

	float4 result;

	FbxGeometryElementUV* pElement = _Mesh->GetElementUV();
	int iDataIndex = VtxId;
	switch (pElement->GetMappingMode())
		//switch (vertexTangnet->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
		switch (pElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result.x = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[0]);
			result.y = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[1]);
			// result.z = static_cast<float>(pElement->GetDirectArray().GetAt(_Index).mData[2]);
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pElement->GetIndexArray().GetAt(_Index);
			result.x = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[0]);
			result.y = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[1]);
			// result.z = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[2]);
		}
		break;
		default:
		{
		}
		break;
		}
		break;

	case FbxGeometryElement::eByPolygonVertex:
		switch (pElement->GetReferenceMode())
		{
		case FbxGeometryElement::eDirect:
		{
			result.x = static_cast<float>(pElement->GetDirectArray().GetAt(VtxId).mData[0]);
			result.y = static_cast<float>(pElement->GetDirectArray().GetAt(VtxId).mData[1]);
		}
		break;

		case FbxGeometryElement::eIndexToDirect:
		{
			int index = pElement->GetIndexArray().GetAt(VertexCount);
			result.x = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[0]);
			result.y = static_cast<float>(pElement->GetDirectArray().GetAt(index).mData[1]);
		}
		break;
		default:
		{
		}
		break;
		}
		break;
	}

	_ArrVtx[_Index].TEXCOORD.x = (float)result.x;
	// _ArrVtx[_Index].TEXCOORD.y = (float)result.y;
	_ArrVtx[_Index].TEXCOORD.y = 1.0f - (float)result.y;
}



void GameEngineFBXMesh::VertexBufferCheck()
{
	int meshInfoSize = static_cast<int>(MeshInfos.size());
	for (int meshInfoIndex = 0; meshInfoIndex < meshInfoSize; ++meshInfoIndex)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(meshInfoIndex);
		fbxsdk::FbxNode* pMeshNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* pMesh = meshInfo.Mesh;

		// 인덱스 버퍼 기준으로 만들어야 한다.
		// 나중에 변경
		FbxRenderUnitInfo& RenderUnit = RenderUnitInfos.emplace_back();
		RenderUnit.VectorIndex = meshInfoIndex;

		if (RenderUnit.MapWI.end() == RenderUnit.MapWI.find(pMesh))
		{
			RenderUnit.MapWI.insert(std::make_pair(pMesh, std::map<int, std::vector<FbxExIW>>()));
		}

		RenderUnit.IsLod = meshInfo.bIsLodGroup;
		RenderUnit.IsLodLv = meshInfo.LodLevel;
		std::vector<GameEngineVertex>& VtxData = RenderUnit.Vertexs;
		std::vector<std::vector<UINT>>& IdxData = RenderUnit.Indexs;

		// 버텍스 개수입니다.
		int controlPointsCount = pMesh->GetControlPointsCount();

		// 그 버텍스 개수는 배열로 저장되어있는데 첫번째 포인터.
		fbxsdk::FbxVector4* pControlPoints = pMesh->GetControlPoints();

		VtxData.resize(controlPointsCount);

		fbxsdk::FbxAMatrix meshMatrix = ConvertMatrix;
		meshMatrix = ComputeTotalMatrix(pMeshNode);
		if (false == meshInfo.bIsSkeletalMesh)
		{
			// 애니메메이션일 경우에는 애니메이션의 특수한 본정보를 기반으로 버텍스를 전환해서 받아야 하는데.
			meshMatrix = JointMatrix * meshMatrix;
		}

		// 크기가 -인게 있는지 확인
		bool isOddNegativeScale = IsOddNegativeScale(meshMatrix);

		// 컨트롤 포인트 개수만큼 돌면서 버텍스의 정보를 모두 얻어온다.
		for (int controlPointIndex = 0; controlPointIndex < controlPointsCount; ++controlPointIndex)
		{
			// 버텍스를 얻어오고
			fbxsdk::FbxVector4 controlPoint = pControlPoints[controlPointIndex];
			// 혹시나 애니메이션이 있을경우에는 애니메이션의 행렬을 고려해서 버텍스 정보를 변환한다.
			// 애니메이션이 없다면 그냥 기본행렬일 것이다.
			fbxsdk::FbxVector4 calculateControlPoint = meshMatrix.MultT(controlPoint);
			// FBX는 기본적으로 3d 맥스에서 사용하는데. 
			// 데카르트 좌표계에서 z만 -가 되어있다.

			VtxData[controlPointIndex].POSITION = FbxVecToTransform(calculateControlPoint);
			VtxData[controlPointIndex].POSITION.w = 1.0f;

			if (RenderUnit.MaxBoundBox.x < VtxData[controlPointIndex].POSITION.x)			{				RenderUnit.MaxBoundBox.x = VtxData[controlPointIndex].POSITION.x;			}
			if (RenderUnit.MaxBoundBox.y < VtxData[controlPointIndex].POSITION.y)			{				RenderUnit.MaxBoundBox.y = VtxData[controlPointIndex].POSITION.y;			}
			if (RenderUnit.MaxBoundBox.z < VtxData[controlPointIndex].POSITION.z) { RenderUnit.MaxBoundBox.z = VtxData[controlPointIndex].POSITION.z; }

			if (RenderUnit.MinBoundBox.x > VtxData[controlPointIndex].POSITION.x) { RenderUnit.MinBoundBox.x = VtxData[controlPointIndex].POSITION.x; }
			if (RenderUnit.MinBoundBox.y > VtxData[controlPointIndex].POSITION.y) { RenderUnit.MinBoundBox.y = VtxData[controlPointIndex].POSITION.y; }
			if (RenderUnit.MinBoundBox.z > VtxData[controlPointIndex].POSITION.z) { RenderUnit.MinBoundBox.z = VtxData[controlPointIndex].POSITION.z; }
		}

		RenderUnit.BoundScaleBox.x = RenderUnit.MaxBoundBox.x - RenderUnit.MinBoundBox.x;
		RenderUnit.BoundScaleBox.y = RenderUnit.MaxBoundBox.y - RenderUnit.MinBoundBox.y;
		RenderUnit.BoundScaleBox.z = RenderUnit.MaxBoundBox.z - RenderUnit.MinBoundBox.z;
		
		// 머티리얼 정보를 얻어오고 텍스처의 경로를 알아낸다.
		FbxRenderUnitInfoMaterialSetting(pMeshNode, &RenderUnit);

		pMesh->GetElementMaterialCount();
		fbxsdk::FbxGeometryElementMaterial* pGeometryElementMaterial = pMesh->GetElementMaterial();
		fbxsdk::FbxGeometryElementNormal* pGeometryElementNormal = pMesh->GetElementNormal();

		int materialCount = pMeshNode->GetMaterialCount();
		IdxData.resize(materialCount);

		UINT VtxId = 0;

		int nPolygonCount = pMesh->GetPolygonCount();
		for (int PolygonIndex = 0; PolygonIndex < nPolygonCount; ++PolygonIndex)
		{
			int PolygonSize = pMesh->GetPolygonSize(PolygonIndex);
			if (3 != PolygonSize)
			{
				MsgBoxAssert("삼각형이 아닌 면이 발견됬습니다.");
			}

			int IndexArray[3] = { 0, };
			for (int PositionInPolygon = 0; PositionInPolygon < PolygonSize; ++PositionInPolygon)
			{
				int ControlPointIndex = pMesh->GetPolygonVertex(PolygonIndex, PositionInPolygon);
				IndexArray[PositionInPolygon] = ControlPointIndex;


				LoadNormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
				LoadTangent(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
				LoadBinormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);

				int Count = pMesh->GetLayerCount();

				//FMeshDescription* MeshDescription = StaticMesh->GetMeshDescription(LODIndex);
				//FStaticMeshAttributes Attributes(*MeshDescription);
				LoadUV(pMesh, meshMatrix, VtxData, pMesh->GetTextureUVIndex(PolygonIndex, PositionInPolygon), VtxId, ControlPointIndex);

				++VtxId;
			}

			int materialId = pGeometryElementMaterial->GetIndexArray().GetAt(PolygonIndex);
			IdxData[materialId].push_back(IndexArray[0]);
			IdxData[materialId].push_back(IndexArray[2]);
			IdxData[materialId].push_back(IndexArray[1]);
		}

		// LoadUVInformation(pMesh, VtxData);

		RenderUnit.FbxVertexMap.insert(std::make_pair(pMesh, &VtxData));
	}

	MeshInfos;
	RenderUnitInfos;
	int a = 0;

}

void GameEngineFBXMesh::LoadUVInformation(fbxsdk::FbxMesh* pMesh, std::vector<GameEngineVertex>& _ArrVtx)
{
	//get all UV set names
	FbxStringList lUVSetNameList;
	pMesh->GetUVSetNames(lUVSetNameList);

	int Index = 0;

	if (1 < lUVSetNameList.GetCount())
	{
		MsgBoxAssert("UV가 2개입니다.");
	}

	GameEngineDebug::OutPutString(" NewMesh Vertex Size : " + std::to_string(_ArrVtx.size()));

	//iterating over all uv sets
	// 여러개 있을수 있네요.
	for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
	{
		//get lUVSetIndex-th uv set
		const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
		const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(lUVSetName);

		if (!lUVElement)
			continue;

		// only support mapping mode eByPolygonVertex and eByControlPoint
		if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
			lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			return;

		//index array, where holds the index referenced to the uv data
		const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
		const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

		//iterating through the data by polygon
		const int lPolyCount = pMesh->GetPolygonCount();

		if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
			{
				// build the max index array that we need to pass into MakePoly
				const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
				{
					FbxVector2 lUVValue;

					//get the index of the current vertex in control points array
					int lPolyVertIndex = pMesh->GetPolygonVertex(lPolyIndex, lVertIndex);

					//the UV index depends on the reference mode
					int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

					lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

					_ArrVtx[lVertIndex].TEXCOORD.x = static_cast<float>(lUVValue.mData[0]);
					_ArrVtx[lVertIndex].TEXCOORD.y = 1.0f - static_cast<float>(lUVValue.mData[1]);

					//User TODO:
					//Print out the value of UV(lUVValue) or log it to a file
				}
			}
		}
		else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int lPolyIndexCounter = 0;
			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
			{
				// build the max index array that we need to pass into MakePoly
				const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
				{
					if (lPolyIndexCounter < lIndexCount)
					{
						FbxVector2 lUVValue;

						//the UV index depends on the reference mode
						int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

						lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

						//int VertexIndex = pMesh->GetTextureUVIndex(lPolyIndex, lVertIndex);

						//_ArrVtx[VertexIndex].TEXCOORD.x = static_cast<float>(lUVValue.mData[0]);
						//_ArrVtx[VertexIndex].TEXCOORD.y = 1.0f - static_cast<float>(lUVValue.mData[1]);

						//float4 Test;
						//Test.x = static_cast<float>(lUVValue.mData[0]);
						//Test.y = static_cast<float>(lUVValue.mData[1]);
						//GameEngineDebug::OutPutString(Test.ToString() + " Index : " + std::to_string(Index));
						//++Index;

						lPolyIndexCounter++;
					}
				}
			}
		}

	}

}


fbxsdk::FbxNode* GameEngineFBXMesh::RecursiveFindParentLodGroup(fbxsdk::FbxNode* parentNode)
{
	if (nullptr == parentNode)
	{
		return nullptr;
	}
	fbxsdk::FbxNodeAttribute* attribute = parentNode->GetNodeAttribute();
	if (nullptr != attribute && attribute->GetAttributeType() == fbxsdk::FbxNodeAttribute::eLODGroup)
	{
		return parentNode;
	}
	return RecursiveFindParentLodGroup(parentNode->GetParent());
}



fbxsdk::FbxNode* GameEngineFBXMesh::RecursiveGetFirstMeshNode(fbxsdk::FbxNode* Node, fbxsdk::FbxNode* NodeToFind)
{
	if (Node == nullptr)
	{
		return nullptr;
	}

	if (Node->GetMesh() != nullptr)
	{
		return Node;
	}

	for (int ChildIndex = 0; ChildIndex < Node->GetChildCount(); ++ChildIndex)
	{
		fbxsdk::FbxNode* MeshNode = RecursiveGetFirstMeshNode(Node->GetChild(ChildIndex), NodeToFind);
		if (NodeToFind == nullptr)
		{
			if (MeshNode != nullptr)
			{
				return MeshNode;
			}
		}
		else if (MeshNode == NodeToFind)
		{
			return MeshNode;
		}
	}
	return nullptr;
}


fbxsdk::FbxNode* GameEngineFBXMesh::FindLODGroupNode(fbxsdk::FbxNode* NodeLodGroup, int LodIndex, fbxsdk::FbxNode* NodeToFind)
{
	if (NodeLodGroup->GetChildCount() < LodIndex)
	{
		MsgBoxAssert("잘못된 인덱스");
		return nullptr;
	}
	fbxsdk::FbxNode* childNode = NodeLodGroup->GetChild(LodIndex);
	if (nullptr == childNode)
	{
		return nullptr;
	}
	return RecursiveGetFirstMeshNode(childNode, NodeToFind);
}



void GameEngineFBXMesh::MeshNodeCheck()
{
	int geometryCount = Scene->GetGeometryCount();
	for (int i = 0; i < geometryCount; i++)
	{
		// 노드중에서 기하구조를 가진녀석들을 뽑아내는것이고.
		fbxsdk::FbxGeometry* geoMetry = Scene->GetGeometry(i);
		fbxsdk::FbxNode* geoMetryNode = geoMetry->GetNode();

		// FBXInfoDebugFunction(geoMetryNode);

		if (nullptr == geoMetry)
		{
			continue;
		}

		// 뽑아낸 애들중에서 그 타입이
		if (geoMetry->GetAttributeType() != fbxsdk::FbxNodeAttribute::eMesh)
		{
			continue;
		}

		FbxExMeshInfo& Info = MeshInfos.emplace_back();

		if (geoMetry->GetName()[0] != '\0')
		{
			Info.Name = GameEngineString::AnsiToUTF8Return(geoMetry->GetName());
		}
		else {
			Info.Name = nullptr != geoMetryNode ? GameEngineString::AnsiToUTF8Return(geoMetryNode->GetName()) : "None";
		}

		Info.Mesh = reinterpret_cast<fbxsdk::FbxMesh*>(geoMetry);

		// bTriangulated 했으므로 문제는 없을것이지만 만약 이게 삼각형으로 랜더링하는 매쉬가 아니라면 우리로서는 처리할 방법이 없다.
		Info.bTriangulated = Info.Mesh->IsTriangleMesh();
		Info.MaterialNum = geoMetryNode ? geoMetryNode->GetMaterialCount() : 0;
		Info.FaceNum = Info.Mesh->GetPolygonCount();
		Info.VertexNum = Info.Mesh->GetControlPointsCount();
		Info.UniqueId = Info.Mesh->GetUniqueID();


		// 나중에 정리할수 있을것 같다.
		Info.LODGroupName = "";
		if (nullptr != geoMetryNode)
		{
			fbxsdk::FbxNode* ParentNode = RecursiveFindParentLodGroup(geoMetryNode->GetParent());
			if (ParentNode != nullptr && ParentNode->GetNodeAttribute()
				&& ParentNode->GetNodeAttribute()->GetAttributeType() == fbxsdk::FbxNodeAttribute::eLODGroup)
			{
				Info.LODGroupName = GameEngineString::AnsiToUTF8Return(ParentNode->GetName());
				Info.bIsLodGroup = true;
				for (int LODIndex = 0; LODIndex < ParentNode->GetChildCount(); LODIndex++)
				{
					fbxsdk::FbxNode* MeshNode = FindLODGroupNode(ParentNode, LODIndex, geoMetryNode);
					if (geoMetryNode == MeshNode)
					{
						Info.LodLevel = LODIndex;
						break;
					}
				}
			}
		}

		// 디포머는 본과 매쉬를 이어주는 기능을 합니다.
		// 디포머 카운트가 0이 아니라는건.
		if (Info.Mesh->GetDeformerCount(FbxDeformer::eSkin) > 0)
		{
			Info.bIsSkeletalMesh = true;
			Info.MorphNum = Info.Mesh->GetShapeCount();
			// 매쉬의 스키닝
			// 매쉬가 끊어지는 것을 방지하기 위한 버텍스의 가중치등의 정보를 가지고 있는 녀석.
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)Info.Mesh->GetDeformer(0, FbxDeformer::eSkin);
			int ClusterCount = Skin->GetClusterCount();
			fbxsdk::FbxNode* Link = NULL;
			for (int ClusterId = 0; ClusterId < ClusterCount; ++ClusterId)
			{
				fbxsdk::FbxCluster* Cluster = Skin->GetCluster(ClusterId);
				// 서로 연결된 
				Link = Cluster->GetLink();
				while (Link && Link->GetParent() && Link->GetParent()->GetSkeleton())
				{
					Link = Link->GetParent();
				}

				if (Link != NULL)
				{
					break;
				}
			}

			// Info.SkeletonRoot = nullptr != Link ? GameEngineString::UTF8ToAnsiReturn(Link->GetName()) : "None";

			Info.SkeletonRoot = nullptr != Link ? Link->GetName() : "None";
			Info.SkeletonElemNum = nullptr != Link ? Link->GetChildCount(true) : 0;

			//if (nullptr != Link)
			//{
			//	fbxsdk::FbxTimeSpan AnimTimeSpan(fbxsdk::FBXSDK_TIME_INFINITE, fbxsdk::FBXSDK_TIME_MINUS_INFINITE);
			//	Link->GetAnimationInterval(AnimTimeSpan);
			//	GlobalTimeSpan.UnionAssignment(AnimTimeSpan);
			//}
		}
		else
		{
			Info.bIsSkeletalMesh = false;
			Info.SkeletonRoot = "";
		}
	}
}

std::shared_ptr<GameEngineMesh> GameEngineFBXMesh::GetGameEngineMesh(size_t _MeshIndex, size_t _SubIndex)
{
	if (RenderUnitInfos.size() <= _MeshIndex)
	{
		MsgBoxAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	FbxRenderUnitInfo& Unit = RenderUnitInfos[_MeshIndex];

	if (nullptr == Unit.VertexBuffer)
	{
		std::shared_ptr<GameEngineVertexBuffer> VertexBuffer = GameEngineVertexBuffer::Create(Unit.Vertexs);

		if (nullptr == VertexBuffer)
		{
			MsgBoxAssert("FBX 버텍스 버퍼 생성 실패.");
		}

		Unit.VertexBuffer = VertexBuffer;
	}

	if (Unit.Indexs.size() <= _SubIndex)
	{
		MsgBoxAssert("존재하지 않는 서브셋을 만들려고 했습니다. 인덱스 버퍼를 생성할수 없습니다.");
	}

	if (Unit.IndexBuffers.empty())
	{
		Unit.IndexBuffers.resize(Unit.Indexs.size());
	}

	if (nullptr == Unit.IndexBuffers[_SubIndex])
	{
		std::shared_ptr<GameEngineIndexBuffer> IndexBuffer = GameEngineIndexBuffer::Create(Unit.Indexs[_SubIndex]);

		if (nullptr == IndexBuffer)
		{
			MsgBoxAssert("FBX 버텍스 버퍼 생성 실패.");
		}

		Unit.IndexBuffers[_SubIndex] = IndexBuffer;
	}

	if (Unit.Meshs.empty())
	{
		Unit.Meshs.resize(Unit.Indexs.size());
	}

	if (nullptr == Unit.Meshs[_SubIndex])
	{
		Unit.Meshs[_SubIndex] = GameEngineMesh::Create(Unit.VertexBuffer, Unit.IndexBuffers[_SubIndex]);
	}

	// 끝나면 이에 해당하는 메테리얼을 확인합니다.

	if (
		false == Unit.MaterialData[_SubIndex].DifTextureName.empty()
		&& "" != Unit.MaterialData[_SubIndex].DifTextureName
		)
	{
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(Unit.MaterialData[_SubIndex].DifTextureName);

		if (nullptr == Texture)
		{
			Path = GameEngineDirectory::GetFolderPath(GetPath());

			// CH_NPC_MOB_Anashar_A01_Lower_D_KGW.tga

			std::string FilePath = Path + Unit.MaterialData[_SubIndex].DifTextureName;
			GameEngineTexture::Load(FilePath);
		}
	}
	

	return Unit.Meshs[_SubIndex];
}

const FbxExMaterialSettingData& GameEngineFBXMesh::GetMaterialSettingData(size_t _MeshIndex, size_t _SubIndex)
{
	if (RenderUnitInfos.size() <= _MeshIndex)
	{
		MsgBoxAssert("존재하지 않는 랜더 유니트를 사용하려고 했습니다.");
	}

	FbxRenderUnitInfo& Unit = RenderUnitInfos[_MeshIndex];

	if (Unit.MaterialData.size() <= _SubIndex)
	{
		MsgBoxAssert("존재하지 않는 재질정보를 얻어오려고 했습니다.");
	}

	return Unit.MaterialData[_SubIndex];
}

// 본의 정보를 가져오는것이기 때문에 
bool GameEngineFBXMesh::ImportBone()
{
	std::string Path = GetPath();

	if (0 != AllBones.size())
	{
		return false;
	}


	size_t meshCount = MeshInfos.size();
	if (0 == meshCount)
	{
		return false;
	}

	// 이건 스키닝 관련 정보가 있는 녀석.
	std::vector<fbxsdk::FbxNode*> MeshNodeArray;

	// 스키닝 관련 정보가 다 들어있다. 이걸 모으기 위한 함수
	std::vector<std::vector<fbxsdk::FbxCluster*>> ClusterArray;
	fbxsdk::FbxNode* Link = nullptr;
	int SkelType = 0;

	ClusterArray.resize(MeshInfos.size());

	// 디포머는 n개의 클러스터를 가지고 있고
	// 클러스터는 스키닝(버텍스가 영향받는 본에 대한 정보를 가지고 있다.)
	for (size_t meshindex = 0; meshindex < meshCount; ++meshindex)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(meshindex);

		fbxsdk::FbxNode* pNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* FbxMesh = meshInfo.Mesh;

		MeshNodeArray.push_back(pNode);
		const int SkinDeformerCount = FbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);
		for (int DeformerIndex = 0; DeformerIndex < SkinDeformerCount; DeformerIndex++)
		{
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)FbxMesh->GetDeformer(DeformerIndex, fbxsdk::FbxDeformer::eSkin);
			for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ClusterIndex++)
			{
				ClusterArray[meshindex].push_back(Skin->GetCluster(ClusterIndex));
			}
		}
	}

	if (0 == ClusterArray.size())
	{
		return false;
	}

	// 조사한 클러스터들에 연결되어있는 본들을 조사하기 시작한다.
	for (size_t Clusterindex = 0; Clusterindex < ClusterArray.size(); Clusterindex++)
	{
		AllBones.emplace_back();
		std::map<std::string, Bone*>& FindMap = AllFindMap.emplace_back();

		if (0 == ClusterArray[Clusterindex].size())
		{
			continue;
		}

		// 클러스터와 연결된 노드들이 전부다 여기로 들어가게 되고.
		std::vector<fbxsdk::FbxNode*> SortedLinks;

		fbxsdk::FbxNode* SkeletalMeshNode = nullptr;
		SkeletalMeshNode = MeshNodeArray[Clusterindex];

		fbxsdk::PoseList PoseArray;

		// 애니메이션의 불필요한 포즈등을 제거하고 최적화하는 작업을 거친다.
		if (RetrievePoseFromBindPose(Scene, MeshNodeArray, PoseArray) == false)
		{
			const int PoseCount = Scene->GetPoseCount();
			for (int PoseIndex = PoseCount - 1; PoseIndex >= 0; --PoseIndex)
			{
				fbxsdk::FbxPose* CurrentPose = Scene->GetPose(PoseIndex);

				if (CurrentPose && CurrentPose->IsBindPose())
				{
					Scene->RemovePose(PoseIndex);
					CurrentPose->Destroy();
				}
			}

			Manager->CreateMissingBindPoses(Scene);
			if (RetrievePoseFromBindPose(Scene, MeshNodeArray, PoseArray) == false)
			{
				// MsgBoxAssert("Recreating bind pose failed.");
			}
		}

		BuildSkeletonSystem(Scene, ClusterArray[Clusterindex], SortedLinks);

		std::map<fbxsdk::FbxNode*, std::set<fbxsdk::FbxCluster*>> ClusterSet;

		for (int ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
		{
			for (size_t i = 0; i < ClusterArray[ClusterIndex].size(); i++)
			{
				fbxsdk::FbxCluster* Cluster = ClusterArray[ClusterIndex][i];
				ClusterSet[Cluster->GetLink()].insert(ClusterArray[ClusterIndex][i]);;
			}
		}


		// 본이 없다는 이야기.
		if (SortedLinks.size() == 0)
		{
			continue;
		}

		std::map<fbxsdk::FbxString, int> m_NameBoneCheck;
		size_t LinkIndex;

		for (LinkIndex = 0; LinkIndex < SortedLinks.size(); ++LinkIndex)
		{
			Link = SortedLinks[LinkIndex];
			m_NameBoneCheck.insert(std::make_pair(Link->GetName(), 0));

			for (size_t AltLinkIndex = LinkIndex + 1; AltLinkIndex < SortedLinks.size(); ++AltLinkIndex)
			{
				fbxsdk::FbxNode* AltLink = SortedLinks[AltLinkIndex];

				fbxsdk::FbxString tempLinkName = Link->GetName();
				fbxsdk::FbxString tempAltLinkName = AltLink->GetName();

				std::map<fbxsdk::FbxString, int>::iterator FindBoneNameIter = m_NameBoneCheck.find(tempAltLinkName);

				// 같은 이름의 본이 있어서
				// 기존 본의 겹치는 이름을 변경해준다.
				if (FindBoneNameIter != m_NameBoneCheck.end())
				{
					fbxsdk::FbxString newName = FindBoneNameIter->first;
					newName += "_";
					newName += (++FindBoneNameIter->second);

					// 만약에 바꿨는데도 미친 또 있어
					std::map<fbxsdk::FbxString, int>::iterator RevertIter = m_NameBoneCheck.find(newName);

					while (RevertIter != m_NameBoneCheck.find(newName))
					{
						newName = FindBoneNameIter->first;
						newName += "_";
						newName += (++FindBoneNameIter->second);
						RevertIter = m_NameBoneCheck.find(newName);
					}

					// 겹치는 이름의 링크는 이 새이름을 바꾸면
					// 앞으로 펼쳐질 본과 관련된 모든곳에서
					// 이 이름으로 계산될것이므로 걱정할 필요가 없어진다.
					AltLink->SetName(newName.Buffer());
				}
			}
		}


		// 최종적으로 SortedLinks에는 이제 의미있는 본노드들만 담겨있다.
		// 이제 정리된 본의 
		fbxsdk::FbxArray<fbxsdk::FbxAMatrix> GlobalsPerLink;
		GlobalsPerLink.Grow(static_cast<int>(SortedLinks.size()));
		GlobalsPerLink[0] = ConvertMatrix;

		bool GlobalLinkFoundFlag;
		fbxsdk::FbxVector4 LocalLinkT;
		fbxsdk::FbxQuaternion LocalLinkQ;
		fbxsdk::FbxVector4	LocalLinkS;
		fbxsdk::FbxVector4 GlobalLinkT;
		fbxsdk::FbxQuaternion GlobalLinkQ;
		fbxsdk::FbxVector4	GlobalLinkS;

		bool bAnyLinksNotInBindPose = false;
		std::string LinksWithoutBindPoses;
		int NumberOfRoot = 0;

		int RootIdx = -1;

		for (LinkIndex = 0; LinkIndex < SortedLinks.size(); LinkIndex++)
		{
			Bone& tempBoneData = AllBones[Clusterindex].emplace_back();
			// Bone& tempBoneData = m_vecRefBones.at(m_vecRefBones.size() - 1);
			tempBoneData.Index = static_cast<int>(AllBones[Clusterindex].size() - 1);

			Link = SortedLinks[LinkIndex];

			int ParentIndex = -1;
			fbxsdk::FbxNode* LinkParent = Link->GetParent();
			if (LinkIndex)
			{
				for (int ll = 0; ll < LinkIndex; ++ll)
				{
					fbxsdk::FbxNode* Otherlink = SortedLinks[ll];
					if (Otherlink == LinkParent)
					{
						ParentIndex = ll;
						break;
					}
				}
			}

			if (ParentIndex == -1)
			{
				++NumberOfRoot;
				RootIdx = static_cast<int>(LinkIndex);
				//	unreal 에서는 루트를 하나만 허용하지만 
				//	유니티에서는 여러개를 허용해서 밑의 코드를 제거함
				/*if (NumberOfRoot > 1)
				{
					AMSG(L"여러개의 루트");
				}*/
			}

			GlobalLinkFoundFlag = false;
			if (!SkelType)
			{
				if (PoseArray.GetCount())
				{
					for (int PoseIndex = 0; PoseIndex < PoseArray.GetCount(); PoseIndex++)
					{
						int PoseLinkIndex = PoseArray[PoseIndex]->Find(Link);
						if (PoseLinkIndex >= 0)
						{
							fbxsdk::FbxMatrix NoneAffineMatrix = PoseArray[PoseIndex]->GetMatrix(PoseLinkIndex);
							fbxsdk::FbxAMatrix Matrix = *(fbxsdk::FbxAMatrix*)(double*)&NoneAffineMatrix;
							GlobalsPerLink[static_cast<int>(LinkIndex)] = Matrix;
							GlobalLinkFoundFlag = true;
							break;
						}
					}
				}

				if (!GlobalLinkFoundFlag)
				{

					std::map<fbxsdk::FbxNode*, std::set<fbxsdk::FbxCluster*>>::iterator FindIter = ClusterSet.find(Link);

					if (FindIter != ClusterSet.end())
					{
						for (fbxsdk::FbxCluster* Cluster : FindIter->second)
						{
							Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
							GlobalLinkFoundFlag = true;
							break;
						}
					}

					//for (int ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
					//{
					//	//fbxsdk::FbxCluster* Cluster = ClusterArray[0][ClusterIndex];
					//	//if (Link == Cluster->GetLink())
					//	//{
					//	//	Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
					//	//	GlobalLinkFoundFlag = true;
					//	//	break;
					//	//}

					//	for (size_t i = 0; i < ClusterArray[ClusterIndex].size(); i++)
					//	{
					//		fbxsdk::FbxCluster* Cluster = ClusterArray[ClusterIndex][i];
					//		if (Link == Cluster->GetLink())
					//		{
					//			Cluster->GetTransformLinkMatrix(GlobalsPerLink[static_cast<int>(LinkIndex)]);
					//			GlobalLinkFoundFlag = true;
					//			break;
					//		}
					//	}
					//}
				}
			}

			if (!GlobalLinkFoundFlag)
			{
				GlobalsPerLink[static_cast<int>(LinkIndex)] = Link->EvaluateGlobalTransform();
			}

			GlobalsPerLink[static_cast<int>(LinkIndex)] = GlobalsPerLink[static_cast<int>(LinkIndex)];
			if (LinkIndex &&
				-1 != ParentIndex)
			{
				fbxsdk::FbxAMatrix	Matrix;
				Matrix = GlobalsPerLink[static_cast<int>(ParentIndex)].Inverse() * GlobalsPerLink[static_cast<int>(LinkIndex)];
				LocalLinkT = Matrix.GetT();
				LocalLinkQ = Matrix.GetQ();
				LocalLinkS = Matrix.GetS();
				GlobalLinkT = GlobalsPerLink[static_cast<int>(LinkIndex)].GetT();
				GlobalLinkQ = GlobalsPerLink[static_cast<int>(LinkIndex)].GetQ();
				GlobalLinkS = GlobalsPerLink[static_cast<int>(LinkIndex)].GetS();
			}
			else
			{
				GlobalLinkT = LocalLinkT = GlobalsPerLink[static_cast<int>(LinkIndex)].GetT();
				GlobalLinkQ = LocalLinkQ = GlobalsPerLink[static_cast<int>(LinkIndex)].GetQ();
				GlobalLinkS = LocalLinkS = GlobalsPerLink[static_cast<int>(LinkIndex)].GetS();
			}

			Bone& Bone = AllBones[Clusterindex][static_cast<int>(LinkIndex)];

			Bone.Name = Link->GetName();

			JointPos& BonePosData = Bone.BonePos;
			fbxsdk::FbxSkeleton* Skeleton = Link->GetSkeleton();
			if (Skeleton)
			{
				BonePosData.Length = (float)Skeleton->LimbLength.Get();
				BonePosData.XSize = (float)Skeleton->Size.Get();
				BonePosData.YSize = (float)Skeleton->Size.Get();
				BonePosData.ZSize = (float)Skeleton->Size.Get();
			}
			else
			{
				BonePosData.Length = 1.;
				BonePosData.XSize = 100.;
				BonePosData.YSize = 100.;
				BonePosData.ZSize = 100.;
			}

			Bone.ParentIndex = ParentIndex;
			Bone.NumChildren = 0;
			for (int ChildIndex = 0; ChildIndex < Link->GetChildCount(); ChildIndex++)
			{
				fbxsdk::FbxNode* Child = Link->GetChild(ChildIndex);
				if (IsBone(Child))
				{
					Bone.NumChildren++;
				}
			}

			BonePosData.SetTranslation(LocalLinkT);
			BonePosData.SetRotation(LocalLinkQ);
			BonePosData.SetScale(LocalLinkS);
			BonePosData.SetGlobalTranslation(GlobalLinkT);
			BonePosData.SetGlobalRotation(GlobalLinkQ);
			BonePosData.SetGlobalScale(GlobalLinkS);
			BonePosData.BuildMatrix();
		}


		for (size_t i = 0; i < AllBones[Clusterindex].size(); i++)
		{
			if (FindMap.end() == FindMap.find(AllBones[Clusterindex][i].Name))
			{
				FindMap.insert(std::make_pair(AllBones[Clusterindex][i].Name, &AllBones[Clusterindex][i]));
				continue;
			}

			std::multimap<std::string, Bone*>::iterator it, itlow, itup;

			itlow = FindMap.lower_bound(AllBones[Clusterindex][i].Name);  // itlow points to b
			itup = FindMap.upper_bound(AllBones[Clusterindex][i].Name);   // itup points to e (not d)

			int Count = 0;
			for (it = itlow; it != itup; ++it)
			{
				++Count;
			}

			std::string Name = AllBones[Clusterindex][i].Name + std::to_string(Count);
			FindMap.insert(std::make_pair(GameEngineString::ToUpperReturn(Name), &AllBones[Clusterindex][i]));
		}


	}

	LoadSkinAndCluster();

	return true;
}


void GameEngineFBXMesh::ImportCluster()
{
	size_t meshCount = MeshInfos.size();
	if (0 == meshCount)
	{
		return;
	}

	// 그냥 이때 다시하자.
	for (size_t n = 0; n < meshCount; ++n)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(n);
		fbxsdk::FbxNode* pNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* FbxMesh = meshInfo.Mesh;
		const int SkinDeformerCount = FbxMesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin);

		std::vector<FbxClusterData>& vecClusterData = ClusterData.emplace_back();

		// 요주의 선생님이 바꾼코드라 무슨 사이드 이펙트를 일으킬지모릅니다.
		if (0 == SkinDeformerCount)
		{
			continue;
		}

		for (int DeformerIndex = 0; DeformerIndex < SkinDeformerCount; DeformerIndex++)
		{
			fbxsdk::FbxSkin* Skin = (fbxsdk::FbxSkin*)FbxMesh->GetDeformer(DeformerIndex, fbxsdk::FbxDeformer::eSkin);
			for (int ClusterIndex = 0; ClusterIndex < Skin->GetClusterCount(); ClusterIndex++)
			{
				vecClusterData.push_back(FbxClusterData());
				FbxClusterData& clusterData = vecClusterData[vecClusterData.size() - 1];
				clusterData.Cluster = Skin->GetCluster(ClusterIndex);
				clusterData.Mesh = FbxMesh;
				clusterData.LinkName = clusterData.Cluster->GetLink()->GetName();
			}
		}
	}
}


void GameEngineFBXMesh::DrawSetWeightAndIndexSetting(FbxRenderUnitInfo* _DrawSet, fbxsdk::FbxMesh* _Mesh, fbxsdk::FbxCluster* _Cluster, int _BoneIndex)
{
	if (nullptr == _DrawSet)
	{
		return;
	}

	int iIndexCount = _Cluster->GetControlPointIndicesCount();

	for (size_t i = 0; i < iIndexCount; i++)
	{
		FbxExIW IW;
		IW.Index = _BoneIndex;

		IW.Weight = _Cluster->GetControlPointWeights()[i];
		int ControlPointIndices = _Cluster->GetControlPointIndices()[i];

		_DrawSet->MapWI[_Mesh][ControlPointIndices].push_back(IW);
	}
}


void GameEngineFBXMesh::LoadAnimationVertexData(FbxRenderUnitInfo* _MeshSet, const std::vector<FbxClusterData>& vecClusterData)
{
	for (auto& clusterData : vecClusterData)
	{
		if (nullptr == clusterData.Cluster->GetLink())
		{
			continue;
		}

		std::string StrBoneName = clusterData.LinkName;
		Bone* pBone = FindBone(_MeshSet->VectorIndex, StrBoneName);
		if (nullptr == pBone)
		{
			continue;
		}

		DrawSetWeightAndIndexSetting(_MeshSet, clusterData.Mesh, clusterData.Cluster, pBone->Index);
	}
}


// 가중치와 본이 10개 20 int4그중에서 너무 미약하거나 이런애들 잘라버리고
// 다 더했는데 1이 아닌것도 체크해서 정리하고.
void GameEngineFBXMesh::CalAnimationVertexData(FbxRenderUnitInfo& _DrawSet)
{
	for (auto& _WISet : _DrawSet.MapWI)
	{
		std::vector<GameEngineVertex>* Ptr = &_DrawSet.Vertexs;

		if (nullptr == Ptr)
		{
			MsgBoxAssert("버텍스 데이터와 수집한 가중치 데이터가 매칭되지 않습니다.");
		}

		std::vector<GameEngineVertex>& VertexData = *Ptr;

		for (auto& _WI : _WISet.second)
		{
			double dWeight = 0.0;
			for (int n = 0; n < _WI.second.size(); ++n)
			{
				dWeight += _WI.second[n].Weight;
			}

			for (int n = 0; n < _WI.second.size(); ++n)
			{
				_WI.second[n].Weight /= dWeight;
			}

			if (_WI.second.size() > 4)
			{
				std::sort(_WI.second.begin(), _WI.second.end(),
					[](const FbxExIW& _Left, const FbxExIW& _Right) {
						return _Left.Weight > _Right.Weight;
					}
				);

				double dInterPolate = 0.0;

				std::vector<FbxExIW>::iterator IterErase = _WI.second.begin() + 4;
				for (; IterErase != _WI.second.end(); ++IterErase)
				{
					dInterPolate += IterErase->Weight;
				}
				IterErase = _WI.second.begin() + 4;

				_WI.second.erase(IterErase, _WI.second.end());
				_WI.second[0].Weight += dInterPolate;
			};

			float Weight[4] = { 0.0f };
			int Index[4] = { 0 };

			for (size_t i = 0; i < _WI.second.size(); i++)
			{
				Weight[i] = (float)_WI.second[i].Weight;
				Index[i] = _WI.second[i].Index;
			}

			memcpy_s(VertexData[_WI.first].WEIGHT.Arr1D, sizeof(float4), Weight, sizeof(float4));
			memcpy_s(VertexData[_WI.first].BLENDINDICES, sizeof(float4), Index, sizeof(float4));
		}
	}
}


void GameEngineFBXMesh::LoadSkinAndCluster()
{
	ImportCluster();

	for (int i = 0; i < RenderUnitInfos.size(); ++i)
	{
		FbxRenderUnitInfo& RenderInfo = RenderUnitInfos[i];
		std::vector<FbxClusterData>& ClusterInfo = ClusterData[i];

		// 클러스터는 가중치 정보와 인덱스 정보를 가지고 있는데
		// 클러스터를 통해서 정보를 가져오고
		LoadAnimationVertexData(&RenderInfo, ClusterInfo);

		// 진짜 가중치를 계산한다.
		CalAnimationVertexData(RenderInfo);
	}
}


bool GameEngineFBXMesh::RetrievePoseFromBindPose(fbxsdk::FbxScene* pScene, const std::vector<fbxsdk::FbxNode*>& NodeArray, fbxsdk::FbxArray<fbxsdk::FbxPose*>& PoseArray)
{
	const int PoseCount = pScene->GetPoseCount();
	for (int PoseIndex = 0; PoseIndex < PoseCount; PoseIndex++)
	{
		fbxsdk::FbxPose* CurrentPose = pScene->GetPose(PoseIndex);

		if (CurrentPose && CurrentPose->IsBindPose())
		{
			std::string PoseName = CurrentPose->GetName();
			fbxsdk::FbxStatus Status;

			for (auto Current : NodeArray)
			{
				std::string CurrentName = Current->GetName();
				fbxsdk::NodeList pMissingAncestors, pMissingDeformers, pMissingDeformersAncestors, pWrongMatrices;

				if (CurrentPose->IsValidBindPoseVerbose(Current, pMissingAncestors, pMissingDeformers, pMissingDeformersAncestors, pWrongMatrices, 0.0001, &Status))
				{
					PoseArray.Add(CurrentPose);
					break;
				}
				else
				{
					for (int i = 0; i < pMissingAncestors.GetCount(); i++)
					{
						fbxsdk::FbxAMatrix mat = pMissingAncestors.GetAt(i)->EvaluateGlobalTransform(FBXSDK_TIME_ZERO);
						CurrentPose->Add(pMissingAncestors.GetAt(i), mat);
					}

					pMissingAncestors.Clear();
					pMissingDeformers.Clear();
					pMissingDeformersAncestors.Clear();
					pWrongMatrices.Clear();

					if (CurrentPose->IsValidBindPose(Current))
					{
						PoseArray.Add(CurrentPose);
						break;
					}
					else
					{
						fbxsdk::FbxNode* ParentNode = Current->GetParent();
						while (ParentNode)
						{
							fbxsdk::FbxNodeAttribute* Attr = ParentNode->GetNodeAttribute();
							if (Attr && Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eNull)
							{
								break;
							}

							ParentNode = ParentNode->GetParent();
						}

						if (ParentNode && CurrentPose->IsValidBindPose(ParentNode))
						{
							PoseArray.Add(CurrentPose);
							break;
						}
						else
						{
							std::string ErrorString = Status.GetErrorString();
							std::string CurrentName = Current->GetName();

							break;
							//MsgBoxAssertString(ErrorString + "_" + CurrentName);
						}
					}
				}
			}
		}
	}

	return (PoseArray.Size() > 0);
}


fbxsdk::FbxNode* GameEngineFBXMesh::GetRootSkeleton(fbxsdk::FbxScene* pScene, fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNode* RootBone = Link;

	while (RootBone && RootBone->GetParent())
	{
		bool bIsBlenderArmatureBone = false;

		fbxsdk::FbxNodeAttribute* Attr = RootBone->GetParent()->GetNodeAttribute();
		if (Attr &&
			(Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh ||
				(Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eNull && !bIsBlenderArmatureBone) ||
				Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eSkeleton) &&
			RootBone->GetParent() != pScene->GetRootNode())
		{
			if (Attr->GetAttributeType() == fbxsdk::FbxNodeAttribute::eMesh)
			{
				fbxsdk::FbxMesh* Mesh = (fbxsdk::FbxMesh*)Attr;
				if (Mesh->GetDeformerCount(fbxsdk::FbxDeformer::eSkin) > 0)
				{
					break;
				}
			}

			RootBone = RootBone->GetParent();
		}
		else
		{
			break;
		}
	}

	return RootBone;
}

bool GameEngineFBXMesh::IsNull(fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNodeAttribute* Attr = Link->GetNodeAttribute();
	if (Attr)
	{
		fbxsdk::FbxNodeAttribute::EType AttrType = Attr->GetAttributeType();
		if (AttrType == fbxsdk::FbxNodeAttribute::eNull)
		{
			return true;
		}
	}
	return false;
}


bool GameEngineFBXMesh::IsBone(fbxsdk::FbxNode* Link)
{
	fbxsdk::FbxNodeAttribute* Attr = Link->GetNodeAttribute();
	if (Attr)
	{
		fbxsdk::FbxNodeAttribute::EType AttrType = Attr->GetAttributeType();
		if (AttrType == fbxsdk::FbxNodeAttribute::eSkeleton ||
			AttrType == fbxsdk::FbxNodeAttribute::eMesh ||
			AttrType == fbxsdk::FbxNodeAttribute::eNull)
		{
			return true;
		}
	}

	return false;
}



void GameEngineFBXMesh::RecursiveBuildSkeleton(fbxsdk::FbxNode* Link, std::vector<fbxsdk::FbxNode*>& OutSortedLinks)
{
	if (IsBone(Link))
	{
		if (false == IsNull(Link))
		{
			OutSortedLinks.push_back(Link);
		}
		int ChildIndex;
		for (ChildIndex = 0; ChildIndex < Link->GetChildCount(); ChildIndex++)
		{
			RecursiveBuildSkeleton(Link->GetChild(ChildIndex), OutSortedLinks);
		}
	}
}


void GameEngineFBXMesh::BuildSkeletonSystem(fbxsdk::FbxScene* pScene, std::vector<fbxsdk::FbxCluster*>& ClusterArray, std::vector<fbxsdk::FbxNode*>& OutSortedLinks)
{
	fbxsdk::FbxNode* Link;
	std::vector<fbxsdk::FbxNode*> RootLinks;
	size_t ClusterIndex;
	for (ClusterIndex = 0; ClusterIndex < ClusterArray.size(); ClusterIndex++)
	{
		Link = ClusterArray[ClusterIndex]->GetLink();
		if (Link)
		{
			Link = GetRootSkeleton(pScene, Link);
			size_t LinkIndex;
			for (LinkIndex = 0; LinkIndex < RootLinks.size(); LinkIndex++)
			{
				if (Link == RootLinks[static_cast<int>(LinkIndex)])
				{
					break;
				}
			}

			if (LinkIndex == RootLinks.size())
			{
				RootLinks.push_back(Link);
			}
		}
	}

	for (size_t LinkIndex = 0; LinkIndex < RootLinks.size(); LinkIndex++)
	{
		RecursiveBuildSkeleton(RootLinks[LinkIndex], OutSortedLinks);
	}
}

void GameEngineFBXMesh::CreateGameEngineStructuredBuffer()
{
	// AllBoneStructuredBuffers.resize(AllBones.size());

	for (size_t i = 0; i < AllBones.size(); i++)
	{
		std::shared_ptr<GameEngineStructuredBuffer> NewStructuredBuffer = AllBoneStructuredBuffers.emplace_back(std::make_shared<GameEngineStructuredBuffer>());
		NewStructuredBuffer->CreateResize(sizeof(float4x4), static_cast<int>(AllBones[i].size()), nullptr);
	}
}

std::shared_ptr<GameEngineStructuredBuffer> GameEngineFBXMesh::GetAnimationStructuredBuffer(size_t _Index)
{
	if (AllBoneStructuredBuffers.size() <= _Index)
	{
		MsgBoxAssert("스트럭처드 버퍼 인덱스 오버");
	}

	return AllBoneStructuredBuffers[_Index];
}