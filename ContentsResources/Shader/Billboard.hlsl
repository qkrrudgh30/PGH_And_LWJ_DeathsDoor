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

cbuffer BillboardInfo : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
    unsigned int muOnOffBillboard;
    float4x4 f4x4MainCameraRotation;
}

Output Billboard_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    if (1u == muOnOffBillboard)
    {
        NewOutPut.Pos = mul(NewOutPut.Pos, f4x4MainCameraRotation);
    }
    
    NewOutPut.PosLocal = _Input.Pos;
    NewOutPut.Tex.x = (_Input.Tex.x * TextureFrameSize.x) + TextureFramePos.x;
    NewOutPut.Tex.y = (_Input.Tex.y * TextureFrameSize.y) + TextureFramePos.y;
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
SamplerState LINEARWRAP : register(s0);

float4 Billboard_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    if (_Input.Tex.y < Slice.y)
    {
        clip(-1);
    }
    
    float4 TexColor = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
    
    if (TexColor.a == 0)
    {
        clip(-1);
    }
    
    float4 Result = (Tex.Sample(LINEARWRAP, _Input.Tex.xy) * MulColor) + PlusColor;
    
    if (1 <= Result.a)
    {
        Result.a = 1.0f;
    }
    
    return Result;
}
