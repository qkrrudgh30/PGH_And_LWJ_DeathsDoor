#include "../../GameEngineResources/GameEngineShader/TransformHeader.fx"

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

cbuffer PaperBurnInfo : register(b1)
{
    uint muOnOffPaperBurn;
    float mfEffectTime;
    float mfPadding1;
    float mfPadding2;
}

Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D CloudTexture : register(t1);
SamplerState LINEARWRAP : register(s0);

float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 f4Orignal = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    float4 f4Cloud = CloudTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    
    if (0u == muOnOffPaperBurn)
    {
        return f4Orignal;
    }    
    
    if (f4Cloud.r <= mfEffectTime)
    {
        f4Orignal.a = 0;
    }
    else
    {
        f4Orignal.a = 1;
    }

    if (mfEffectTime - 0.05 <= f4Cloud.r && f4Cloud.r <= mfEffectTime + 0.05)
    {
        f4Orignal = float4(1, 0, 0, 1);
    }
     
    if (mfEffectTime - 0.03 <= f4Cloud.r && f4Cloud.r <= mfEffectTime + 0.03)
    {
        f4Orignal = float4(1, 1, 0, 1);
    }
     
    if (mfEffectTime - 0.025 <= f4Cloud.r && f4Cloud.r <= mfEffectTime + 0.025)
    {
        f4Orignal = float4(1, 1, 1, 1);
    }
    
    return f4Orignal;
}
