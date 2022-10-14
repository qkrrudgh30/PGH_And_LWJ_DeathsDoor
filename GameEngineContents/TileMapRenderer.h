#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>


class Tile
{
public:
	int TileIndex;
	int Z;
	GameEngineTexture* TileImage;
	// GameEngineTexture* 절벽텍스처;
};

// 타일의 정보

// 설명 :
class TileMapRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	TileMapRenderer();
	~TileMapRenderer();

	// delete Function
	TileMapRenderer(const TileMapRenderer& _Other) = delete;
	TileMapRenderer(TileMapRenderer&& _Other) noexcept = delete;
	TileMapRenderer& operator=(const TileMapRenderer& _Other) = delete;
	TileMapRenderer& operator=(TileMapRenderer&& _Other) noexcept = delete;

	// CreateTileMap(Scale[0], Scale[1], SelectFolderTexture);
	void CreateIsometricTileMap(int _X, int _Y, float4 _TileScale, const std::string& _FolderTexture, int _DefualtIndex = 0);
	void SetTileIndex(float4 _Pos, size_t _Index);

	void GetTileIndex(float4 _Pos, int& _X, int& _Y);

protected:
	void Render(float _DeltaTime) override;

private:
	void Start() override;
	void Update(float _Delta) override;


	int TileX;
	int TileY;

	GameEngineFolderTexture* TileTextures;

	float4 TileScale;
	float4 TileScaleH;
	std::vector<std::vector<Tile>> Tiles;
	float4 FrameData;
	PixelData PixelData;
};

