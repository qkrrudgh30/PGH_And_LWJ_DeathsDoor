#pragma once
#include "GameEngineFBXRenderer.h"
#include "GameEngineFBXAnimation.h"
#include <map>

class FbxExAniData;
class GameEngineFBXMesh;
class GameEngineFBXAnimation;
class GameEngineFBXAnimationRenderer;
class FBXRendererAnimation : public std::enable_shared_from_this<FBXRendererAnimation>
{
public:
	GameEngineFBXAnimationRenderer* ParentRenderer;
	// SetFBX 본을 가지고 있는 매쉬
	GameEngineFBXMesh* Mesh;
	// 애니메이션을 가지고 있는 FBX
	GameEngineFBXAnimation* Aniamtion;
	FbxExAniData* FBXAnimationData;

	// 이 애니메이션이 현재까지 얼마나 지났나.
	float CurFrameTime;
	float FrameTime; // 0.1
	UINT CurFrame;
	UINT Start;
	UINT End;

	void Init(int _Index);
	void Reset();
	void Update(float _DeltaTime);

public:
	FBXRendererAnimation() 
		: CurFrameTime(0.0f)
		, FrameTime(0.0f) // 0.1
		, CurFrame(0)
		, Start(0)
		, End(0)
	{
		int a = 0;
	}

	~FBXRendererAnimation()
	{
		int a = 0;
	}
};

struct AnimationBoneData
{
public:
	int Index = -1;
	float4 Scale;
	float4 RotQuaternion;
	float4 Pos;
	float4 RotEuler;
};


// 설명 :
class GameEngineFBXAnimationRenderer : public GameEngineFBXRenderer
{
	friend FBXRendererAnimation;

public:
	// constrcuter destructer
	GameEngineFBXAnimationRenderer();
	~GameEngineFBXAnimationRenderer();

	// delete Function
	GameEngineFBXAnimationRenderer(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;
	GameEngineFBXAnimationRenderer& operator=(const GameEngineFBXAnimationRenderer& _Other) = delete;
	GameEngineFBXAnimationRenderer& operator=(GameEngineFBXAnimationRenderer&& _Other) noexcept = delete;

	void SetFBXMesh(const std::string& _Name, std::string _Material) override;
	GameEngineRenderUnit* SetFBXMesh(const std::string& _Name, std::string _Material, size_t _MeshIndex, size_t _SubSetIndex = 0) override;

	void CreateFBXAnimation(const std::string& _AnimationName, const std::string& _AnimationFBX, int _Index = 0);

	void ChangeAnimation(const std::string& _AnimationName);

	void Update(float _DeltaTime) override;

protected:

private:
	std::map<std::string, std::shared_ptr<FBXRendererAnimation>> Animations;
	std::shared_ptr<FBXRendererAnimation> CurAnimation;

	std::map<size_t, std::vector<float4x4>> AnimationBoneMatrixs;
	// std::map<size_t, std::vector<float4x4>> PrevAnimationBoneMatrixs;

	std::map<size_t, std::vector<AnimationBoneData>> AnimationBoneDatas;

};

