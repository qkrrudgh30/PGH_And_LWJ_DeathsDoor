

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :

class BillboardRenderer;
class TestFog : public UnitBase
{
public:
	// constrcuter destructer
	TestFog();
	~TestFog();

	// delete Function
	TestFog(const TestFog& _Other) = delete;
	TestFog(TestFog&& _Other) noexcept = delete;
	TestFog& operator=(const TestFog& _Other) = delete;
	TestFog& operator=(TestFog&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
//	std::shared_ptr<BillboardRenderer> sptrTestPicture;
	std::shared_ptr <GameEngineUIRenderer> FogRender;
	std::shared_ptr <GameEngineUIRenderer> FogRender2;
public:
	float4 StartPos1 = {};
	float4 StartPos2 = {};
	float m_fEffTime = 0.1f;
};

