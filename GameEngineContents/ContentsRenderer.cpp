#include "PreCompile.h"
#include "ContentsRenderer.h"

#include <GameEngineCore/GameEngineTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineVertexShader.h>

ContentsRenderer::ContentsRenderer() 
{
}

ContentsRenderer::~ContentsRenderer() 
{
}

void ContentsRenderer::Render(float _fDeltatime)
{
	if (eResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->Render(_fDeltatime);
	}
	else
	{

	}
}

void ContentsRenderer::SetMesh(const std::string& _strMeshName)
{
	if (eResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->SetMesh(_strMeshName);
	}
	else
	{

	}
	
}

void ContentsRenderer::SetMaterial(const std::string& _strMaterialName)
{
	if (eResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit.lock()->SetPipeLine(_strMaterialName);
		mwptrRenderingUnit.lock()->SetRenderer(std::dynamic_pointer_cast<GameEngineRenderer>(shared_from_this()));
	}
	else
	{

	}
}

void ContentsRenderer::SetPivot()
{
}

void ContentsRenderer::SetTexture()
{
}

void ContentsRenderer::Set2DUIShaderingInfo()
{
}

void ContentsRenderer::Set3DStaticShaderingInfo()
{
}

void ContentsRenderer::Set3DAnimatorShaderingInfo()
{
}

void ContentsRenderer::Start(void)
{
	GameEngineRenderer::Start();

	if (eResourceType::UI == mShaderingInfo.miResourceType)
	{
		mwptrRenderingUnit = std::make_shared<GameEngineRenderUnit>();
	}
	else
	{

	}
	
}

void ContentsRenderer::Update(float _fDeltatime)
{
}

void ContentsRenderer::InitializeShaderingInfo(void)
{
}

void ContentsRenderer::SetRenderingPipeline(void)
{
}

