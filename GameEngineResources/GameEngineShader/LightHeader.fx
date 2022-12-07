struct LightData
{
    float4 LightColor;
    
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
    
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
};

cbuffer LightDatas : register(b13)
{
    int LightCount;
    LightData Lights[128];
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
    
    return DiffuseLight;
}

float4 CalDiffuseLights(float4 _ViewNormal)
{
    float4 DiffuseLights = (float4) 0.0f;
    
    for (int i = 0; i < LightCount; ++i)
    {
        DiffuseLights += CalDiffuseLight(_ViewNormal, Lights[i]);
    }
    
    //if (DiffuseLights.r > 1.0f)
    //{
    //    DiffuseLights.r = 1.0f;
    //}
    
    //if (DiffuseLights.g > 1.0f)
    //{
    //    DiffuseLights.g = 1.0f;
    //}
    
    //if (DiffuseLights.b > 1.0f)
    //{
    //    DiffuseLights.b = 1.0f;
    //}
    
    DiffuseLights.w = 1.0f;
    return DiffuseLights;

}