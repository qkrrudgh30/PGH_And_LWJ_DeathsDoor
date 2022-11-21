#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"
#include "..\..\GameEngineResources\GameEngineShader\RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
    uint Index : ROWINDEX;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;    
};

cbuffer BlurInfo : register(b1)
{
    float2 mf2FrameDataPos;
    float2 mf2FrameDataSize;
    float4 mf4PivotPos;
    uint muAppliedType;
    uint muAppliedCount;
    int miIsUnityTexture;
}

static float GaussianBlur1D[5] = { 0.0545f, 0.2442f, 0.4026f, 0.2442f, 0.0545f };
// static float GaussianBlur1D = { 6.f, 24.f, 36.f, 24.f, 6.f };

Output ContentsBlur_VS(Input _Input)
{
    Output NewOutput = (Output)0;
    
    _Input.Pos += mf4PivotPos;
    NewOutput.Pos = mul(_Input.Pos, WorldViewProjection);
    
    NewOutput.PosLocal = _Input.Pos;

    NewOutput.Tex.x = (_Input.Tex.x * mf2FrameDataSize.x) + mf2FrameDataPos.x;
    NewOutput.Tex.y = (_Input.Tex.y * mf2FrameDataSize.y) + mf2FrameDataPos.y;
    
    return NewOutput;
}

Texture2D Tex : register(t0);

SamplerState POINTWRAP : register(s0);

float4 ContentsBlur_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex.x < 0.f || _Input.Tex.y < 0.f)
    {
        clip(-1);
    }
    
    float4 Result = 0.f;
    
    float2 UVSize = float2(1.f / mf2FrameDataSize.x, 1.f / mf2FrameDataSize.y);
    float2 UVCenterPos = _Input.Tex.xy;
    float2 UVStartPos = UVCenterPos + (-UVSize * 2.f);
    float2 UVCurrentPos = UVStartPos;
    
    if (0u == muAppliedType || 2u == muAppliedType)
    {
        for (uint count = 0; count <= muAppliedCount; ++count)
        {
            for (uint i = 0; i <= 4; ++i)
            {
                Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                UVCurrentPos.x += UVSize.x;
            }
        }
    }
    
    if (1u == muAppliedType || 2u == muAppliedType)
    {
        for (uint count = 0; count <= muAppliedCount; ++count)
        {
            for (uint i = 0; i <= 4; ++i)
            {
                Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                UVCurrentPos.y += UVSize.y;
            }
        }
    }
    
    return Result;
}