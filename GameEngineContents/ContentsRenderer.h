#pragma once

// Ό³Έν :
class ContentsRenderer
{
public:
	// constrcuter destructer
	ContentsRenderer();
	~ContentsRenderer();

	// delete Function
	ContentsRenderer(const ContentsRenderer& _Other) = delete;
	ContentsRenderer(ContentsRenderer&& _Other) noexcept = delete;
	ContentsRenderer& operator=(const ContentsRenderer& _Other) = delete;
	ContentsRenderer& operator=(ContentsRenderer&& _Other) noexcept = delete;

protected:

private:

};

