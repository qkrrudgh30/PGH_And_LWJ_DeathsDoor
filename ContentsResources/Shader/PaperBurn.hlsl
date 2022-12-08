#include "../../GameEngineResources/GameEngineShader/TransformHeader.fx"

struct Input
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 BLENDWEIGHT : BLENDWEIGHT;
    int4 BLENDINDICES : BLENDINDICES;
};

struct Output
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

struct AniMat
{
    float4x4 Mat;
};

StructuredBuffer<AniMat> ArrAniMationMatrix : register(t11);

cbuffer PaperBurnInfo : register(b1)
{
    uint muOnOffPaperBurn;
    float mfEffectTime;
    float mfHitted;
    float mfPadding2;    
}

void Skinning(inout float4 _Pos, inout float4 _Weight, inout int4 _Index, StructuredBuffer<AniMat> _ArrMatrix)
{
    float4 CalPos = (float4) 0.0f;
    _Pos.w = 1.0f;
    
    for (int i = 0; i < 4; ++i)
    {
        AniMat Mat = _ArrMatrix[_Index[i]];
        CalPos += _Weight[i] * mul(_Pos, Mat.Mat);
    }
    
    _Pos = CalPos;
}

Output Texture_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    NewOutPut.POSITION = _Input.POSITION;
    Skinning(NewOutPut.POSITION, _Input.BLENDWEIGHT, _Input.BLENDINDICES, ArrAniMationMatrix);
    NewOutPut.POSITION.w = 1.0f;
    NewOutPut.POSITION = mul(NewOutPut.POSITION, WorldViewProjection);
    NewOutPut.TEXCOORD = _Input.TEXCOORD;
    
    return NewOutPut;
}

Texture2D DiffuseTexture : register(t0);
Texture2D CloudTexture : register(t1);
SamplerState LINEARWRAP : register(s0);

float4 Texture_PS(Output _Input) : SV_Target0
{
    float4 f4Orignal = DiffuseTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy);
    float4 f4Cloud = CloudTexture.Sample(LINEARWRAP, _Input.TEXCOORD.xy);    
    
    if (1e-2f < mfHitted && 1u != muOnOffPaperBurn)
    {
        float2 PixelUVSize = float2(1.0f / 1280.0f, 1.0f / 720.0f);
        float2 PixelUVCenter = _Input.TEXCOORD.xy;
        float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
        float2 CurUV = StartUV;
        float4 f4Red = { 0.0f, 0.f, 0.f, 0.f };
        
        for (int i = 0; i <= 4; ++i)
        {
            for (int j = 0; j <= 4; ++j)
            {
                f4Red += DiffuseTexture.Sample(LINEARWRAP, CurUV) * (1.f / 16.f);
                CurUV.x += PixelUVSize.x;
            }
        
            CurUV.x = StartUV.x;
            CurUV.y += PixelUVSize.y;
        }
        
        return f4Red;
    }
    
    if (0u == muOnOffPaperBurn)
    {
        if (f4Orignal.a <= 0.0f)
        {
            f4Orignal.a = 1.f;
        }
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
