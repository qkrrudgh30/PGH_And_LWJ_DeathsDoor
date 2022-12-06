#include "PreCompile.h"
#include "BillboardRenderer.h"

#include <GameEngineCore/GameEngineTextureRenderer.h>

BillboardRenderer::BillboardRenderer() 
	: mBillboardInfo{}
	, mPixelData{}
{
}

BillboardRenderer::~BillboardRenderer() 
{
}

void BillboardRenderer::Start()
{
	GameEngineDefaultRenderer::Start();

	SetBillboardRenderingSetting();
}

void BillboardRenderer::Update(float _fDeltatime)
{
	float4 f4EyePosition = GEngine::GetCurrentLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	float4 f4EyeFocus = GetTransform().GetWorldPosition() - GEngine::GetCurrentLevel()->GetMainCamera()->GetTransform().GetWorldPosition();
	float4 f4Up = float4::UP;

	mBillboardInfo.mf4x4MainCameraRotation = GetMainCameraRotation(f4EyePosition, f4EyeFocus, f4Up);
}

void BillboardRenderer::InitializeBillboard()
{
	mBillboardInfo.mf4FrameData.PosX = 0.f;
	mBillboardInfo.mf4FrameData.PosY = 0.f;
	mBillboardInfo.mf4FrameData.SizeX = 1.f;
	mBillboardInfo.mf4FrameData.SizeY = 1.f;

	mBillboardInfo.mf4PivotPos = float4::ZERO;

	mBillboardInfo.muOnOffBillboard = 0u;
	mBillboardInfo.mf4x4MainCameraRotation = float4x4{};
}

void BillboardRenderer::SetBillboardRenderingSetting()
{
	InitializeBillboard();

	SetMaterial("Billboard");

	GetShaderResources().SetConstantBufferLink("BillboardInfo", mBillboardInfo);
	GetShaderResources().SetConstantBufferLink("PixelData", mPixelData);
}

void BillboardRenderer::SetPivot(PIVOTMODE _mode)
{
	switch (_mode)
	{
	case PIVOTMODE::CENTER:
		mBillboardInfo.mf4PivotPos = float4::ZERO;
		break;
	case PIVOTMODE::BOT:
		mBillboardInfo.mf4PivotPos = float4(0.0f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::TOP:
		mBillboardInfo.mf4PivotPos = float4(0.0f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFT:
		mBillboardInfo.mf4PivotPos = float4(0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHT:
		mBillboardInfo.mf4PivotPos = float4(-0.5f, 0.0f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTTOP:
		mBillboardInfo.mf4PivotPos = float4(0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTTOP:
		mBillboardInfo.mf4PivotPos = float4(-0.5f, -0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::LEFTBOT:
		mBillboardInfo.mf4PivotPos = float4(0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::RIGHTBOT:
		mBillboardInfo.mf4PivotPos = float4(-0.5f, 0.5f, 0.0f, 0.0f);
		break;
	case PIVOTMODE::CUSTOM:
		break;
	default:
		break;
	}
}

void BillboardRenderer::SetBillboardInfo(unsigned int _uOnOffBillboard)
{
	mBillboardInfo.muOnOffBillboard = _uOnOffBillboard;
}

void BillboardRenderer::SetTexture(const std::string& _strTextureName)
{
	mwpCurrTexture = GetShaderResources().SetTexture("Tex", _strTextureName);
}

float4x4 BillboardRenderer::GetMainCameraRotation(const float4& _f4EyePosition, const float4& _f4EyeFocus, const float4& _f4Up)
{
	float4 R2 = float4::Normalize3DReturn(_f4EyeFocus);

	float4 R0 = float4::Cross3D(_f4Up, R2);
	R0.Normalize3D();

	float4 R1 = float4::Cross3D(R2, R0);

	float4 P = float4{ 0.f, 0.f, 0.f, 0.f };

	float4 Control = { 0xff, 0xff, 0xff, 0 };
	float4x4 Mat;
	Mat.ArrV[0] = float4::Select(P, R0, Control);
	Mat.ArrV[1] = float4::Select(P, R1, Control);
	Mat.ArrV[2] = float4::Select(P, R2, Control);
	Mat.ArrV[3] = float4{ 0.f, 0.f, 0.f, 1.f };

	Mat.Transpose();

	return Mat;

	/*float4 R2 = float4::Normalize3DReturn(_f4EyeFocus);

	float4 R0 = float4::Cross3D(_f4Up, R2);
	R0.Normalize3D();

	float4 R1 = float4::Cross3D(R2, R0);

	float4 P = float4{ 0.f, 0.f, 0.f, 0.f };

	float4 Control = { 0xff, 0xff, 0xff, 0 };
	float4x4 Mat;
	Mat.ArrV[0] = float4::Select(P, R0, Control);
	Mat.ArrV[1] = float4::Select(P, R1, Control);
	Mat.ArrV[2] = float4::Select(P, R2, Control);
	Mat.ArrV[3] = float4{ 0.f, 0.f, 0.f, 1.f };

	Mat.Transpose();

	return Mat;*/
}
