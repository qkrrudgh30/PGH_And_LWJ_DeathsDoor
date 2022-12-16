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
Output CalDeferredMerge_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

Texture2D DiffuseTex : register(t0);
Texture2D DiffuseLightTex : register(t1);
Texture2D SpacularLightTex : register(t2);
Texture2D AmbientLightTex : register(t3);
SamplerState POINTWRAP : register(s0);

float4 CalDeferredMerge_PS(Output _Input) : SV_Target0
{
    float4 DiffuseColor = DiffuseTex.Sample(POINTWRAP, _Input.Tex.xy);
    float4 DiffuseLight = DiffuseLightTex.Sample(POINTWRAP, _Input.Tex.xy);
    float4 SpacularLight = SpacularLightTex.Sample(POINTWRAP, _Input.Tex.xy);
    float4 AmbientLight = AmbientLightTex.Sample(POINTWRAP, _Input.Tex.xy);
    
    if (0 == DiffuseColor.a)
    {
        clip(-1);
    }
    
    float4 LightEffectResult = DiffuseColor * (DiffuseLight + SpacularLight + AmbientLight);
    LightEffectResult.w = 1.0f;
    
    return LightEffectResult;
}