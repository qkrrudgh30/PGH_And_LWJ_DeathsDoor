#pragma once
#include <GameEngineCore/GameEngineRenderer.h>

struct ShaderingInfo
{
	int             miResourceType;
	int				miShaderType;
	int				miIsUnityTexture;

	/*       2D UI      */
	float4			mf4FrameData;
	float4			mf4PivotPos;

	float			mfFadeAccValue;

	unsigned int	muBlurDirection;
	unsigned int	muBlurAppliedCount;

	float			mfBloomLuminanceThreshold;
	float			mfBloomIntensity;


	/*    3D Static    */



	/*   3D Animator   */

};

class GameEngineTexture;
class GameEngineRenderUnit;
class GameEngineShaderResourcesHelper;
class ContentsRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	ContentsRenderer();
	~ContentsRenderer();

	// delete Function
	ContentsRenderer(const ContentsRenderer& _Other) = delete;
	ContentsRenderer(ContentsRenderer&& _Other) noexcept = delete;
	ContentsRenderer& operator=(const ContentsRenderer& _Other) = delete;
	ContentsRenderer& operator=(ContentsRenderer&& _Other) noexcept = delete;

	inline std::weak_ptr<GameEngineRenderUnit> GetRenderUnit() { return mwptrRenderingUnit; }
	inline GameEngineShaderResourcesHelper& GetShaderResources() { return mwptrRenderingUnit.lock()->ShaderResources; }

	virtual void Render(float _fDeltatime);
	void SetTexture(const std::string& _strTextureName);
	void SetMesh(const std::string& _strMeshName);
	void SetMaterial(const std::string& _strMaterialName);
	void SetShader(ShaderBitFlag _eShaderType);

	/*      2D UI      */
	void SetPivot();
	void SetTexture();
	void Set2DUIShaderingInfo();

	/*    3D Static    */
	void Set3DStaticShaderingInfo();

	/*   3D Animator   */
	void Set3DAnimatorShaderingInfo();


protected:
	void Start(void) override;
	void Update(float _fDeltatime) override;

private:
	void InitializeShaderingInfo(void);
	void SetRenderingPipeline(void);

	std::weak_ptr<GameEngineTexture>		mwptrCurrent2DTexture;
	std::weak_ptr<GameEngineRenderUnit>		mwptrRenderingUnit;

	ShaderingInfo							mShaderingInfo;

};

