
#pragma once

// Ό³Έν :
class LaserTarget;
class TowerLaser : public UnitBase
{
public:
	// constrcuter destructer
	TowerLaser();
	~TowerLaser();

	// delete Function
	TowerLaser(const TowerLaser& _Other) = delete;
	TowerLaser(TowerLaser&& _Other) noexcept = delete;
	TowerLaser& operator=(const TowerLaser& _Other) = delete;
	TowerLaser& operator=(TowerLaser&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float m_fTime = 0.f;
	bool m_bMakeCheck = false;
public:
	std::weak_ptr < LaserTarget> m_CLaserTarget;

};

