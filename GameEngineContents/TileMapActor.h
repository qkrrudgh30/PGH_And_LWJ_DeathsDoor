#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "TileMapRenderer.h"


// Ό³Έν :
class TileMapRenderer;
class TileMapActor : public GameEngineActor
{
public:
	// constrcuter destructer
	TileMapActor();
	~TileMapActor();

	// delete Function
	TileMapActor(const TileMapActor& _Other) = delete;
	TileMapActor(TileMapActor&& _Other) noexcept = delete;
	TileMapActor& operator=(const TileMapActor& _Other) = delete;
	TileMapActor& operator=(TileMapActor&& _Other) noexcept = delete;

	TileMapRenderer* TileRenderer;

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End();

private:

};

