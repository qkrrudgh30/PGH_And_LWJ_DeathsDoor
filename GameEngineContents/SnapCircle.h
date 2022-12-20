#pragma once
#include "UnitBase.h"

// Ό³Έν :
class SnapCircle : public UnitBase
{
public:
	// constrcuter destructer
	SnapCircle();
	~SnapCircle();

	// delete Function
	SnapCircle(const SnapCircle& _Other) = delete;
	SnapCircle(SnapCircle&& _Other) noexcept = delete;
	SnapCircle& operator=(const SnapCircle& _Other) = delete;
	SnapCircle& operator=(SnapCircle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float m_fScale = 100.f;
	std::weak_ptr<class WaveRenderer> m_wptrWaveRenderer;
	CollisionReturn PlayerCollision(std::shared_ptr < GameEngineCollision> _This, std::shared_ptr < GameEngineCollision> _Other);

};

