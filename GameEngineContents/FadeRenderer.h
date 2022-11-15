#pragma once

// Ό³Έν :
class FadeRenderer
{
public:
	// constrcuter destructer
	FadeRenderer();
	~FadeRenderer();

	// delete Function
	FadeRenderer(const FadeRenderer& _Other) = delete;
	FadeRenderer(FadeRenderer&& _Other) noexcept = delete;
	FadeRenderer& operator=(const FadeRenderer& _Other) = delete;
	FadeRenderer& operator=(FadeRenderer&& _Other) noexcept = delete;

protected:

private:

};

