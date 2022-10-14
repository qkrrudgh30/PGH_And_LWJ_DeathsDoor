cbuffer TransformData : register(b0)
{
    float4 LocalPosition;
    float4 LocalRotation;
    float4 LocalScaling;
    
    float4 WorldPosition;
    float4 WorldRotation;
    float4 WorldScaling;
    
    float4x4 LocalPositionMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalScalingMatrix;
    
    float4x4 LocalWorldMatrix;
    float4x4 WorldWorldMatrix;
    float4x4 View;
    float4x4 Projection;
    
    float4x4 WorldView;
    float4x4 WorldViewProjection;
};

struct TransformData
{
    float4 LocalPosition;
    float4 LocalRotation;
    float4 LocalScaling;
    
    float4 WorldPosition;
    float4 WorldRotation;
    float4 WorldScaling;
    
    float4x4 LocalPositionMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalScalingMatrix;
    
    float4x4 LocalWorldMatrix;
    float4x4 WorldWorldMatrix;
    float4x4 View;
    float4x4 Projection;
    
    float4x4 WorldView;
    float4x4 WorldViewProjection;
};

StructuredBuffer<TransformData> AllInstancingTransformData : register(t12);