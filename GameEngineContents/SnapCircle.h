#pragma once

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

};

