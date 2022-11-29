#pragma once

// Ό³Έν :
class SnapEffect : public UnitBase
{
public:
	// constrcuter destructer
	SnapEffect();
	~SnapEffect();

	// delete Function
	SnapEffect(const SnapEffect& _Other) = delete;
	SnapEffect(SnapEffect&& _Other) noexcept = delete;
	SnapEffect& operator=(const SnapEffect& _Other) = delete;
	SnapEffect& operator=(SnapEffect&& _Other) noexcept = delete;
protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:

};

