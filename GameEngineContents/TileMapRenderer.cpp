#include "PreCompile.h"
#include "TileMapRenderer.h"

TileMapRenderer::TileMapRenderer() 
{
}

TileMapRenderer::~TileMapRenderer() 
{
}

void TileMapRenderer::Start() 
{
	SetPipeLine("TextureAtlas");

	FrameData.PosX = 0.0f;
	FrameData.PosY = 0.0f;
	FrameData.SizeX = 1.0f;
	FrameData.SizeY = 1.0f;

	GetShaderResources().SetConstantBufferLink("AtlasData", FrameData);
	GetShaderResources().SetConstantBufferLink("PixelData", PixelData);

	PushRendererToMainCamera();
}

void TileMapRenderer::GetTileIndex(float4 _Pos, int& _X, int& _Y)
{
	float fX = (_Pos.x / TileScaleH.x + _Pos.y / -TileScaleH.y) / 2.0f;
	float fY = (_Pos.y / -TileScaleH.y - _Pos.x / TileScaleH.x) / 2.0f;

	_X = static_cast<int>(roundf(fX));
	_Y = static_cast<int>(roundf(fY));
}

void TileMapRenderer::SetTileIndex(float4 _Pos, size_t _Index)
{
	if (0 > _Index)
	{
		return;
	}

	if (TileTextures->GetTextureCount() <= _Index)
	{
		return;
	}

	// _Pos
	int X = -1;
	int Y = -1;

	GetTileIndex(_Pos, X, Y);

	if (0 > X)
	{
		return;
	}

	if (TileX <= X)
	{
		return;
	}

	if (0 > Y)
	{
		return;
	}

	if (TileY <= Y)
	{
		return;
	}

	Tiles[Y][X].TileIndex = static_cast<int>(_Index);
	Tiles[Y][X].TileImage = TileTextures->GetTexture(_Index);

}

void TileMapRenderer::CreateIsometricTileMap(int _X, int _Y, float4 _TileScale, const std::string& _FolderTexture, int _DefualtIndex)
{
	TileTextures = GameEngineFolderTexture::Find(_FolderTexture);

	if (nullptr == TileTextures)
	{
		MsgBoxAssertString("존재하지 않는 폴더텍스처로 타일맵을 만들려고 했습니다" + _FolderTexture);
	}

	TileX = _X;
	TileY = _Y;

	Tiles.resize(_Y);

	TileScale = _TileScale;
	TileScaleH = TileScale.Half();

	for (size_t y = 0; y < Tiles.size(); y++)
	{
		Tiles[y].resize(_X);

		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			Tiles[y][x].TileIndex = static_cast<int>(_DefualtIndex);
			Tiles[y][x].TileImage = TileTextures->GetTexture(_DefualtIndex);
		}
	}
}

void TileMapRenderer::Update(float _Delta) 
{

}
void TileMapRenderer::Render(float _DeltaTime) 
{
	static GameEngineTransform TileTrans;

	// TileTrans.SetLocalScale(TileScale);
	TileTrans.SetView(GetTransform().GetTransformData().ViewMatrix);
	TileTrans.SetProjection(GetTransform().GetTransformData().ProjectionMatrix);
	// DebugTrans.CalculateWorldViewProjection();



	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			float4 Pos = GetTransform().GetWorldPosition();
			// Pos.x += TileScale.x * x;
			// Pos.y += -TileScale.y * y;

			Pos.x = (x * TileScaleH.x) + (y * -TileScaleH.x);
			Pos.y = (x * -TileScaleH.y) + (y * -TileScaleH.y);
			Pos.z = Pos.y;

			TileTrans.SetLocalScale(Tiles[y][x].TileImage->GetScale());
			TileTrans.SetLocalPosition(Pos);
			TileTrans.CalculateWorldViewProjection();
			GetShaderResources().SetConstantBufferLink("TransformData", TileTrans.GetTransformData());
			GetShaderResources().SetTexture("Tex", Tiles[y][x].TileImage);
			GameEngineDefaultRenderer::Render(_DeltaTime);

			//if (Tiles[y][x].절벽텍스처)
			//{
			//  TileTrans.SetLocalScale(Tiles[y][x].TileImage.GetScale());
			//	TileTrans.SetLocalPosition(Pos);
			//	TileTrans.CalculateWorldViewProjection();
			//	ShaderResources.SetConstantBufferLink("TransformData", TileTrans.GetTransformData());
			//	ShaderResources.SetTexture("Tex", Tiles[y][x].TileImage);
			//	GameEngineDefaultRenderer::Render(_DeltaTime);
			//}

		}
	}
}