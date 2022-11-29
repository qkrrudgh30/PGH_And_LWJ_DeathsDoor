
struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
    float4 ClonedTex : CLONEDTEXCOORD;
};

cbuffer BloomInfo : register(b1)
{
    uint muOnOff;
    uint muAppliedArea;
    float mfLuminance;
    float mfIntence;
    float4 mf4WindowSize;
}

Output ContentsBloom_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    NewOutPut.ClonedTex = _Input.Tex;
    
    return NewOutPut;
}

Texture2D Tex : register(t0);
SamplerState POINTWRAP : register(s0);
float4 ContentsBloom_PS(Output _Input) : SV_Target0
{
    float2 f2UVSize = float2(1.0f / mf4WindowSize.x, 1.0f / mf4WindowSize.y);
    float2 f2UVCenterPos = _Input.Tex.xy;
    float2 f2UVStartPos = f2UVCenterPos + (-f2UVSize * 2.f);
    float2 f2UVCurrentPos = f2UVStartPos;
    float4 f4Result = (float) 0.f;
    
    if (0u == muOnOff)
    {
        f4Result = Tex.Sample(POINTWRAP, _Input.Tex.xy);
        return f4Result;
    }
    
    for (int y = 0; y < muAppliedArea; ++y)
    {
        for (int x = 0; x < muAppliedArea; ++x)
        {
            f4Result += Tex.Sample(POINTWRAP, f2UVCurrentPos) * (1.f / ((muAppliedArea * muAppliedArea) - mfIntence));
        
            f2UVCurrentPos.x += f2UVSize.x;
        }
        
        f2UVCurrentPos.x = f2UVStartPos.x;
        f2UVCurrentPos.y += f2UVSize.y;
    }
    
    float4 f4ClonedTex = Tex.Sample(POINTWRAP, _Input.Tex.xy);
    const float relativeLuminance = f4ClonedTex.r * 0.2126f + f4ClonedTex.g * 0.7152f + f4ClonedTex.b * 0.0722f;
    if (relativeLuminance < mfLuminance)
    {
        f4Result.r += f4ClonedTex.r;
        f4Result.g += f4ClonedTex.g;
        f4Result.b += f4ClonedTex.b;
    }
    
    f4Result.r += 1e-2f;
    f4Result.g += 1e-2f;
    f4Result.b += 1e-2f;
    
    if (f4Result.a <= 0.0f)
    {
        clip(-1);
    }
    
    return f4Result;
}
