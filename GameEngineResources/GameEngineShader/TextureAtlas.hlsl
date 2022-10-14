// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

#include "TransformHeader.fx"
#include "RenderOption.fx"

// 0                                                                                                1 
// 0□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□1

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
    
    // 1. 무조건 int 하나만 사용합니다.
    // 인스턴싱 데이터
    uint Index : ROWINDEX;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
};

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};


Output TextureAtlas_VS(Input _Input)
{
    // -0.5, 0.5,     0.5 0.5
    // 0.5, 0.5,     0.5 0.5
    
    Output NewOutPut = (Output)0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // 버텍스가 몇번째 버텍스 인지 알수가 없다.
    // NewOutPut.Tex
    // 00    10
    
    //// 10    11
    
    //TextureFrameSize.x -= 0.5f;
    //TextureFrameSize.y -= 0.5f;
    //TextureFramePos.x -= 0.5f;
    //TextureFramePos.y -= 0.5f;
    
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
SamplerState Smp : register(s0);
float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex.x < Slice.x)
    {
        clip(-1);
    }
    
    if (_Input.Tex.y < Slice.y)
    {
        clip(-1);
    }
    
    float4 TexColor = Tex.Sample(Smp, _Input.Tex.xy);
    
    if (TexColor.a == 0)
    {
        clip(-1);
    }
    
    float4 Result = (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
    
    if (1 <= Result.a)
    {
        Result.a = 1.0f;

    }
    
    // Result.a = 1.0f;
    
    return Result;
}


Output TextureAtlas_VSINST(Input _Input)
{
    // _Input.Index => 인스턴싱 버퍼를 통해서 전달.
    // 인스턴싱 버퍼를 통해서 행렬을 전달하지 않은 이유는 인스턴싱 버퍼를 매번 새롭게 정의해야 하기 때문다.
    // 
    
    // -0.5, 0.5,     0.5 0.5
    // 0.5, 0.5,     0.5 0.5
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Pos = mul(_Input.Pos, AllInstancingTransformData[_Input.Index].WorldViewProjection);
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}


//Texture2D Tex : register(t0);
//SamplerState Smp : register(s0);
//float4 TextureAtlas_PSINST(Output _Input) : SV_Target0
//{
//    if (_Input.Tex.x < Slice.x)
//    {
//        clip(-1);
//    }
    
//    if (_Input.Tex.y < Slice.y)
//    {
//        clip(-1);
//    }
    
//    float4 TexColor = Tex.Sample(Smp, _Input.Tex.xy);
    
//    if (TexColor.a == 0)
//    {
//        clip(-1);
//    }
    
//    return (Tex.Sample(Smp, _Input.Tex.xy) * MulColor) + PlusColor;
//}
