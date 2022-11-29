#pragma once

// Ό³Έν :
class TowerJumpAtt : public UnitBase
{
public:
	// constrcuter destructer
	TowerJumpAtt();
	~TowerJumpAtt();

	// delete Function
	TowerJumpAtt(const TowerJumpAtt& _Other) = delete;
	TowerJumpAtt(TowerJumpAtt&& _Other) noexcept = delete;
	TowerJumpAtt& operator=(const TowerJumpAtt& _Other) = delete;
	TowerJumpAtt& operator=(TowerJumpAtt&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}
private:

};

