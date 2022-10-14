// #include "myshader.hlsli"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.

// t1

// Create("TransformData");
#include "TransformHeader.fx"

// cbuffer Color : 
// TestColor;
struct Input
{
    float4 Pos : POSITION;
};

struct Output
{
    // 레스터라이저한테 뷰포트를 곱해서 이녀석으로 픽셀을 건져내줘.
    float4 Pos : SV_POSITION;
    // 레스터라이저한테 뷰포트를 곱해서 이녀석으로 픽셀을 건져내줘.
    float4 PosWorld : POSITION;
};

//cbuffer ResultColor : register(b2)
//{
//    float4 PlusColor;
//    float4 MultyplyColor;
//}



// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

Output Debug3D_VS(Input _Input)
{
    // 쉐이더의 경우에는 대부분의 상황에서 형변환이 가능하다.
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosWorld.xyz = _Input.Pos.xyz;
    NewOutPut.PosWorld.w = 1.0f;
    return NewOutPut;
}

cbuffer DebugInfo : register(b8)
{
    int4 Type;
    float4 Color;
}

float4 Debug3D_PS(Output _Input) : SV_Target0
{
    // 원을 그리거나
    // 박스를 그릴수도 있죠?
    
    
    if (Type.x == 0 && length(_Input.PosWorld.xyz) > 0.7f)
    {
        clip(-1);
    }
        
    
    return Color;
}
