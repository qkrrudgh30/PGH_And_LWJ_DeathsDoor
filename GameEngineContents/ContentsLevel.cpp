#include "PreCompile.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineCore/GameEngineFBXStaticRenderer.h"

#include "ContentsLevel.h"
#include "EditGUIWindow.h"
#include "StaticMesh.h"
#include "LoadingUI.h"

#include <filesystem>
#include <fstream>

std::atomic<unsigned int> ContentsLevel::muFBXLoadedCount = 0;
std::vector<std::string> ContentsLevel::mstrvecAllResourceNames;
std::string ContentsLevel::mstrNextLevelName;
std::string ContentsLevel::mstrPrevLevelName;
std::map<std::string, bool> ContentsLevel::mmapPrimitiveInitialized;

enum { eWaiting = -1 };

// #define MT
#define NMT

ContentsLevel::ContentsLevel()	
	: mpLoadingUI(nullptr)
	, muAllResourcesCount(0u)
	, muAllAnimatorCount(0u)
	, muAllStaticCount(0u)
	, muAllAnimationCount(0u)
	, muMyThreadCount(0u)
	, muLines(0u)
	, muRemains(0u)
	, muAnimationStartIndex(0u)
	, mstrvecAllResourcePaths()
{
	mvecDirectories.reserve(64u);
	mstrvecAnimatorMeshFileNames.reserve(64u);
	mstrvecAnimatorMeshFileNamesForEdit.reserve(64u);
	mstrvecStaticMeshFileNames.reserve(64u);
	mstrvecStaticMeshFileNamesForEdit.reserve(64u);
	mstrvecAnimationFileNames.reserve(64u);
	mstrvecAllResourceNames.reserve(64u);
	mstrvecAllResourcePaths.reserve(64u);
	mstrvecAllResourcePaths.reserve(64u);

	// GameEngineFBX::CreateManager();
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::PlacePathOn(const std::string& _strFolderName)
{
	mvecDirectories.clear();

	GameEngineDirectory tempDir;
	tempDir.MoveParentToExitsChildDirectory("ContentsResources");
	tempDir.Move("ContentsResources");
	tempDir.Move("Asset");
	tempDir.Move(_strFolderName);

	std::vector<GameEngineDirectory> vOuterDirectories = tempDir.GetAllDirectory();
	int uOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	mvecDirectories.reserve(uOuterDirectoriesCount);
	for (int i = 0; i < uOuterDirectoriesCount; ++i)
	{
		mvecDirectories.push_back(vOuterDirectories[i]);
	}
}

void ContentsLevel::LoadFBXFiles()
{
	mstrvecAllResourceNames.clear();
	mstrvecAllResourcePaths.clear();
	muAllResourcesCount = 0u;
	// muMyThreadCount = GameEngineCore::EngineThreadPool.GetMyThreadCount();
	muMyThreadCount = 6u;

	LoadFBXMesiesOfAnimator();
	LoadFBXMesiesOfStatic();
	LoadAnimationsOfAnimator();

	LoadResources2();
}

void ContentsLevel::LoadCreaturesFromFile(const std::string& _strFolderName)
{
	GameEngineDirectory tempDir;
	tempDir.MoveParentToExitsChildDirectory("ContentsResources");
	tempDir.Move("ContentsResources");
	tempDir.Move("Asset");
	tempDir.Move(_strFolderName);

	std::filesystem::path p(tempDir.PlusFilePath(_strFolderName + ".txt"));

	std::ifstream fin;
	fin.open(p);

	int uCount = 0;

	fin >> uCount;

	std::string strName;
	float4 f4Scale, f4Rotation, f4Position;
	float4 f4ColliderScale, f4ColliderRotation, f4ColliderPosition;
	for (int i = 0; i < uCount; ++i)
	{
		fin >> strName
			>> f4Scale.x >> f4Scale.y >> f4Scale.z
			>> f4Rotation.x >> f4Rotation.y >> f4Rotation.z
			>> f4Position.x >> f4Position.y >> f4Position.z
			>> f4ColliderScale.x >> f4ColliderScale.y >> f4ColliderScale.z
			>> f4ColliderRotation.x >> f4ColliderRotation.y >> f4ColliderRotation.z
			>> f4ColliderPosition.x >> f4ColliderPosition.y >> f4ColliderPosition.z;

		std::weak_ptr<StaticMesh> temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
		temp.lock()->SetPriorityInitialize();
		if ("Collider" != strName)
		{
			temp.lock()->GetFBXRenderer()->SetFBXMesh(strName + ".fbx", "Texture");
		}
		temp.lock()->GetTransform().SetLocalScale(f4Scale);
		temp.lock()->GetTransform().SetLocalRotate(f4Rotation);
		temp.lock()->GetTransform().SetLocalPosition(f4Position);

		temp.lock()->GetCollider()->GetTransform().SetLocalScale(f4ColliderScale);
		temp.lock()->GetCollider()->GetTransform().SetLocalRotation(f4ColliderRotation);
		temp.lock()->GetCollider()->GetTransform().SetLocalPosition(f4ColliderPosition);

		std::string strCurrLevelName = GEngine::GetCurrentLevel()->GetNameCopy();
		EditGUIWindow::GetCreatureMap()[strCurrLevelName].push_back(make_pair(strName, temp));
	}

	fin.close();
}

void ContentsLevel::LoadFBXMesiesOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	muAllAnimatorCount = uOuterDirectoriesCount;
	muAllResourcesCount += uOuterDirectoriesCount;
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetMyThreadCount();
	size_t uThreadCount = 6u;
	size_t uLines = static_cast<size_t>(uOuterDirectoriesCount / uThreadCount);
	size_t uRemains = uOuterDirectoriesCount % uThreadCount;
	muFBXLoadedCount = 0u;

	mstrvecAnimatorMeshFileNames.clear();
	mstrvecAnimatorMeshFileNames.reserve(uOuterDirectoriesCount);
	mstrvecAnimatorMeshFileNamesForEdit.clear();
	mstrvecAnimatorMeshFileNamesForEdit.reserve(uOuterDirectoriesCount);
	for (size_t i = 0; i < uOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecAnimatorMeshFileNamesForEdit.push_back(strTemp);
		mstrvecAllResourceNames.push_back(strTemp);
		mstrvecAnimatorMeshFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		mstrvecAllResourcePaths.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

	LoadingUI::mbIsFirstLoadingStage = true;

}

void ContentsLevel::LoadFBXMesiesOfStatic()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eStaticDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	muAllStaticCount = uOuterDirectoriesCount;
	muAllResourcesCount += uOuterDirectoriesCount;
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetMyThreadCount();
	size_t uThreadCount = 6u;
	size_t uLines = static_cast<size_t>(uOuterDirectoriesCount / uThreadCount);
	size_t uRemains = uOuterDirectoriesCount % uThreadCount;
	muFBXLoadedCount = 0u;

	mstrvecStaticMeshFileNames.clear();
	mstrvecStaticMeshFileNames.reserve(uOuterDirectoriesCount);
	mstrvecStaticMeshFileNamesForEdit.clear();
	mstrvecStaticMeshFileNamesForEdit.reserve(uOuterDirectoriesCount);
	for (size_t i = 0; i < uOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecStaticMeshFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		mstrvecStaticMeshFileNamesForEdit.push_back(strTemp);
		mstrvecAllResourceNames.push_back(strTemp);
		mstrvecAllResourcePaths.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

	LoadingUI::mbIsFirstLoadingStage = false;

}

void ContentsLevel::LoadAnimationsOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimationDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	muAllAnimationCount = uOuterDirectoriesCount;
	muAnimationStartIndex = muAllResourcesCount;
	muAllResourcesCount += uOuterDirectoriesCount;
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetMyThreadCount();
	size_t uThreadCount = 6u;
	size_t uLines = static_cast<size_t>(uOuterDirectoriesCount / uThreadCount);
	size_t uRemains = uOuterDirectoriesCount % uThreadCount;
	muFBXLoadedCount = 0u;

	mstrvecAnimationFileNames.clear();
	mstrvecAnimationFileNames.reserve(uOuterDirectoriesCount);
	for (size_t i = 0; i < uOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecAnimationFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		mstrvecAllResourcePaths.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

}

void ContentsLevel::LoadResources()
{
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	muMyThreadCount = 6u;
	muLines = static_cast<size_t>(muAllResourcesCount / muMyThreadCount);
	muRemains = muAllResourcesCount % muMyThreadCount;
	muFBXLoadedCount = 0u;

	size_t i = 0, j = 0, k = 0, l = 0;
	for (i = 0; i < muLines; ++i) // 여러 줄인 경우, 딱 uLines * uThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (j = 0; j < muMyThreadCount; ++j)
		{
			l = i * muMyThreadCount + j;
			if (l < muAnimationStartIndex)
			{
				if (l < muAllAnimatorCount)
				{
					EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAllResourceNames[l]);
				}
				else
				{
					EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecAllResourceNames[l]);
				}

				GameEngineCore::EngineThreadPool.Work(
					[=]
					{
						std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(mstrvecAllResourcePaths[l]);
						mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
					});
			}
			else
			{
				GameEngineCore::EngineThreadPool.Work(
					[=]
					{
						//GameEngineFBXAnimation* Mesh = GameEngineFBXAnimation::Load(mstrvecAllResourcePaths[l]);
						mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
					});
			}
		}
	}

	if (0 != muRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (k = 0; k < muRemains; ++k)
		{
			l = i * muMyThreadCount + k;
			if (i * muMyThreadCount + k < muAnimationStartIndex)
			{
				if (l < muAllAnimatorCount)
				{
					EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAllResourceNames[l]);
				}
				else
				{
					EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecAllResourceNames[l]);
				}

				GameEngineCore::EngineThreadPool.Work(
					[=]
					{
						std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(mstrvecAllResourcePaths[l]);
						mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
					});
			}
			else
			{
				GameEngineCore::EngineThreadPool.Work(
					[=]
					{
						//GameEngineFBXAnimation* Mesh = GameEngineFBXAnimation::Load(mstrvecAllResourcePaths[l]);
						mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
					});
			}
		}
	}

}

void ContentsLevel::LoadResources2()
{
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	muMyThreadCount = 6u;
	muLines = static_cast<size_t>(muAllResourcesCount / muMyThreadCount);
	muRemains = muAllResourcesCount % muMyThreadCount;
	muFBXLoadedCount = 0u;

	size_t i = 0, j = 0, k = 0, l = 0;
	for (i = 0; i < muLines; ++i) // 여러 줄인 경우, 딱 uLines * uThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (j = 0; j < muMyThreadCount; ++j)
		{
			l = i * muMyThreadCount + j;
			
			if (l < muAnimationStartIndex)
			{
				if ("Collider" != mstrvecAllResourceNames[l])
				{
					std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(mstrvecAllResourcePaths[l]);
				}
				mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
				if (l < muAllAnimatorCount)
				{
					EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAllResourceNames[l]);
				}
				else
				{
					EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecAllResourceNames[l]);
				}
			}
			else
			{
				std::shared_ptr<GameEngineFBXAnimation> Mesh = GameEngineFBXAnimation::Load(mstrvecAllResourcePaths[l]);
				mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
			}
		}
	}

	if (0 != muRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (k = 0; k < muRemains; ++k)
		{
			l = i * muMyThreadCount + k;
			
			if (i * muMyThreadCount + k < muAnimationStartIndex)
			{
				if ("Collider" != mstrvecAllResourceNames[l])
				{
					std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(mstrvecAllResourcePaths[l]);
				}
				mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
				if (l < muAllAnimatorCount)
				{
					EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAllResourceNames[l]);
				}
				else
				{
					EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecAllResourceNames[l]);
				}
				
			}
			else
			{
				std::shared_ptr<GameEngineFBXAnimation> Mesh = GameEngineFBXAnimation::Load(mstrvecAllResourcePaths[l]);
				mpLoadingUI->SetProgressAmount(muAllResourcesCount, ++muFBXLoadedCount);
			}
		}
	}
}
