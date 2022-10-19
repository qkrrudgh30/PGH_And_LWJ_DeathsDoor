#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class LoginUI : public GameEngineActor
{
public:
	// constrcuter destructer
	LoginUI();
	~LoginUI();

	// delete Function
	LoginUI(const LoginUI& _Other) = delete;
	LoginUI(LoginUI&& _Other) noexcept = delete;
	LoginUI& operator=(const LoginUI& _Other) = delete;
	LoginUI& operator=(LoginUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineUIRenderer* RendererButton1;
	GameEngineUIRenderer* RendererButton2;

	int m_ILevelType;
	int m_ILevelTypeCheck;

	bool m_bButtoncheck;

	float4 m_fPlayPos2;
	float4 m_fPlayPos1;
	float4 m_fEditPos1;
	float4 m_fEditPos2;


	GameEngineFontRenderer* FontPlay;
	GameEngineFontRenderer* FontEdit;
	float TimeAngle;
};

