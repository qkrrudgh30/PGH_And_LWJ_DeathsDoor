#pragma once

// Ό³Έν :
class SnapTarGet : public UnitBase
{
public:
	// constrcuter destructer
	SnapTarGet();
	~SnapTarGet();

	// delete Function
	SnapTarGet(const SnapTarGet& _Other) = delete;
	SnapTarGet(SnapTarGet&& _Other) noexcept = delete;
	SnapTarGet& operator=(const SnapTarGet& _Other) = delete;
	SnapTarGet& operator=(SnapTarGet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

private:



};

