#include "ContentsShader.hlsli"

Output ContentsShader_VS(Input _Input)
{
    Output NewOuput = (Output) 0;
    
    _Input.Pos += mf4PivotPos;
    NewOuput.Pos = mul(_Input.Pos, WorldViewProjection);
    
    NewOuput.PosLocal = _Input.Pos;
    
    if (UI == miResourceType)
    {
        if (miShaderType & BLOOM == 1)
        {
            
        }
        
        NewOuput.Tex.x = (_Input.Tex.x * mf2FrameDataSize.x) + mf2FrameDataPos.x;
        NewOuput.Tex.y = (_Input.Tex.y * mf2FrameDataSize.y) + mf2FrameDataPos.y;
    }
    else if (STATIC == miResourceType)
    {
        
    }
    else if (ANIMATOR == miResourceType)
    {
        
    }
    
    
    
    
      
    
    return NewOuput;
}

float4 ContentsShader_PS(Output _Input) : SV_Target0
{
    float4 Result = (float4) 0;
    
    if (UI == miResourceType)
    {
        
    }
    else if (STATIC == miResourceType)
    {
        
    }
    else if (ANIMATOR == miResourceType)
    {
        
    }

    return Result;
}