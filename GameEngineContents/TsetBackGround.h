#pragma once

// Ό³Έν :
class TsetBackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	TsetBackGround();
	~TsetBackGround();

	// delete Function
	TsetBackGround(const TsetBackGround& _Other) = delete;
	TsetBackGround(TsetBackGround&& _Other) noexcept = delete;
	TsetBackGround& operator=(const TsetBackGround& _Other) = delete;
	TsetBackGround& operator=(TsetBackGround&& _Other) noexcept = delete;


protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}

	GameEngineTextureRenderer* Renderer;


private:

};

