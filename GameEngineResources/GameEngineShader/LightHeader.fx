struct LightData
{
    float4x4 LightViewMatrix;
    float4x4 LightViewInverseMatrix;
    float4x4 LightProjectionMatrix;
    float4x4 LightProjectionInverseMatrix;
    float4x4 LightViewProjectionMatrix;
    float4x4 CameraViewInverseMatrix;
    float LightNear;
    float LightFar;
    
    float4 LightColor;
    float4 AmbientLight;
    float DifLightPower;
    float SpcLightPower;
    float AmbLightPower;
    float SpcPow;

    
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
    
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    
    float4 CameraPosition;
    
};

cbuffer LightDatas : register(b13)
{
    int LightCount;
    LightData Lights[64];
};

// 빛에는 3가지 종류가 있습니다.
// 난반사광 Diffuse 빛의 방향에 따라서 표면적으로 어떻게 분포될거냐?
// 정반사광 Specular 빛이 반사된게 내눈에 얼마나 들어오느냐.


// 환경광 가장 리얼한 빛을 표현하려면 환경광을 제대로 계산해야 하는데.
// 계산이 불가능에 가깝기 때문에 통계에 가까운 공식으로 처리하거나.
// 그냥 상수로 넣어버리는데. 선생님은 상수로

// StructuredBuffer<InstTransformData> AllInstancingTransformData : register(t12);

float4 CalDiffuseLight(float4 _ViewNormal, LightData _LightData)
{
    _ViewNormal = normalize(_ViewNormal);
    float4 LightRevDir = normalize(_LightData.ViewLightRevDir);
    
    float4 DiffuseLight = max(0.0f, dot(_ViewNormal.xyz, LightRevDir.xyz));
    DiffuseLight *= _LightData.LightColor;
    DiffuseLight.w = 1.0f;
    
    return DiffuseLight * _LightData.DifLightPower;
}

float4 CalDiffuseLights(float4 _ViewNormal)
{
    float4 ResultLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalDiffuseLight(_ViewNormal, Lights[i]);
    }
    
    ResultLights.w = 1.0f;
    return ResultLights;

}

float4 CalAmbientLight(LightData _LightData)
{
    return _LightData.AmbientLight * _LightData.AmbLightPower;
}


float4 CalAmbientLight()
{
    float4 ResultLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalAmbientLight(Lights[i]);
    }
    
    ResultLights.w = 1.0f;
    return ResultLights;
}


float4 CalSpacularLight(float4 _ViewPosition, float4 _ViewNormal, LightData _LightData)
{
    float4 SpacularLight = (float4) 0.0f;
    
    _ViewNormal.xyz = normalize(_ViewNormal.xyz);
    _LightData.ViewLightRevDir.xyz = normalize(_LightData.ViewLightRevDir.xyz);
    
    // N
    float3 Reflection = normalize(2.0f * _ViewNormal.xyz * dot(_LightData.ViewLightRevDir.xyz, _ViewNormal.xyz) - _LightData.ViewLightRevDir.xyz);
    // L
    float3 Eye = normalize(_LightData.CameraPosition.xyz - _ViewPosition.xyz);
    
    // 1인 부분만 살리고 나머지 부분은 
    // 0~1사이의 값이 나오니까.
    // 0.5
    float Result = max(0.0f, dot(Reflection.xyz, Eye.xyz));
    SpacularLight.xyz = pow(Result, _LightData.SpcPow);
    SpacularLight.w = 1.0f;
    
    return SpacularLight * _LightData.SpcLightPower;
}


float4 CalSpacularLight(float4 _ViewPosition, float4 _ViewNormal)
{
    float4 ResultLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        ResultLights += CalSpacularLight(_ViewPosition, _ViewNormal, Lights[i]);
    }
    
    ResultLights.w = 1.0f;
    return ResultLights;
}

