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
    float   mfFrom;
    float   mfTo;
    int     mbWrapping;
    int     mbLoop;
    int     mbIsUnityTexture;
    float4  mf4PivotPos;
}

Output Fade_VS(Input _Input)
{
	Output NewOutput = (Output)0;

	_Input.Pos += PivotPos;
	NewOutput.Pos = mul(_Input.Pos, WorldViewProjection);
	NewOutput.PosLocal = _Input.Pos;

	NewOutput.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
	NewOutput.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;

	return NewOutput;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);

SamplerState LINEARWRAP : register(s0);

float4 Fade_PS(Output _Input)
{
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
	
    if (_Input.Tex.y < Slice.y)
    {
        clip(-1);
    }
    
}




