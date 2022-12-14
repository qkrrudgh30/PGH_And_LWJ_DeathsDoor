

#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TowerBossUI : public GameEngineActor
{
public:
	// constrcuter destructer
	TowerBossUI();
	~TowerBossUI();

	// delete Function
	TowerBossUI(const TowerBossUI& _Other) = delete;
	TowerBossUI(TowerBossUI&& _Other) noexcept = delete;
	TowerBossUI& operator=(const TowerBossUI& _Other) = delete;
	TowerBossUI& operator=(TowerBossUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	std::shared_ptr <GameEngineUIRenderer> RendererButton1;
	std::shared_ptr <GameEngineUIRenderer> RendererButton2;


public:

	bool m_bStartCheck = false;

	bool m_bButtoncheck = false;;

	//float4 m_fPlayPos2 = {};
	//float4 m_fPlayPos1 = {};
	//float4 m_fEditPos1 = {};
	//float4 m_fEditPos2 = {};

	float TimeAngle = 0.f;
};

