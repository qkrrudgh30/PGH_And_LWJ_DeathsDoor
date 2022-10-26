#include "PreCompile.h"
#include "GameEngineFBXMesh.h"

GameEngineFBXMesh::GameEngineFBXMesh()
{
}

GameEngineFBXMesh::~GameEngineFBXMesh()
{
}



GameEngineFBXMesh* GameEngineFBXMesh::Load(const std::string& _Path, const std::string& _Name)
{
	GameEngineFBXMesh* NewRes = CreateResName(_Name);
	NewRes->LoadMesh(_Path, _Name);
	return NewRes;
}

void GameEngineFBXMesh::LoadMesh(const std::string& _Path, const std::string& _Name)
{
	if (false == CreateFBXSystemInitialize(_Path))
	{
		MsgBoxAssert("시스템 로드에 실패했습니다.");
	}

	FBXConvertScene();

	// 버텍스 정보를 가진 노드를 조사한다.
	MeshLoad();
}

void GameEngineFBXMesh::MeshLoad()
{
	MeshNodeCheck();

	VertexBufferCheck();

	RenderUnitInfos;
	MeshInfos;
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


void GameEngineFBXMesh::FbxRenderUnitMaterialSetting(fbxsdk::FbxNode* _Node, FbxRenderUnit* _RenderData)
{
	int MtrlCount = _Node->GetMaterialCount();

	if (MtrlCount > 0)
	{
		_RenderData->MaterialData.push_back(std::vector<FbxExMaterialSettingData>());

		std::vector<FbxExMaterialSettingData>& MatrialSet = _RenderData->MaterialData[_RenderData->MaterialData.size() - 1];

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
			// fbxsdk::FbxSurfaceMaterial::sNormalMap = 0x00007ff68291bfa0 "NormalMap"
			MatData.NorTexturePath = MaterialTex(pMtrl, "NormalMap");
			MatData.SpcTexturePath = MaterialTex(pMtrl, "SpecularColor");
		}

	}
	else {
		MsgBoxAssert("매쉬는 존재하지만 재질은 존재하지 않습니다.");
	}

}
void GameEngineFBXMesh::VertexBufferCheck()
{
	int meshInfoSize = static_cast<int>(MeshInfos.size());
	for (int meshInfoIndex = 0; meshInfoIndex < meshInfoSize; ++meshInfoIndex)
	{
		FbxExMeshInfo& meshInfo = MeshInfos.at(meshInfoIndex);
		fbxsdk::FbxNode* pMeshNode = meshInfo.Mesh->GetNode();
		fbxsdk::FbxMesh* pMesh = meshInfo.Mesh;

		FbxRenderUnit& RenderUnit = RenderUnitInfos.emplace_back();
		RenderUnit.Index = meshInfoIndex;

		if (RenderUnit.MapWI.end() == RenderUnit.MapWI.find(pMesh))
		{
			RenderUnit.MapWI.insert(std::make_pair(pMesh, std::map<int, std::vector<FbxExIW>>()));
		}

		RenderUnit.IsLod = meshInfo.bIsLodGroup;
		RenderUnit.IsLodLv = meshInfo.LodLevel;
		std::vector<GameEngineVertex>& VtxData = RenderUnit.Vertexs;
		std::vector<std::vector<UINT>>& IdxData = RenderUnit.Indexs.emplace_back();

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
		}
		
		FbxRenderUnitMaterialSetting(pMeshNode, &RenderUnit);

		//pMesh->GetElementMaterialCount();
		//fbxsdk::FbxGeometryElementMaterial* pGeometryElementMaterial = pMesh->GetElementMaterial();
		//fbxsdk::FbxGeometryElementNormal* pGeometryElementNormal = pMesh->GetElementNormal();

		//// pMeshNode->GetMaterialIndex()
		//int materialCount = pMeshNode->GetMaterialCount();
		//IdxData.resize(materialCount);

		//UINT VtxId = 0;

		//int nPolygonCount = pMesh->GetPolygonCount();
		//for (int PolygonIndex = 0; PolygonIndex < nPolygonCount; ++PolygonIndex)
		//{
		//	int PolygonSize = pMesh->GetPolygonSize(PolygonIndex);
		//	if (3 != PolygonSize)
		//	{
		//		GameEngineDebug::MsgBoxError("삼각형이 아닌 면이 발견됬습니다.");
		//	}

		//	int IndexArray[3] = { 0, };
		//	for (int PositionInPolygon = 0; PositionInPolygon < PolygonSize; ++PositionInPolygon)
		//	{
		//		int ControlPointIndex = pMesh->GetPolygonVertex(PolygonIndex, PositionInPolygon);
		//		IndexArray[PositionInPolygon] = ControlPointIndex;


		//		LoadNormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
		//		LoadTangent(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);
		//		LoadBinormal(pMesh, meshMatrix, VtxData, VtxId, ControlPointIndex);

		//		int Count = pMesh->GetLayerCount();

		//		//FMeshDescription* MeshDescription = StaticMesh->GetMeshDescription(LODIndex);
		//		//FStaticMeshAttributes Attributes(*MeshDescription);


		//		LoadUv(pMesh, meshMatrix, VtxData, pMesh->GetTextureUVIndex(PolygonIndex, PositionInPolygon), VtxId, ControlPointIndex);

		//		++VtxId;
		//	}

		//	int materialId = pGeometryElementMaterial->GetIndexArray().GetAt(PolygonIndex);
		//	IdxData[materialId].push_back(IndexArray[0]);
		//	IdxData[materialId].push_back(IndexArray[2]);
		//	IdxData[materialId].push_back(IndexArray[1]);
		//}

		//DrawMesh.FbxVertexMap.insert(std::make_pair(pMesh, &VtxData));
	}

	//std::set<std::string> UVSets;
	//std::vector<std::string> UVVectors;
	//fbxsdk::FbxMesh* pMesh = nullptr;

	//std::vector<FbxLayerElementUV const*> LayerElementUV;
	//std::vector<FbxLayerElement::EReferenceMode> UVReferenceMode;
	//std::vector<FbxLayerElement::EMappingMode> UVMappingMode;

	//for (int meshInfoIndex = 0; meshInfoIndex < meshInfoSize; ++meshInfoIndex)
	//{
	//	FbxExMeshInfo& meshInfo = MeshInfos.at(meshInfoIndex);
	//	fbxsdk::FbxNode* pMeshNode = meshInfo.Mesh->GetNode();
	//	fbxsdk::FbxMesh* pMesh = meshInfo.Mesh;

	//	FbxLayer* BaseLayer = pMesh->GetLayer(0);
	//	if (BaseLayer == NULL)
	//	{
	//		return;
	//	}

	//	int LayerCount = pMesh->GetLayerCount();
	//	if (LayerCount > 0)
	//	{
	//		int UVLayerIndex;
	//		for (UVLayerIndex = 0; UVLayerIndex < LayerCount; UVLayerIndex++)
	//		{
	//			FbxLayer* lLayer = pMesh->GetLayer(UVLayerIndex);
	//			int UVSetCount = lLayer->GetUVSetCount();
	//			if (UVSetCount)
	//			{
	//				FbxArray<FbxLayerElementUV const*> EleUVs = lLayer->GetUVSets();
	//				for (int UVIndex = 0; UVIndex < UVSetCount; UVIndex++)
	//				{
	//					FbxLayerElementUV const* ElementUV = EleUVs[UVIndex];
	//					if (ElementUV)
	//					{
	//						const char* UVSetName = ElementUV->GetName();
	//						std::string LocalUVSetName = UVSetName;
	//						if (LocalUVSetName.empty())
	//						{
	//							LocalUVSetName = TEXT("UVmap_") + std::to_string(UVLayerIndex);
	//						}

	//						if (UVSets.end() == UVSets.find(LocalUVSetName))
	//						{
	//							UVVectors.push_back(LocalUVSetName);
	//							UVSets.insert(LocalUVSetName);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}


	//	// If the the UV sets are named using the following format (UVChannel_X; where X ranges from 1 to 4)
	//	// we will re-order them based on these names.  Any UV sets that do not follow this naming convention
	//	// will be slotted into available spaces.
	//	if (UVSets.size())
	//	{
	//		for (int ChannelNumIdx = 0; ChannelNumIdx < 4; ChannelNumIdx++)
	//		{
	//			std::string ChannelName = "UVChannel_%d" + std::to_string(ChannelNumIdx + 1);
	//			int SetIdx = -1;

	//			for (size_t i = 0; i < UVVectors.size(); i++)
	//			{
	//				if (UVVectors[i] == ChannelName)
	//				{
	//					SetIdx = i;
	//					break;
	//				}
	//			}

	//			//if (SetIdx == -1)
	//			//{
	//			//	GameEngineDebug::AssertFalse();
	//			//}

	//			// If the specially formatted UVSet name appears in the list and it is in the wrong spot,
	//			// we will swap it into the correct spot.
	//			if (SetIdx != -1 && SetIdx != ChannelNumIdx)
	//			{
	//				// If we are going to swap to a position that is outside the bounds of the
	//				// array, then we pad out to that spot with empty data.
	//				for (int ArrSize = UVSets.size(); ArrSize < ChannelNumIdx + 1; ArrSize++)
	//				{
	//					UVVectors.push_back("");
	//					UVSets.insert("");
	//				}
	//				//Swap the entry into the appropriate spot.

	//				std::string Temp = UVVectors[SetIdx];
	//				UVVectors[SetIdx] = UVVectors[ChannelNumIdx];
	//				UVVectors[ChannelNumIdx] = Temp;
	//			}
	//		}
	//	}


	//	{


	//		int UniqueUVCount = UVSets.size();
	//		if (UniqueUVCount > 0)
	//		{
	//			LayerElementUV.resize(UniqueUVCount);
	//			UVReferenceMode.resize(UniqueUVCount);
	//			UVMappingMode.resize(UniqueUVCount);
	//		}
	//		for (size_t UVIndex = 0; UVIndex < UniqueUVCount; UVIndex++)
	//		{
	//			LayerElementUV[UVIndex] = NULL;
	//			for (size_t UVLayerIndex = 0, LayerCount = pMesh->GetLayerCount(); UVLayerIndex < LayerCount; UVLayerIndex++)
	//			{
	//				FbxLayer* lLayer = pMesh->GetLayer(UVLayerIndex);
	//				int UVSetCount = lLayer->GetUVSetCount();
	//				if (UVSetCount)
	//				{
	//					FbxArray<FbxLayerElementUV const*> EleUVs = lLayer->GetUVSets();
	//					for (size_t FbxUVIndex = 0; FbxUVIndex < UVSetCount; FbxUVIndex++)
	//					{
	//						FbxLayerElementUV const* ElementUV = EleUVs[FbxUVIndex];
	//						if (ElementUV)
	//						{
	//							const char* UVSetName = ElementUV->GetName();
	//							std::string LocalUVSetName = UVSetName;
	//							if (0 == LocalUVSetName.size())
	//							{
	//								LocalUVSetName = "UVmap_" + std::to_string(UVLayerIndex);
	//							}
	//							if (LocalUVSetName == UVVectors[UVIndex])
	//							{
	//								LayerElementUV[UVIndex] = ElementUV;
	//								UVReferenceMode[UVIndex] = ElementUV->GetReferenceMode();
	//								UVMappingMode[UVIndex] = ElementUV->GetMappingMode();
	//								break;
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}

	//		//if (UniqueUVCount > 8)
	//		//{
	//		//	UInterchangeResultMeshWarning_TooManyUVs* Message = MeshDescriptionImporter.AddMessage<UInterchangeResultMeshWarning_TooManyUVs>(Mesh);
	//		//	Message->ExcessUVs = UniqueUVCount - 8;
	//		//}

	//		// UniqueUVCount = UniqueUVCount; // 8이상이 될수 없다.

	//		if (UniqueUVCount >= 8)
	//		{
	//			GameEngineDebug::AssertFalse();
	//		}
	//	}
	//}



	MeshInfos;
	RenderUnitInfos;
	int a = 0;

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