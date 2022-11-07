#include "PreCompile.h"
#include "GameEngineFBXAnimation.h"

GameEngineFBXAnimation::GameEngineFBXAnimation() 
{
}

GameEngineFBXAnimation::~GameEngineFBXAnimation() 
{
}


GameEngineFBXAnimation* GameEngineFBXAnimation::Load(const std::string& _Path, const std::string& _Name) 
{
	GameEngineFBXAnimation* NewRes = CreateResName(_Name);
	NewRes->SetPath(_Path);
	NewRes->LoadMesh(_Path, _Name);
	return NewRes;
}


void GameEngineFBXAnimation::LoadMesh(const std::string& _Path, const std::string& _Name)
{
	FBXInit(_Path);

	CheckAnimation();
	// 애니메이션이 존재한다 => 그걸로 아직 뭔가를 하지 않는다.

	AnimationDatas; // 3D 뷰어와 갯수가 달라도 어쩔 수 없음.
}

bool GameEngineFBXAnimation::CheckAnimation()
{
	std::string Path = GetPath();

	fbxsdk::FbxArray<FbxString*> AniNameArray;
	Scene->FillAnimStackNameArray(AniNameArray);

	if (0 == AniNameArray.Size())
	{
		return false;
	}

	AnimationDatas.resize(AniNameArray.Size());

	for (unsigned int i = 0; i < AnimationDatas.size(); i++)
	{
		AnimationDatas[i].AniName = GameEngineString::UTF8ToAnsiReturn(AniNameArray[i]->Buffer());

		FbxTakeInfo* TakeInfo = Scene->GetTakeInfo(AnimationDatas[i].AniName.c_str());
		AnimationDatas[i].StartTime = TakeInfo->mLocalTimeSpan.GetStart();
		AnimationDatas[i].EndTime = TakeInfo->mLocalTimeSpan.GetStop();
		AnimationDatas[i].TimeMode = Scene->GetGlobalSettings().GetTimeMode();
		AnimationDatas[i].TimeStartCount = AnimationDatas[i].StartTime.GetFrameCount(AnimationDatas[i].TimeMode);

		if (0 >= AnimationDatas[i].TimeStartCount)
		{
			AnimationDatas[i].TimeStartCount *= (FbxLongLong)-1;
		}

		AnimationDatas[i].TimeEndCount = AnimationDatas[i].EndTime.GetFrameCount(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FrameCount = AnimationDatas[i].TimeEndCount - AnimationDatas[i].TimeStartCount;

		AnimationDatas[i].FbxModeCount = (long long)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
		AnimationDatas[i].FbxModeRate = (double)fbxsdk::FbxTime::GetFrameRate(AnimationDatas[i].TimeMode);
	}

	for (int i = 0; i < AniNameArray.Size(); i++)
	{
		delete AniNameArray[i];
	}

	return true;
}