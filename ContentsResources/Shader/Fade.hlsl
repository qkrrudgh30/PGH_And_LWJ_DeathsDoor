#include "..\GameEngineResources\GameEngineShader\TransformHeader.fx"
#include "..\GameEngineResources\GameEngineShader\RenderOption.fx"

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

cbuffer FadeInfo : register(b1)
{
    float2  mf2FrameDataPos;
    float2  mf2FrameDataSize;
    float4  mf4PivotPos;
    float   mfFrom;
    float   mfTo;
    int     mbWrapping;
    int     mbLoop;
    int     mbIsUnityTexture;
}

Output Fade_VS(Input _Input)
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

SamplerState LINEARWRAP : register(s0);

float4 Fade_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex.x < 0.f || _Input.Tex.y < 0.f)
    {
        clip(-1);
    }
    
    float4 Result = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
    
    if (1 <= Result.a)
    {
        Result.a = 1.0f;
    }
    
    return Result;
}




