#pragma once

// Ό³Έν :
class AClassDefaultWithPrecompile
{
public:
	// constrcuter destructer
	AClassDefaultWithPrecompile();
	~AClassDefaultWithPrecompile();

	// delete Function
	AClassDefaultWithPrecompile(const AClassDefaultWithPrecompile& _Other) = delete;
	AClassDefaultWithPrecompile(AClassDefaultWithPrecompile&& _Other) noexcept = delete;
	AClassDefaultWithPrecompile& operator=(const AClassDefaultWithPrecompile& _Other) = delete;
	AClassDefaultWithPrecompile& operator=(AClassDefaultWithPrecompile&& _Other) noexcept = delete;

protected:

private:

};

