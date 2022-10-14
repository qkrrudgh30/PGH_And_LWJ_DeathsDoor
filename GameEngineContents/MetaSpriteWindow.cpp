#include "PreCompile.h"
#include "MetaSpriteWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineCoreDebug.h>

MetaSpriteWindow::MetaSpriteWindow() 
    : CurMetaFolder_{}
    , CurAtlasFolder_{}
    , CurMetaFile_{}
    , CurAtlasFile_{}
{
}

MetaSpriteWindow::~MetaSpriteWindow() 
{
}

void MetaSpriteWindow::Initialize(GameEngineLevel* _Level) 
{
}

void MetaSpriteWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime) 
{
    AtlasFileButton(_Level);
    MetaFileButton(_Level);

    // AtlasFileButton();
    // MetaFileButton();
}


void MetaSpriteWindow::MetaFileButton(GameEngineLevel* _Level)
{
    if (nullptr == TargetTexture)
    {
        return;
    }


    if (true == ImGui::Button("MetaFileLoad") && 0 == TargetTexture->GetCutCount())
    {

        std::string Path = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineFile LoadFile = GameEngineFile(Path);
            LoadFile.Open(OpenMode::Read, FileMode::Text);

            std::string AllText = LoadFile.GetString();

            size_t StartPos = 0;

            while (true)
            {
                StartPos = AllText.find("rect:", StartPos);

                if (StartPos == std::string::npos)
                {
                    break;
                }

                size_t EndPos = AllText.find("outline:", StartPos);

                if (EndPos == std::string::npos)
                {
                    break;
                }

                std::string CutDataString = AllText.substr(StartPos, EndPos - StartPos);

                int StartX = 0;
                int StartY = 0;
                int SizeX = 0;
                int SizeY = 0;

                {
                    std::string FindString = "x:";
                    size_t DataStartPos = CutDataString.find(FindString);
                    size_t DataEndpos = CutDataString.find("\n", DataStartPos);
                    std::string XString = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
                    StartX = atoi(XString.c_str());
                }

                {
                    std::string FindString = "y:";
                    size_t DataStartPos = CutDataString.find(FindString);
                    size_t DataEndpos = CutDataString.find("\n", DataStartPos);
                    std::string XString = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
                    StartY = atoi(XString.c_str());
                }

                {
                    std::string FindString = "width:";
                    size_t DataStartPos = CutDataString.find(FindString);
                    size_t DataEndpos = CutDataString.find("\n", DataStartPos);
                    std::string XString = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
                    SizeX = atoi(XString.c_str());
                }

                {
                    std::string FindString = "height:";
                    size_t DataStartPos = CutDataString.find(FindString);
                    size_t DataEndpos = CutDataString.find("\n", DataStartPos);
                    std::string XString = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
                    SizeY = atoi(XString.c_str());
                }

                std::string DebugText;
                DebugText += "StartX : " + std::to_string(StartX) + ",";
                DebugText += "StartY : " + std::to_string(StartY) + ",";
                DebugText += "SizeX : " + std::to_string(SizeX) + ",";
                DebugText += "SizeY : " + std::to_string(SizeY) + ",";
                DebugText += "\n";

                GameEngineDebug::OutPutString(DebugText.c_str());

                TargetTexture->Cut(StartX, static_cast<UINT>(TargetTexture->GetScale().y - StartY - SizeY), SizeX, SizeY);
                StartPos += 1;
            }

            GameEngineActor* NewActor = _Level->CreateActor<GameEngineActor>();

            NewActor->GetTransform().SetLocalPosition(float4{-500.0f, 0.0f, 0.0f});

            Renderer = NewActor->CreateComponent<GameEngineTextureRenderer>();
            Renderer->SetTexture(TargetTexture, 0);
            Renderer->SetSamplingModePoint();
            Renderer->ScaleToCutTexture(2);



            // CurMetaFolder_ = GameEnginePath::GetFileName(Path);
            // GameEngineMetaDataFolder::Load(Path.c_str());
        }


    }

    if (nullptr != TargetTexture && 0 != TargetTexture->GetCutCount())
    {
        ImGui::SliderInt("ImageIndex", &CurFrame, 0, static_cast<int>(TargetTexture->GetCutCount() - 1));
        Renderer->SetTexture(TargetTexture, CurFrame);
        Renderer->ScaleToCutTexture(CurFrame);
    }


    if (nullptr != TargetTexture)
    {
        float4 ImagePos = TargetTexture->GetScale().Half();

        ImagePos.y = -ImagePos.y;

        GameEngineDebug::DrawTexture(TargetTexture, ImagePos);

        for (int i = 0; i < TargetTexture->GetCutCount(); i++)
        {
            float4 Pos = TargetTexture->GetCutPos(i);
            float4 Scale = TargetTexture->GetCutScale(i);

            Pos.y = -Pos.y;
            Pos.x += Scale.x * 0.5f;
            Pos.y -= Scale.y * 0.5f;

            GameEngineDebug::DrawBox(Pos, Scale, float4::ZERO, float4(1.0f, 0.0f, 0.0f, 0.5f));
        }
    }


    if (false == CurMetaFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurMetaFolder_.c_str());
    }
}

void MetaSpriteWindow::AtlasFileButton(GameEngineLevel* _Level)
{

    if (true == ImGui::Button("AtlasFileLoad"))
    {
        std::string Path = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            TargetTexture = GameEngineTexture::Load(Path);
        }
    }

    if (false == CurAtlasFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(TargetTexture->GetNameCopy().c_str());
    }
}

//
//void MetaSpriteWindow::MetaFileButton() 
//{
//    if (true == ImGui::Button("MetaFileLoad"))
//    {
//        if (true == CurAtlasFile_.empty())
//        {
//            MsgBoxAssert("아틀라스 시트를 선택하기 전에 메타 파일을 선택하려고 하였습니다.");
//            return;
//        }
//
//        GameEngineDirectory Dir;
//        Dir.MoveParentToExitsChildDirectory("GameEngineResources");
//        Dir.Move("GameEngineResources");
//        Dir.Move("Resources");
//        Dir.Move("Metafile");
//
//        std::string Path
//            = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), Dir.GetFullPath());
//
//        if (false == Path.empty())
//        {
//            CurMetaFile_ = GameEnginePath::GetFileName(Path);
//            // GameEngineMetaData::Load(Path.c_str());
//        }
//    }
//
//    if (false == CurMetaFile_.empty())
//    {
//        if (CurMetaFile_ != CurAtlasFile_ + ".meta")
//        {
//            MsgBoxAssert("가져오려는 메타 파일과 선택된 아틀라스 시트의 이름이 다릅니다.");
//            return;
//        }
//
//        ImGui::SameLine();
//        ImGui::Text(CurMetaFile_.c_str());
//    }
//}
//
//void MetaSpriteWindow::AtlasFileButton()
//{
//    if (true == ImGui::Button("AtlasFileLoad"))
//    {
//        GameEngineDirectory Dir;
//        Dir.MoveParentToExitsChildDirectory("GameEngineResources");
//        Dir.Move("GameEngineResources");
//        Dir.Move("Resources");
//        Dir.Move("Sprite");
//
//        std::string Path
//            = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"), Dir.GetFullPath());
//
//        if (false == Path.empty())
//        {
//            CurAtlasFile_ = GameEnginePath::GetFileName(Path);
//
//            GameEngineTexture::Load(Path.c_str());
//        }
//    }
//
//    if (false == CurAtlasFile_.empty())
//    {
//        ImGui::SameLine();
//        ImGui::Text(CurAtlasFile_.c_str());
//    }
//}
