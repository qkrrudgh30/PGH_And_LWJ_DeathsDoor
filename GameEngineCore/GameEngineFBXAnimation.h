#pragma once
#include "GameEngineRes.h"
#include <GameEngineCore/GameEngineFBX.h>



class FbxExBoneFrameData : public GameEngineSerializer
{
public:
	float4 S; // 크
	float4 Q; // 자
	float4 T; // 이
	double Time;
	float4x4 FrameMat;

	fbxsdk::FbxAMatrix GlobalAnimation;
	fbxsdk::FbxAMatrix LocalAnimation;

	FbxExBoneFrameData() {

	}

	void Write(GameEngineFile& _File) override
	{
		_File.Write(S);
		_File.Write(Q);
		_File.Write(T);
		_File.Write(Time);
		_File.Write(FrameMat);
		_File.Write(GlobalAnimation);
		_File.Write(LocalAnimation);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(S);
		_File.Read(Q);
		_File.Read(T);
		_File.Read(Time);
		_File.Read(FrameMat);
		_File.Read(GlobalAnimation);
		_File.Read(LocalAnimation);
	}

};

class FbxExBoneFrame : public GameEngineSerializer
{
public:
	int BoneIndex;
	int BoneParentIndex;

	// 120프레임이야.
	std::vector<FbxExBoneFrameData> BoneMatData;

	FbxExBoneFrame() {

	}

	void Write(GameEngineFile& _File) override
	{
		_File.Write(BoneIndex);
		_File.Write(BoneParentIndex);
		_File.Write(BoneMatData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(BoneIndex);
		_File.Read(BoneParentIndex);
		_File.Read(BoneMatData);
	}
};

// Take 001이라는 애니메이션이 있는데.
class FbxExAniData : public GameEngineSerializer
{
public:
	std::string				AniName;
	fbxsdk::FbxTime			StartTime; // 설정된 애니메이션 시간
	fbxsdk::FbxTime			EndTime; // 
	fbxsdk::FbxLongLong		TimeStartCount; 
	fbxsdk::FbxLongLong		TimeEndCount; // 1414
	fbxsdk::FbxLongLong		FrameCount;
	fbxsdk::FbxTime::EMode	TimeMode;
	__int64					FbxModeCount;
	double					FbxModeRate;

	// 0~100
	// meshInfo 1개 상체 20
	// meshInfo 1개 하체
	// meshInfo 1개 전신 20
	std::map<size_t, std::vector<FbxExBoneFrame>> AniFrameData;

	void Write(GameEngineFile& _File) override
	{
		_File.Write(AniName);
		_File.Write(StartTime);
		_File.Write(EndTime);
		_File.Write(TimeStartCount);
		_File.Write(TimeEndCount);
		_File.Write(FrameCount);
		_File.Write(TimeMode);
		_File.Write(FbxModeCount);
		_File.Write(FbxModeRate);
		_File.Write(AniFrameData);
	}

	void Read(GameEngineFile& _File) override
	{
		_File.Read(AniName);
		_File.Read(StartTime);
		_File.Read(EndTime);
		_File.Read(TimeStartCount);
		_File.Read(TimeEndCount);
		_File.Read(FrameCount);
		_File.Read(TimeMode);
		_File.Read(FbxModeCount);
		_File.Read(FbxModeRate);
		_File.Read(AniFrameData);
	}


public:
	float FrameTime(int _Frame)
	{
		fbxsdk::FbxTime tTime = {};
		tTime.SetFrame(_Frame, TimeMode);

		return (float)tTime.GetSecondDouble();
	}

public:
	__int64 FrameModeRateInt()
	{
		return static_cast<__int64>(fbxsdk::FbxGetFrameRate(TimeMode));
	}
	double FrameModeRateDouble()
	{
		return fbxsdk::FbxGetFrameRate(TimeMode);
	}

	float FrameModeRateFloat()
	{
		return static_cast<float>(fbxsdk::FbxGetFrameRate(TimeMode));
	}


public:
	FbxExAniData() : AniName(""), StartTime(0), EndTime(0), TimeStartCount(0), TimeEndCount(0), FrameCount(0), FbxModeCount(0), FbxModeRate(0.0), TimeMode()
	{}
	~FbxExAniData() {}
};

// 설명 :
class GameEngineFBXMesh;
class GameEngineFBXAnimationRenderer;
class GameEngineFBXAnimation : public GameEngineFBX, public GameEngineRes<GameEngineFBXAnimation>
{
public:
	// constrcuter destructer
	GameEngineFBXAnimation();
	~GameEngineFBXAnimation();

	// delete Function
	GameEngineFBXAnimation(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation(GameEngineFBXAnimation&& _Other) noexcept = delete;
	GameEngineFBXAnimation& operator=(const GameEngineFBXAnimation& _Other) = delete;
	GameEngineFBXAnimation& operator=(GameEngineFBXAnimation&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path)
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static std::shared_ptr<GameEngineFBXAnimation> Load(const std::string& _Path, const std::string& _Name);

	// 애니메이션 프레임 행렬계산.
	// 여기서 프레임의 의미는 Animation TimeEndCount - TimeStartCount
	void AnimationMatrixLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, const std::string_view& _Name, int _AnimationIndex);

	FbxExAniData* GetAnimationData(int _Index)
	{
		if (AnimationDatas.size() <= _Index)
		{
			MsgBoxAssert("애니메이션 데이터 범위를 넘어섰습니다");
		}

		return &AnimationDatas[_Index];
	}

	void UserLoad(const std::string_view& _Path/*GameEngineFile& _File*/);
	void UserSave(const std::string_view& _Path/*GameEngineFile& _File*/);

protected:
	void LoadMesh(const std::string& _Path, const std::string& _Name);

	// 애니메이션은 노드의 어트리뷰트가 다 eMesh인 녀석에게 들어있으므로 그녀석에게서 애니메이션 로드 함수를 실행시키는 역할을 한다.
	void ProcessAnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* pNode, int _index);
	bool AnimationLoad(std::shared_ptr <GameEngineFBXMesh> _Mesh, fbxsdk::FbxNode* _Node, int AnimationIndex);
	void ProcessAnimationCheckState(std::shared_ptr <GameEngineFBXMesh> _Fbx, int userAniDataIndex);
	fbxsdk::FbxAMatrix GetGeometryTransformation(fbxsdk::FbxNode* pNode);

	// 런
	// 아이들
	// 어택
	std::vector<FbxExAniData> AnimationDatas;

private:
	bool CheckAnimation();

};

