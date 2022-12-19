struct LightData
{
    float4      f4LightColor;            
    float4      f4AmbientLightColor;
    
    float       fDiffuseLightIntensity;   
    float       fSpecularLightIntensity;  
    float       fAmbientLightIntensity;   
    float       fSpecularLightPower;      
    
    float4      f4LightPosition;    
    float4      f4LightDirection;
    float4      f4LightReverseDirection;  
    
    float4      f4LightPositionWithView;
    float4      f4LightDirectionWithView; 
    float4      f4LightReverseDirectionWithView;
    
    float4      f4CameraPosition;
    
};

cbuffer LightDatas : register(b13)
{
    int LightCount;
    LightData Lights[128];
};

float4 CalculateDiffuseLight(float4 _f4ViewNormal, LightData _LightData)
{
    _f4ViewNormal = normalize(_f4ViewNormal);
    float4 f4LightReverseDirection = normalize(_LightData.f4LightReverseDirectionWithView);
    
    float4 f4DiffuseLight = max(0.0f, dot(_f4ViewNormal.xyz, f4LightReverseDirection.xyz));
    f4DiffuseLight *= _LightData.f4LightColor;
    f4DiffuseLight.w = 1.0f;
    
    return f4DiffuseLight * _LightData.fDiffuseLightIntensity;
}

float4 CalculateDiffuseLights(float4 _f4ViewNormal)
{
    float4 f4DiffuseLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        f4DiffuseLights += CalculateDiffuseLight(_f4ViewNormal, Lights[i]);
    }
    f4DiffuseLights.w = 1.0f;
    
    return f4DiffuseLights;
}

float4 CalculateAmbientLight(LightData _LightData)
{
    return _LightData.f4AmbientLightColor * _LightData.fAmbientLightIntensity;
}

float4 CalculateAmbientLights()
{
    float4 f4AmbientLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        f4AmbientLights += CalculateAmbientLight(Lights[i]);
    }
    f4AmbientLights.w = 1.0f;
    
    return f4AmbientLights;
}

float4 CalculateSpacularLight(float4 _f4ViewPosition, float4 _f4ViewNormal, LightData _LightData)
{
    float4 f4SpacularLight = (float4) 0.0f;
    
    _f4ViewNormal.xyz = normalize(_f4ViewNormal.xyz);
    _LightData.f4LightReverseDirectionWithView.xyz = normalize(_LightData.f4LightReverseDirectionWithView.xyz);
    
    // N
    float3 Reflection = normalize(2.0f * _f4ViewNormal.xyz * dot(_LightData.f4LightReverseDirectionWithView.xyz, _f4ViewNormal.xyz) - _LightData.f4LightReverseDirectionWithView.xyz);
    // L
    float3 Eye = normalize(_LightData.f4CameraPosition.xyz - _f4ViewPosition.xyz);
    
    float fResult = max(0.0f, dot(Reflection.xyz, Eye.xyz));
    f4SpacularLight.xyz = pow(fResult, _LightData.fSpecularLightPower);
    f4SpacularLight.w = 1.0f;
    
    return f4SpacularLight * _LightData.fSpecularLightPower;
}


float4 CalculateSpacularLights(float4 _f4ViewPosition, float4 _f4ViewNormal)
{
    float4 f4SpacularLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        f4SpacularLights += CalculateSpacularLight(_f4ViewPosition, _f4ViewNormal, Lights[i]);
    }
    
    f4SpacularLights.w = 1.0f;
    return f4SpacularLights;
}

