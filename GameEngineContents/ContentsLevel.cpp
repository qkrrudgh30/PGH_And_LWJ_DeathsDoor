#include "PreCompile.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineCore/GameEngineFBXStaticRenderer.h"

#include "ContentsLevel.h"
#include "EditGUIWindow.h"
#include "StaticMesh.h"

#include <filesystem>
#include <fstream>

std::atomic<int> ContentsLevel::muFBXFolderCount = 0;

ContentsLevel::ContentsLevel()	
	: mbPrimitiveInitialized(false)
{
}

ContentsLevel::~ContentsLevel() 
{
}

void ContentsLevel::DirectPathAt(const std::string& _strFolderName)
{
	GameEngineDirectory tempDir;
	tempDir.MoveParentToExitsChildDirectory("ContentsResources");
	tempDir.Move("ContentsResources");
	tempDir.Move("Texture");
	tempDir.Move(_strFolderName);

	std::vector<GameEngineDirectory> vOuterDirectories = tempDir.GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	mvecDirectories.reserve(iOuterDirectoriesCount);
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		mvecDirectories.push_back(vOuterDirectories[i]);
	}
}

void ContentsLevel::LoadFBXFiles()
{
	LoadFBXMesiesOfAnimator();
	LoadFBXMesiesOfStatic();
	// LoadAnimationsOfAnimator();
}

void ContentsLevel::LoadTextureInAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	GameEngineDirectory actorDir;
	
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		actorDir.Move(vOuterDirectories[i].GetFullPath());
		// std::lock_guard<std::mutex> LockInst(m);
		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		actorDir.Move("..\\");
		++muFBXFolderCount;
	}
}

void ContentsLevel::LoadTextureInStatic()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eStaticDir].GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	GameEngineDirectory mapDir;
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mapDir.Move(vOuterDirectories[i].GetFullPath());
		// std::lock_guard<std::mutex> LockInst(m);
		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		mapDir.Move("..\\");
		++muFBXFolderCount;
	}
}

void ContentsLevel::LoadCreaturesFromFile(const std::string& _strFolderName)
{
	GameEngineDirectory tempDir;
	tempDir.MoveParentToExitsChildDirectory("ContentsResources");
	tempDir.Move("ContentsResources");
	tempDir.Move("Texture");
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
	}
}

void ContentsLevel::LoadFBXMesiesOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	// int iThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	int iThreadCount = 6;
	int iLines = iOuterDirectoriesCount / iThreadCount;
	int iRemains = iOuterDirectoriesCount % iThreadCount;

	// Create FileNames From Path.
	// mapDir.Move(vOuterDirectories[i].GetFullPath());
	// 매 순회마다 strTemp가 변경되는 듯함.. -> 멀티 스레딩시 경로가 계속 변경됨.
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecAnimatorMeshFileNamesForEdit.push_back(strTemp);
		mstrvecAnimatorMeshFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));

	}

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때

	GameEngineDirectory mapDir;
	for (int i = 0; i < iLines; ++i) // 여러 줄인 경우, 딱 iLines * iThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (int j = 0; j < iThreadCount; ++j)
		{
			//GameEngineCore::EngineThreadPool.Work(
			//	[&]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * iThreadCount + j]);
			//		++muFBXFolderCount;
			//	});

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * iThreadCount + j]);
			EditGUIWindow::GetLoadedFromAnimatorVector().push_back(mstrvecAnimatorMeshFileNamesForEdit[i * iThreadCount + j]);
		}
	}

	if (0 != iRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (int i = 0; i < iRemains; ++i)
		{

			//GameEngineCore::EngineThreadPool.Work(
			//	[=]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i]);
			//		++muFBXFolderCount;
			//	});

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i]);
			EditGUIWindow::GetLoadedFromAnimatorVector().push_back(mstrvecAnimatorMeshFileNamesForEdit[i]);
		}
	}
}

void ContentsLevel::LoadFBXMesiesOfStatic()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eStaticDir].GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	// int iThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	int iThreadCount = 6;
	int iLines = iOuterDirectoriesCount / iThreadCount;
	int iRemains = iOuterDirectoriesCount % iThreadCount;

	// Create FileNames From Path.
	// mapDir.Move(vOuterDirectories[i].GetFullPath());
	// 매 순회마다 strTemp가 변경되는 듯함.. -> 멀티 스레딩시 경로가 계속 변경됨.
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecStaticMeshFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
		mstrvecStaticMeshFileNamesForEdit.push_back(strTemp);
	}

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때

	GameEngineDirectory mapDir;
	for (int i = 0; i < iLines; ++i) // 여러 줄인 경우, 딱 iLines * iThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (int j = 0; j < iThreadCount; ++j)
		{
			//GameEngineCore::EngineThreadPool.Work(
			//	[&]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * iThreadCount + j]);
			//		++muFBXFolderCount;
			//	});

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i * iThreadCount + j]);
			EditGUIWindow::GetLoadedFromStaticVector().push_back(mstrvecStaticMeshFileNamesForEdit[i * iThreadCount + j]);
		}
	}

	if (0 != iRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (int i = 0; i < iRemains; ++i)
		{

			//GameEngineCore::EngineThreadPool.Work(
			//	[=]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i]);
			//		++muFBXFolderCount;
			//	});

			GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecStaticMeshFileNames[i]);
			EditGUIWindow::GetLoadedFromStaticVector().push_back(mstrvecStaticMeshFileNamesForEdit[i]);
		}
	}
}

void ContentsLevel::LoadAnimationsOfAnimator()
{
	std::vector<GameEngineDirectory> vOuterDirectories = mvecDirectories[eAnimatorDir].GetAllDirectory();
	int iOuterDirectoriesCount = static_cast<int>(vOuterDirectories.size());
	// int iThreadCount = GameEngineCore::EngineThreadPool.GetThreadCount();
	int iThreadCount = 6;
	int iLines = iOuterDirectoriesCount / iThreadCount;
	int iRemains = iOuterDirectoriesCount % iThreadCount;

	// Create FileNames From Path.
	// mapDir.Move(vOuterDirectories[i].GetFullPath());
	// 매 순회마다 strTemp가 변경되는 듯함.. -> 멀티 스레딩시 경로가 계속 변경됨.
	for (int i = 0; i < iOuterDirectoriesCount; ++i)
	{
		std::string strTemp = vOuterDirectories[i].GetFileName();
		mstrvecAnimationFileNames.push_back(vOuterDirectories[i].PlusFilePath(strTemp + ".FBX"));
	}

	// 1줄도 안될 때
	// 여러 줄 인데, 나누어 떨어질때
	// 여러 줄 인데, 나누어 떨어지지 않을때

	GameEngineDirectory mapDir;
	for (int i = 0; i < iLines; ++i) // 여러 줄인 경우, 딱 iLines * iThreadCount 까지만 순회. 1줄도 안되는 경우엔 자동으로 넘어가게끔. 
	{
		for (int j = 0; j < iThreadCount; ++j)
		{
			//GameEngineCore::EngineThreadPool.Work(
			//	[&]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh* Mesh = GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i * iThreadCount + j]);
			//		++muFBXFolderCount;
			//	});
			GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Load(mstrvecAnimationFileNames[i * iThreadCount + j]);
		}
	}

	if (0 != iRemains) // 1줄도 안되는 경우와 여러 줄이지만 여분의 FBX 폴더가 있는 경우.
	{
		for (int i = 0; i < iRemains; ++i)
		{

			//GameEngineCore::EngineThreadPool.Work(
			//	[=]
			//	{
			//		// std::lock_guard<std::mutex> LockInst(m);
			//		GameEngineFBXMesh::Load(mstrvecAnimatorMeshFileNames[i]);
			//		++muFBXFolderCount;
			//	});

			GameEngineFBXAnimation* Animation = GameEngineFBXAnimation::Load(mstrvecAnimationFileNames[i]);
		}
	}
}
