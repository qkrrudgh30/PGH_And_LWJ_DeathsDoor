#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"

struct Input
{
    float4 Position : POSITION;
};

struct Output
{
    float4 Position : SV_POSITION;
};

Output ContentsColor_VS(Input _VSInput)
{
    Output VSOutput = (Output) 0;
    
    VSOutput.Position = mul(_VSInput.Position, WorldViewProjection);
    
    return VSOutput;
}

cbuffer ResultColor : register(b8)
{
    float4 Color;
}

float4 ContentsColor_PS(Output _PSInput) : SV_Target0
{
    return Color;
}