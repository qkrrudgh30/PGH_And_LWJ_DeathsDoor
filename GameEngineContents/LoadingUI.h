#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum
{
	eAnimatorMesh,
	eStaticMesh,
	eAnimation,
	eEndStage,
};

// 설명 :
class LoadingUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LoadingUI();
	~LoadingUI();

	// delete Function
	LoadingUI(const LoadingUI& _Other) = delete;
	LoadingUI(LoadingUI&& _Other) noexcept = delete;
	LoadingUI& operator=(const LoadingUI& _Other) = delete;
	LoadingUI& operator=(LoadingUI&& _Other) noexcept = delete;

	void SetProgressAmount(size_t _uTotalCountOfResources, size_t _uCurrentCountOfLoadedResources) 
	{
		if (-1 != _uTotalCountOfResources) // 해당 로딩 스테이지의 로딩이 완료 되지 않았을 때
		{ 
			if (false == mbIsFirstLoadingStage && 1 == _uCurrentCountOfLoadedResources) 
			{ // 다음 단계의 첫 번째 로딩이 완료되었을 때. 0%부터 차오르게끔 하기 위함.
				++muCurrLoadingStage;
				mfSrcProgressAmount = 0.f;
			}
			muTotalCountOfResources = _uTotalCountOfResources;
			muCurrentCountOfLoadedResources = _uCurrentCountOfLoadedResources;
			mfDstProgressAmount = (static_cast<float>(muCurrentCountOfLoadedResources)) / muTotalCountOfResources;
		}
		else 
		{ // 해당 로딩 스테이지의 로딩이 완료 되었을 때. 100%까지는 Progress bar가 차오르게끔 하기 위함.
			return;
		}
	}

	static bool mbIsFirstLoadingStage;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineUIRenderer* mpUIRendererForBackground;
	GameEngineUIRenderer* mpUIRendererForProgressBar;
	
	size_t muTotalCountOfResources;
	size_t muCurrentCountOfLoadedResources;

	float mfCrrProgressState;
	float mfDstProgressAmount;
	float mfSrcProgressAmount;
	size_t muCurrLoadingStage;
	size_t muPrevLoadingStage;

};

