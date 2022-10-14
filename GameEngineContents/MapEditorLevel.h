#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MapEditorLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MapEditorLevel();
	~MapEditorLevel();

	// delete Function
	MapEditorLevel(const MapEditorLevel& _Other) = delete;
	MapEditorLevel(MapEditorLevel&& _Other) noexcept = delete;
	MapEditorLevel& operator=(const MapEditorLevel& _Other) = delete;
	MapEditorLevel& operator=(MapEditorLevel&& _Other) noexcept = delete;

	TileMapActor* TileMap;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	void OnEvent() override;

};

