#include "PreCompile.h"
#include "TileMapActor.h"

TileMapActor::TileMapActor() 
{
}

TileMapActor::~TileMapActor() 
{
}

void TileMapActor::Start() 
{
	{
		TileRenderer = CreateComponent<TileMapRenderer>();
	}
}

void TileMapActor::Update(float _DeltaTime) 
{

}
void TileMapActor::End() 
{

}