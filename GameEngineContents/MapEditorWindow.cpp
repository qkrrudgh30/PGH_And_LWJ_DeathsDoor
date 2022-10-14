#include "PreCompile.h"
#include "MapEditorWindow.h"
#include "TileMapActor.h"

MapEditorWindow::MapEditorWindow() 
    : Scale{30, 30}
    , SelectTile(-1)
{
}

MapEditorWindow::~MapEditorWindow() 
{
}


void MapEditorWindow::Initialize(class GameEngineLevel* _Level) 
{
    if (false == GameEngineInput::GetInst()->IsKey("TileSet"))
    {
        GameEngineInput::GetInst()->CreateKey("TileSet", VK_LBUTTON);
    }
	
}


void MapEditorWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime) 
{
    // ImGui::PushID
	if (true == ImGui::Button("FolderTextureLoad"))
	{
        GameEngineDirectory Dir;
        Dir.MoveParentToExitsChildDirectory("ContentsResources");
        Dir.Move("ContentsResources");
        Dir.Move("Texture");
        Dir.Move("Map");



        std::string Path =  GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 텍스처 로드"), Dir.GetFullPath());

        if (false == Path.empty())
        {
            SelectFolderTexture = GameEnginePath::GetFileName(Path);

            GameEngineFolderTexture::Load(Path.c_str());
        }
	}

    if (false == SelectFolderTexture.empty())
    {
        ImGui::SameLine();
        ImGui::Text(SelectFolderTexture.c_str());
        ImGui::InputInt2("Scale", Scale);

        if (true == ImGui::Button("MapCreate"))
        {
            TileMap->TileRenderer->CreateIsometricTileMap(Scale[0], Scale[1], {64, 32}, SelectFolderTexture, 32);
        }


        std::string SelectIndex = "Select Index = ";
        int X;
        int Y;
        TileMap->TileRenderer->GetTileIndex(_Level->GetMainCamera()->GetMouseWorldPosition(), X, Y);

        SelectIndex += std::to_string(X);
        SelectIndex += " " + std::to_string(Y);

        ImGui::Text(SelectIndex.c_str());
    }

    GameEngineFolderTexture* Texture = GameEngineFolderTexture::Find(SelectFolderTexture);

    if (nullptr != Texture)
    {
        ImGui::BeginChildFrame(ImGui::GetID("TileSelect"), { 90 * 5, 500 });

        for (size_t i = 0; i < Texture->GetTextureCount(); i++)
        {
            GameEngineTexture* TileImage = Texture->GetTexture(i);
            if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(TileImage->CreateShaderResourceView()), { 64, 32 }))
            {
                SelectTile = i;
            }
            
            if (0 != (i + 1)% 5)
            {
                ImGui::SameLine();
            }
        }
        ImGui::EndChildFrame();
    }

    if (true == GameEngineInput::GetInst()->IsDown("TileSet")
        && nullptr != Texture
        && -1 != SelectTile
        && SelectTile < Texture->GetTextureCount())
    {

        float4 MousePos = _Level->GetMainCamera()->GetMouseWorldPosition();
        // GameEngineInput::

        TileMap->TileRenderer->SetTileIndex(MousePos, SelectTile);
        int a = 0;
    }
    // TileMap->TileRenderer->

}