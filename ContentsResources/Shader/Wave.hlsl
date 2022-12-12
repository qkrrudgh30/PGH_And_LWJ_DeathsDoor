#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

cbuffer WaveInfo : register(b1)
{
    float m_fAccTime;
    float4 m_f4PivotPos;
}

Output Wave_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    float fCosTime = cos(m_fAccTime + _Input.Tex.x) * 0.1;
    _Input.Pos.y += fCosTime;
    
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D DiffuseTexture : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Wave_PS(Output _Input) : SV_Target0
{
    float4 Color = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor + PlusColor;
    
    if (Color.a <= 0.0f)
    {
        clip(-1);
    }
    
    if (1 <= Color.a)
    {
        Color.a = 1.0f;
    }
    
    return Color;
}
