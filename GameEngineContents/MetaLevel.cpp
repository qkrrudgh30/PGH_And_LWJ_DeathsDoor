#include "PreCompile.h"
#include "MetaLevel.h"
#include "MetaSpriteWindow.h"

MetaLevel::MetaLevel() 
{
}

MetaLevel::~MetaLevel()
{
}

void MetaLevel::Start()
{
    MetaAnimationGUI_ = GameEngineGUI::CreateGUIWindow<MetaSpriteWindow>("MetaAnimationGUI", this);

    MetaAnimationGUI_->MetaDir.MoveParentToExitsChildDirectory("GameEngineResources");
    MetaAnimationGUI_->MetaDir.Move("ContentsResources");
    MetaAnimationGUI_->MetaDir.Move("Texture");
    MetaAnimationGUI_->MetaDir.Move("Meta");

    MetaAnimationGUI_->Off();
}

void MetaLevel::Update(float _DeltaTime)
{
}

void MetaLevel::End()
{
}

void MetaLevel::OnEvent()
{
    MetaAnimationGUI_->On();
}

void MetaLevel::OffEvent()
{
    MetaAnimationGUI_->Off();
}
