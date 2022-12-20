#include "../../GameEngineResources/GameEngineShader/TransformHeader.fx"
#include "../../GameEngineResources/GameEngineShader/DeferredHeader.fx"
#include "ContentsLight.hlsli"

struct Input
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
};

struct Output
{
    float4 Position : SV_POSITION;
    float4 ViewPosition : POSITION;
    float4 ViewNormal : NORMAL;
};

Output ContentsDeferredLightColor_VS(Input _VSInput)
{
    Output VSOutput = (Output) 0;

    VSOutput.Position = mul(_VSInput.Position, WorldViewProjection);
    
    VSOutput.ViewPosition = mul(_VSInput.Position, WorldView);
    
    _VSInput.Normal.w = 0.f;
    VSOutput.ViewNormal = normalize(mul(_VSInput.Normal, WorldView));
    VSOutput.ViewNormal.w = 0.f;
    
    return VSOutput;
}

cbuffer ResultColor : register(b0)
{
    float4 f4OriginalColor;
}

cbuffer AdditionalInfoForLight : register(b1)
{
    uint uOnOffLight;
    float4 f4Padding;
}

DeferredOutPut ContentsColor_PS(Output _PSInput) : SV_Target0
{
    DeferredOutPut PSOutput = (DeferredOutPut) 0;
    
    PSOutput.Dif = f4OriginalColor;
    PSOutput.Pos = _PSInput.ViewPosition;
    if (0u == uOnOffLight)
    {
        PSOutput.Nor = (float4) 0.f;
    }
    else
    {
        PSOutput.Nor = _PSInput.ViewNormal;
    }
    PSOutput.Nor.w = 1.f;
    
    return PSOutput;
}
