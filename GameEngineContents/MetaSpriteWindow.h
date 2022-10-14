#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class GameEngineTextureRenderer;
class MetaSpriteWindow : public GameEngineGUIWindow
{
public:
    MetaSpriteWindow();
    ~MetaSpriteWindow();

    MetaSpriteWindow(const MetaSpriteWindow& _Other)                = delete;
    MetaSpriteWindow(MetaSpriteWindow&& _Other) noexcept            = delete;
    MetaSpriteWindow& operator=(const MetaSpriteWindow& _Other)     = delete;
    MetaSpriteWindow& operator=(MetaSpriteWindow&& _Other) noexcept = delete;

    GameEngineDirectory MetaDir;
    GameEngineTexture* TargetTexture;

protected:
    void Initialize(class GameEngineLevel* _Level) override;
    void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
    int CurFrame;
    GameEngineTextureRenderer* Renderer;

    std::string CurMetaFolder_;
    std::string CurAtlasFolder_;

    std::string CurMetaFile_;
    std::string CurAtlasFile_;

    void MetaFileButton(GameEngineLevel* _Level);
    void AtlasFileButton(GameEngineLevel* _Level);

    //void MetaFileButton();
    //void AtlasFileButton();

};
