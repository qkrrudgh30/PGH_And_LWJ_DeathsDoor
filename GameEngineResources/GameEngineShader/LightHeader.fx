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



// StructuredBuffer<InstTransformData> AllInstancingTransformData : register(t12);