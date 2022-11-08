#include "PreCompile.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineCore/GameEngineFBXStaticRenderer.h"
#include "GameEngineCore/GameEngineFBXMesh.h"

#include "ContentsLevel.h"
#include "EditGUIWindow.h"
#include "StaticMesh.h"
#include "LoadingUI.h"

#include <filesystem>
#include <fstream>

std::atomic<unsigned int> ContentsLevel::muFBXLoadedCount = 0;
std::string ContentsLevel::mstrNextLevelName;
std::string ContentsLevel::mstrPrevLevelName;
std::map<std::string, bool> ContentsLevel::mmapPrimitiveInitialized;

enum { eWaiting = -1 };

ContentsLevel::ContentsLevel()	
	: mbPrimitiveInitialized(false)
	, mpLoadingUI(nullptr)
{
	mvecDirectories.reserve(64u);
	mstrvecAnimatorMeshFileNames.reserve(64u);
	mstrvecAnimatorMeshFileNamesForEdit.reserve(64u);
	mstrvecStaticMeshFileNames.reserve(64u);
	mstrvecStaticMeshFileNamesForEdit.reserve(64u);
	mstrvecAnimationFileNames.reserve(64u);
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
	LoadFBXMesiesOfAnimator();
	LoadFBXMesiesOfStatic();
	LoadAnimationsOfAnimator();
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

		StaticMesh* temp = GEngine::GetCurrentLevel()->CreateActor<StaticMesh>();
		temp->SetPriorityInitialize();
		temp->GetFBXRenderer()->SetFBXMesh(strName + ".fbx", "Texture");
		temp->GetTransform().SetLocalScale(f4Scale);
		temp->GetTransform().SetLocalRotate(f4Rotation);
		temp->GetTransform().SetLocalPosition(f4Position);

		temp->GetCollider()->GetTransform().SetLocalScale(f4ColliderScale);
		temp->GetCollider()->GetTransform().SetLocalRotation(f4ColliderRotation);
		temp->GetCollider()->GetTransform().SetLocalPosition(f4ColliderPosition);

		std::string strCurrLevelName = GEngine::GetCurrentLevel()->GetNameCopy();
		EditGUIWindow::GetCreatureMap()[strCurrLevelName].push_back(make_pair(strName, temp));
		int a = 100;
	}
}

void ContentsLevel::LoadFBXMesiesOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
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
		mstrvecAnimatorMeshFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

	LoadingUI::mbIsFirstLoadingStage = true;

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때
	GameEngineDirectory mapDir;
	size_t i = 0, j = 0, k = 0;
	for (i = 0; i < uLines; ++i) // 여러 줄인 경우, 딱 uLines * uThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (j = 0; j < uThreadCount; ++j)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * uThreadCount + j]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * uThreadCount + j]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
			EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAnimatorMeshFileNamesForEdit[i * uThreadCount + j]);
		}
	}

	if (0 != uRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (k = 0; k < uRemains; ++k)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * uThreadCount + k]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * uThreadCount + k]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
			EditGUIWindow::GetLoadedFromAnimatorSet().insert(mstrvecAnimatorMeshFileNamesForEdit[i * uThreadCount + k]);
		}
	}

	if (0u == uLines && 0u == uRemains)
	{
		mpLoadingUI->SetProgressAmount(1, 1);
		return;
	}

	mpLoadingUI->SetProgressAmount(eWaiting, eWaiting);
}

void ContentsLevel::LoadFBXMesiesOfStatic()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eStaticDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	// size_t uThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
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
	}

	LoadingUI::mbIsFirstLoadingStage = false;

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때
	GameEngineDirectory mapDir;
	size_t i = 0, j = 0, k = 0;
	for (i = 0; i < uLines; ++i) // 여러 줄인 경우, 딱 uLines * uThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (j = 0; j < uThreadCount; ++j)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i * uThreadCount + j]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i * uThreadCount + j]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
			EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecStaticMeshFileNamesForEdit[i * uThreadCount + j]);
		}
	}

	if (0 != uRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (k = 0; k < uRemains; ++k)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i * uThreadCount + k]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i * uThreadCount + k]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
			EditGUIWindow::GetLoadedFromStaticSet().insert(mstrvecStaticMeshFileNamesForEdit[i * uThreadCount + k]);
		}
	}

	if (0u == uLines && 0u == uRemains)
	{
		mpLoadingUI->SetProgressAmount(1, 1);
		return;
	}

	mpLoadingUI->SetProgressAmount(eWaiting, eWaiting);
}

void ContentsLevel::LoadAnimationsOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	size_t uOuterDirectoriesCount = vOuterDirectories.size();
	// int uThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	size_t uThreadCount = 6;
	size_t uLines = static_cast<size_t>(uOuterDirectoriesCount / uThreadCount);
	size_t uRemains = uOuterDirectoriesCount % uThreadCount;
	muFBXLoadedCount = 0u;

	mstrvecAnimationFileNames.clear();
	mstrvecAnimationFileNames.reserve(uOuterDirectoriesCount);
	for (size_t i = 0; i < uOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecAnimationFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때

	GameEngineDirectory mapDir;
	size_t i = 0, j = 0, k = 0;
	for (i = 0; i < uLines; ++i) // 여러 줄인 경우, 딱 uLines * uThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (j = 0; j < uThreadCount; ++j)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimationFileNames[i * uThreadCount + j]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Load(mstrvecAnimationFileNames[i * uThreadCount + j]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
		}
	}

	if (0 != uRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (k = 0; k < uRemains; ++k)
		{
			/*GameEngineCore::EngineThreadPool.Work(
				[=]
				{
					GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * uThreadCount + k]);
					mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
				});*/

			GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Load(mstrvecAnimationFileNames[i * uThreadCount + k]);
			mpLoadingUI->SetProgressAmount(uOuterDirectoriesCount, ++muFBXLoadedCount);
		}
	}

	if (0u == uLines && 0u == uRemains)
	{
		mpLoadingUI->SetProgressAmount(1, 1);
		return;
	}

	mpLoadingUI->SetProgressAmount(eWaiting, eWaiting);
}
