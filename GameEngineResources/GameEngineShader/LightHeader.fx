struct LightData
{
    float4 LightPos;
    float4 LightDir;
    float4 LightRevDir;
};

cbuffer LightDatas : register(b8)
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
    // N
    _ViewNormal = normalize(_ViewNormal);
    float4 LightRevDir = normalize(_LightData.LightRevDir);
    
    float4 DiffuseLight = max(0.0f, dot(_ViewNormal.xyz, LightRevDir.xyz));
    DiffuseLight.w = 1.0f;
    return DiffuseLight;
}