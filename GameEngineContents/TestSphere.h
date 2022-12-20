#pragma once
#include "UnitBase.h"

// Ό³Έν :
class TestSphere : public UnitBase
{
public:
	// constrcuter destructer
	TestSphere();
	~TestSphere();

	// delete Function
	TestSphere(const TestSphere& _Other) = delete;
	TestSphere(TestSphere&& _Other) noexcept = delete;
	TestSphere& operator=(const TestSphere& _Other) = delete;
	TestSphere& operator=(TestSphere&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _fDeltatime) override;
	void End() {}

private:

public:

protected:

private:
	AdditionalInfoForLight m_structLightInfo;

};

