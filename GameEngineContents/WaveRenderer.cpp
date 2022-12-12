#include "PreCompile.h"
#include "WaveRenderer.h"

#include <GameEngineCore/GameEngineTextureRenderer.h>

WaveRenderer::WaveRenderer() 
	: m_structWaveInfo{}
	, m_structPixelData{}
{
}

WaveRenderer::~WaveRenderer() 
{
}

void WaveRenderer::SetPivot(PIVOTMODE _eMode)
{
	switch (_eMode)
	{
	case PIVOTMODE::CENTER:
		m_structWaveInfo.m_f4PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		m_structWaveInfo.m_f4PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		m_structWaveInfo.m_f4PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		m_structWaveInfo.m_f4PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		m_structWaveInfo.m_f4PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		m_structWaveInfo.m_f4PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		m_structWaveInfo.m_f4PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		m_structWaveInfo.m_f4PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		m_structWaveInfo.m_f4PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}
}

void WaveRenderer::SetWaveInfo()
{
}

void WaveRenderer::SetTexture(const std::string& _strTextureName)
{
	m_wptrCurrentTexture = GetShaderResources().SetTexture("DiffuseTexture", _strTextureName);
}

void WaveRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	SetWaveRenderingSetting();
}

void WaveRenderer::Update(float _fDeltatime)
{
	m_structWaveInfo.m_fAccTime += _fDeltatime;
}

void WaveRenderer::InitializeWave()
{
	m_structWaveInfo.m_fAccTime = 0.f;
}


void WaveRenderer::SetWaveRenderingSetting()
{
	InitializeWave();

	SetMaterial("Wave");

	GetShaderResources().SetConstantBufferLink("WaveInfo", m_structWaveInfo);
	GetShaderResources().SetConstantBufferLink("PixelData", m_structPixelData);
}
