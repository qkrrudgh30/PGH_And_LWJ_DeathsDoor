// #include "myshader.hlsli"
#include "..\..\GameEngineResources\GameEngineShader\RenderOption.fx"

// SV_POSITION 시맨틱
// 그래픽카드에게 이녀석은 이런 부류니까 니가 자동으로 처리하는 녀석이 있으면 하고.



struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};


struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};


// 그래픽카드에서 이뤄지는것.
Output YEffect_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001
Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 YEffect_PS(Output _Input) : SV_Target0
{
    // 지금 이 색깔은?
    
    float4 Color = Tex.Sample(Smp, _Input.Tex.xy);
    
    float TempDeltaTime = SumDeltaTime;
    
    TempDeltaTime = clamp(TempDeltaTime, 0.0f, 1.0f);
    
    if (_Input.Tex.y > sin(TempDeltaTime))
    {
        clip(-1);
    }
    
    return Color;
}
