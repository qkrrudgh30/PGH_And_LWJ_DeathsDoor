

#pragma once
#include <GameEngineCore/CoreMinimal.h>

#include "UnitBase.h"

// Ό³Έν :

class BillboardRenderer;
class TsetBackGround : public UnitBase
{
public:
	// constrcuter destructer
	TsetBackGround();
	~TsetBackGround();

	// delete Function
	TsetBackGround(const TsetBackGround& _Other) = delete;
	TsetBackGround(TsetBackGround&& _Other) noexcept = delete;
	TsetBackGround& operator=(const TsetBackGround& _Other) = delete;
	TsetBackGround& operator=(TsetBackGround&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:
	std::shared_ptr<BillboardRenderer> sptrTestPicture;



//	std::shared_ptr<BillboardRenderer> Star1;
public:
	float m_fDownSpeed = 0.f;
	float m_fEffTime = 0.1f;
};

