
#pragma once

// Ό³Έν :
class LaserTarget : public UnitBase
{
public:
	// constrcuter destructer
	LaserTarget();
	~LaserTarget();

	// delete Function
	LaserTarget(const LaserTarget& _Other) = delete;
	LaserTarget(LaserTarget&& _Other) noexcept = delete;
	LaserTarget& operator=(const LaserTarget& _Other) = delete;
	LaserTarget& operator=(LaserTarget&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:
	float m_fTime = 0.f;
	bool m_bMakeCheck = false;

};

