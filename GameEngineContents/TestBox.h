#pragma once
#include "UnitBase.h"

// Ό³Έν :
class TestBox : public UnitBase
{
public:
	// constrcuter destructer
	TestBox();
	~TestBox();

	// delete Function
	TestBox(const TestBox& _Other) = delete;
	TestBox(TestBox&& _Other) noexcept = delete;
	TestBox& operator=(const TestBox& _Other) = delete;
	TestBox& operator=(TestBox&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _fDeltatime) override;
	void End() override {};

private:

public:

protected:

private:


};

