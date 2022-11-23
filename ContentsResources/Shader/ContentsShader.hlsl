#include "ContentsShader.hlsli"

Output ContentsShader_VS(Input _Input)
{
    Output NewOuput = (Output) 0;
    
    _Input.Pos += mf4PivotPos;
    NewOuput.Pos = mul(_Input.Pos, WorldViewProjection);
    
    NewOuput.PosLocal = _Input.Pos;
    
    if (UI == miResourceType)
    {
        if ((miShaderType & BLOOM) == 1)
        {
            NewOuput.ClonedTex.x = (_Input.ClonedTex.x * mf2FrameDataSize.x) + mf2FrameDataPos.x;
            NewOuput.ClonedTex.y = (_Input.ClonedTex.y * mf2FrameDataSize.y) + mf2FrameDataPos.y;
        }
        
        NewOuput.Tex.x = (_Input.Tex.x * mf2FrameDataSize.x) + mf2FrameDataPos.x;
        NewOuput.Tex.y = (_Input.Tex.y * mf2FrameDataSize.y) + mf2FrameDataPos.y;
    }
    else if (STATIC == miResourceType)
    {
        if ((miShaderType & BLOOM)  == 1)
        {
            NewOuput.ClonedTex = _Input.ClonedTex;
        }
        
        NewOuput.Tex = _Input.Tex;
    }
    else if (ANIMATOR == miResourceType)
    {
        
    }
    
    return NewOuput;
}

float4 ContentsShader_PS(Output _Input) : SV_Target0
{
    float4 Result = (float4) 0;
    
    Result = Tex.Sample(LINEARWRAP, _Input.Tex.xy);
    
    if (UI == miResourceType)
    {
        if ((miShaderType & FADE) == 1)
        {
            Result.r = Result.r + 1e-2f;
            Result.g = Result.g + 1e-2f;
            Result.b = Result.b + 1e-2f;
    
            Result.r = clamp(Result.r + mfFadeAccValue, 0.f, 1.f);
            Result.g = clamp(Result.g + mfFadeAccValue, 0.f, 1.f);
            Result.b = clamp(Result.b + mfFadeAccValue, 0.f, 1.f);
        }
        
        if ((miShaderType & BLUR) == 1)
        {
            float2 UVSize = float2(1.f / mf2FrameDataSize.x, 1.f / mf2FrameDataSize.y);
            float2 UVCenterPos = _Input.Tex.xy;
            float2 UVStartPos = UVCenterPos + (-UVSize * 2.f);
            float2 UVCurrentPos = UVStartPos;
    
            if (0u == muBlurDirection || 2u == muBlurDirection)
            {
                for (uint count = 0; count <= muBlurAppliedCount; ++count)
                {
                    for (uint i = 0; i <= 4; ++i)
                    {
                        Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                        UVCurrentPos.x += UVSize.x;
                    }
                }
            }
    
            if (1u == muBlurDirection || 2u == muBlurDirection)
            {
                for (uint count = 0; count <= muBlurAppliedCount; ++count)
                {
                    for (uint i = 0; i <= 4; ++i)
                    {
                        Result += Tex.Sample(POINTWRAP, UVCurrentPos) * GaussianBlur1D[i];
                        UVCurrentPos.y += UVSize.y;
                    }
                }
            }
        }

    }
    else if (STATIC == miResourceType)
    {
        Result = DiffuseTexture.Sample(LINEARWRAP, _Input.Tex.xy);
    }
    else if (ANIMATOR == miResourceType)
    {
        
    }

    return Result;
}