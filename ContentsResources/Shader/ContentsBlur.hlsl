#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"
#include "..\..\GameEngineResources\GameEngineShader\RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;    
};

cbuffer BlurInfo : register(b1)
{
    uint muAppliedType;
    uint muAppliedCount;
    float mfRadius;
    float4 mf4WindowSize;
}

static float GaussianBlur1D[5] = { 0.0545f, 0.2442f, 0.4026f, 0.2442f, 0.0545f };
// static float GaussianBlur1D[5] = { 6.f, 24.f, 36.f, 24.f, 6.f };

Output ContentsBlur_VS(Input _Input)
{
    Output NewOutput = (Output)0;
    
    NewOutput.Pos = _Input.Pos;
    
    NewOutput.Tex = _Input.Tex;
    
    return NewOutput;
}

Texture2D Tex : register(t0);

SamplerState POINTWRAP : register(s0);

float4 ContentsBlur_PS(Output _Input) : SV_Target0
{    
    float2 UVSize = float2(1.f / mf4WindowSize.x, 1.f / mf4WindowSize.y);
    float2 UVCenterPos = _Input.Tex.xy;
    float2 UVStartPos = UVCenterPos + (-UVSize * 2.f);
    float2 UVCurrentPos = UVStartPos;
    
    float4 Result = (float) 0.f;    
    
    if (0u == muAppliedType || 0u == muAppliedCount)
    {
        Result = Tex.Sample(POINTWRAP, _Input.Tex.xy);
        
        return Result;
    }
    
    
    if (1u == muAppliedType || 3u == muAppliedType)
    {
        for (uint count = 0; count <= muAppliedCount; ++count)
        {
            for (uint i = 0; i <= 4; ++i)
            {
                Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                UVCurrentPos.x += UVSize.x;
            }
            UVCurrentPos.x = UVStartPos.x;
        }
    }
     
    if (2u == muAppliedType || 3u == muAppliedType)
    {
        for (uint count = 0; count <= muAppliedCount; ++count)
        {
            for (uint i = 0; i <= 4; ++i)
            {
                Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                UVCurrentPos.y += UVSize.y;
            }
            UVCurrentPos.y = UVStartPos.y;
        }
    }
    
    Result.r += 1e-2f;
    Result.g += 1e-2f;
    Result.b += 1e-2f;
    
    if (Result.a <= 0.0f)
    {
        clip(-1);
    }
    
    return Result;
}