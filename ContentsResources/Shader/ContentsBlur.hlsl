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
    uint muOnOff;
    uint muAppliedArea;
    float mfIntence;
    float4 mf4WindowSize;
}

// static float GaussianBlur1D[5] = { 0.0545f, 0.2442f, 0.4026f, 0.2442f, 0.0545f };
// static float GaussianBlur1D[5] = { 6.f, 24.f, 36.f, 24.f, 6.f };
static float GaussianBlur7x7[7][7] =
{
    { 0,  0,  1,   2,  1,  0, 0 }, // 3
    { 0,  3, 13,  22, 13,  3, 0 }, // 54
    { 1, 13, 59,  97, 59, 13, 1 }, // 243
    { 2, 22, 97, 159, 97, 22, 2 }, // 401
    { 1, 13, 59,  97, 59, 13, 1 }, // 243
    { 0,  3, 13,  22, 13,  3, 0 }, // 54
    { 0,  0,  1,   2,  1,  0, 0 }  // 3
};

static float GaussianBlur5x5[5][5] =
{
    { 1,  4,  7,  4, 1 }, // 17
    { 4, 16, 26, 16, 4 }, // 66
    { 7, 26, 41, 26, 7 }, // 107
    { 4, 16, 26, 16, 4 }, // 66
    { 1,  4,  7,  4, 1 }  // 17
};

static float GaussianBlur3x3[3][3] =
{
    { 1, 2, 1},
    { 2, 4, 2},    
    { 1, 2, 1}
};

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
    float2 f2UVSize = float2(1.f / mf4WindowSize.x, 1.f / mf4WindowSize.y);
    float2 f2UVCenterPos = _Input.Tex.xy;
    float2 f2UVStartPos = f2UVCenterPos + (-f2UVSize * 2.f);
    float2 f2UVCurrentPos = f2UVStartPos;
    float4 f4Result = (float) 0.f;    
    
    if (0u == muOnOff)
    {
        f4Result = Tex.Sample(POINTWRAP, _Input.Tex.xy);
        return f4Result;
    }
    
    for (int y = 0; y < muAppliedArea; ++y)
    {
        for (int x = 0; x < muAppliedArea; ++x)
        {
            if (3 == muAppliedArea)
            {
                f4Result += Tex.Sample(POINTWRAP, f2UVCurrentPos) * GaussianBlur3x3[y][x];
            }
            if (5 == muAppliedArea)
            {
                f4Result += Tex.Sample(POINTWRAP, f2UVCurrentPos) * GaussianBlur5x5[y][x];
            }
            if (7 == muAppliedArea)
            {
                f4Result += Tex.Sample(POINTWRAP, f2UVCurrentPos) * GaussianBlur7x7[y][x];
            }
        
            f2UVCurrentPos.x += f2UVSize.x;
        }
        
        f2UVCurrentPos.x = f2UVStartPos.x;
        f2UVCurrentPos.y += f2UVSize.y;
    }
    
    if (3 == muAppliedArea)
    {
        f4Result /= (16.f - mfIntence);
    }
    if (5 == muAppliedArea)
    {
        f4Result /= (273.f - mfIntence);
    }
    if (7 == muAppliedArea)
    {
        f4Result /= (1001.f - mfIntence);
    }
    
    f4Result.r += 1e-2f;
    f4Result.g += 1e-2f;
    f4Result.b += 1e-2f;
    
    if (f4Result.a <= 0.0f)
    {
        clip(-1);
    }
    
    return f4Result;
}