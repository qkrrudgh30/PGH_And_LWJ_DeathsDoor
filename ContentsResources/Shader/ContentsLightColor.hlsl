#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"
#include "ContentsLight.hlsli"

struct Input
{
    float4 Position : POSITION;
    float4 Normal : NORMAL;
};

struct Output
{
    float4 Position : SV_POSITION;
    float4 PositionWithView : POSITION;
    float4 Normal : NORMAL;
};

Output ContentsColor_VS(Input _VSInput)
{
    Output VSOutput = (Output) 0;
    
    VSOutput.Position = mul(_VSInput.Position, WorldViewProjection);
    
    VSOutput.PositionWithView = mul(_VSInput.Position, WorldView);
    
    _VSInput.Normal.w = 0.f;
    VSOutput.Normal = mul(_VSInput.Normal, WorldView);
    VSOutput.Normal.w = 0.f;
    
    return VSOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

float4 ContentsColor_PS(Output _PSInput) : SV_Target0
{
    if (0.f == Lights[0].f4LightColor.a)
    {
        return Color;
    }
    
    float4 f4Diffuse = CalculateDiffuseLights(_PSInput.Normal);
    float4 f4Specular = CalculateSpacularLights(_PSInput.PositionWithView, _PSInput.Normal);
    float4 f4Ambient = CalculateAmbientLights();
    
    float4 f4Result = Color * (f4Diffuse + f4Specular + f4Ambient);
    f4Result.w = 1.f;
    
    return f4Result;
}
