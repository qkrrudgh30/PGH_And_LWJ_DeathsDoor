#include "..\..\GameEngineResources\GameEngineShader\TransformHeader.fx"
#include "..\..\GameEngineResources\GameEngineShader\RenderOption.fx"

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
    uint Index : ROWINDEX;
    float4 ClonedTex : CLONEDTEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex : TEXCOORD;
    float4 ClonedTex : CLONEDTEXCOORD;
};

#define NONE        (0)
#define UI          (1)
#define STATIC      (2)
#define ANIMATOR    (3)

#define FADE    (0x01)
#define BLUR    (0x02)
#define BLOOM   (0x04)

#define BLUR_VERTICAL   (1)
#define BLUR_HORIZONTAL (2)
#define BLUR_BOTH       (3)

cbuffer ShaderingInfo : register(b1)
{
    int miResourceType;
    int miShaderType;
    int miIsUnityTexture;

	/*       2D UI      */
    float2 mf2FrameDataPos;
    float2 mf2FrameDataSize;
    float4 mf4PivotPos;

    unsigned int muBlurDirection;
    unsigned int muBlurAppliedCount;

    float mfBloomLuminanceThreshold;
    float mfBloomIntensity;

	/*    3D Static    */



	/*   3D Animator   */

};

Texture2D DiffuseTexture : register(t0);

Texture2D Tex : register(t1);
Texture2D ClonedTex : register(t2);

SamplerState LINEWRAP : register(s0);

