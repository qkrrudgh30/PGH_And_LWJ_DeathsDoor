#pragma once
#include "GameEngineTexture.h"
#include <vector>
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineRenderer.h"

// Setting 이제부터 여기그려라.

// Copy(수정본) 이 함수를 호출한 랜더타겟의 내용을 모두 지우고 수정본의 내용을 복사해라.

// Merge(수정본, 블랜드) 이 함수를 호출한 랜더타겟 위에 수정보느이 내용을 덮어 씌워라.

// Effect() 이 랜더타겟에 무언가 효과를 줘.

// Cameras;
// 플레이 카메라
// UI 카메라

// 랜더링 구조
// 플레이 카메라 => 플레이 랜더타겟 세팅
//    주인공 배경맵

// 포스트 이펙트라고 합니다.

// UI 카메라 => UI 랜더타겟 세팅
//    인벤토리 버튼 뭐시기 

// 흐려져라. 포스트 이펙트라고 합니다.

// 백버퍼 랜더타겟->Merge(플레이 랜더타겟)
// 백버퍼 랜더타겟->Merge(UI 랜더타겟)

// 디바이스에 있는 백버퍼 랜더타겟

class GameEnginePostEffect
{
private:
	bool IsUpdate_ = true;

public:
	bool IsUpdate() 
	{
		return IsUpdate_;
	}

	virtual void On()
	{
		IsUpdate_ = true;
	}

	virtual void Off()
	{
		IsUpdate_ = false;
	}

public:
	virtual void EffectInit() = 0;
	virtual void Effect(class GameEngineRenderTarget* _Render) = 0;

	virtual ~GameEnginePostEffect() 
	{

	}
};

// 설명 :
class GameEngineStatusWindow;
class GameEngineDepthStencilTexture;
class GameEngineRenderTarget : public GameEngineRes <GameEngineRenderTarget>
{
	friend GameEngineStatusWindow;

public:
	static ID3D11RenderTargetView* PrevRenderTargetViews;
	static ID3D11DepthStencilView* PrevDepthStencilView;

	static void GetPrevRenderTarget();
	static void SetPrevRenderTarget();

public:
	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static GameEngineRenderTarget* Create(const std::string& _Name);

	static GameEngineRenderTarget* Create();

	void CreateRenderTargetTexture(ID3D11Texture2D* _Texture, float4 _Color);

	void CreateRenderTargetTexture(float4 _Size, float4 _Color);

	void CreateRenderTargetTexture(float4 _Size, DXGI_FORMAT _Format, float4 _Color);

	// 직접 텍스처를 만들어내는 기능
	void CreateRenderTargetTexture(D3D11_TEXTURE2D_DESC _Data, float4 _Color);

	void CreateRenderTargetTexture(GameEngineTexture* _Texture, float4 _Color);

	void SettingDepthTexture(GameEngineTexture* _Texture);

	void Clear();

	void Setting();

	void CreateDepthTexture(int _Index = 0);

	inline GameEngineTexture* GetDepthTexture() 
	{
		return DepthTexture;
	}

	GameEngineTexture* GetRenderTargetTexture(size_t _Index);

	void Copy(GameEngineRenderTarget* _Other, int _Index = 0);

	void Merge(GameEngineRenderTarget* _Other, int _Index = 0);
	
	void Effect(GameEngineRenderingPipeLine* _Other, GameEngineShaderResourcesHelper* _ShaderResourcesHelper);

	void Effect(class GameEngineRenderSet& _RenderSet);

	void EffectProcess();


protected:
	std::vector<GameEngineTexture*> RenderTargets;
	std::vector<ID3D11RenderTargetView*> RenderTargetViews;
	std::vector<ID3D11ShaderResourceView*> ShaderResourceViews;
	std::vector<float4> ClearColors;

	// std::vector<ID3D11RenderTargetView*> RenderTargetViews;

	ID3D11DepthStencilView* DepthStencilView;

	GameEngineShaderResourcesHelper MergeShaderResourcesHelper;
	GameEngineRenderingPipeLine* MergePipeLine;

	GameEngineTexture* DepthTexture;

	// Post이펙트 부분
private:
	std::list<GameEnginePostEffect*> Effects;

public:
	template<typename EffectType>
	EffectType* AddEffect()
	{
		GameEnginePostEffect* NewEffect = new EffectType();
		NewEffect->EffectInit();
		Effects.push_back(NewEffect);

		return reinterpret_cast<EffectType*>(NewEffect);
	}
};

