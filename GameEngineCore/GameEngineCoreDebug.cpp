#include "PreCompile.h"
#include "GameEngineCoreDebug.h"
#include <GameEngineBase/GameEngineTransform.h>
#include "GameEngineShaderResourcesHelper.h"
#include "GameEngineMaterial.h"
#include "GameEngineCore.h"
#include "GameEngineCamera.h"
#include "GameEngineTexture.h"
#include "GameEngineRenderer.h"

namespace GameEngineDebug
{
	enum class DebugRenderType
	{
		Sphere,
		Box,
	};

	struct DebugInfo
	{
		int Type[4];
		float4 Color;

	public:
		DebugInfo(DebugRenderType _Type, const float4& _Color)
			: Type{static_cast<int>(_Type)}
			, Color(_Color)
		{

		}
	};

	struct DebugRenderData 
	{
	public:
		DebugInfo Info;
		TransformData Data;
		GameEngineTexture* Texture;
	};

	std::vector<DebugRenderData> DebugData = std::vector<DebugRenderData>();

	void DrawBox(const GameEngineTransform& _Trans, const float4& _Color) 
	{
		DrawBox(_Trans, GameEngineCore::GetCurLevel()->GetMainCamera(), _Color);
	}

	void DrawBox(const float4& _Pos, const float4& _Scale, const float4& _Rot, const float4& _Color)
	{
		static GameEngineTransform DebugTrans;
		DebugTrans.SetLocalPosition(_Pos);
		DebugTrans.SetLocalRotate(_Rot);
		DebugTrans.SetLocalScale(_Scale);
		DrawBox(DebugTrans, GameEngineCore::GetCurLevel()->GetMainCamera(), _Color);
	}


	void DrawBox(const GameEngineTransform& _Trans, GameEngineCamera* _Camera, const float4& _Color)
	{
		static GameEngineTransform DebugTrans;

		DebugTrans.Copy(_Trans);
		DebugTrans.SetView(_Camera->GetView());
		DebugTrans.SetProjection(_Camera->GetProjectionMatrix());
		DebugTrans.CalculateWorldViewProjection();

		DebugData.push_back(DebugRenderData{ DebugInfo(DebugRenderType::Box, _Color) , DebugTrans.GetTransformData(), nullptr });
	}

	void DrawTexture(const std::string& _Texture, const float4& _Pos, const float4& _Scale, const float4& _Rot /*= float4::ZERO*/)
	{
		GameEngineTexture* FindTexture = GameEngineTexture::Find(_Texture);
		DrawTexture(FindTexture, GameEngineCore::GetCurLevel()->GetMainCamera(), _Pos, _Rot, _Scale);
	}

	void DrawTexture(const std::string& _Texture, GameEngineCamera* _Camera, const float4& _Pos, const float4& _Scale, const float4& _Rot /*= float4::ZERO*/)
	{
		GameEngineTexture* FindTexture = GameEngineTexture::Find(_Texture);
		DrawTexture(FindTexture, _Camera, _Pos, _Rot, _Scale);
	}

	void DrawTexture(GameEngineTexture* _Texture, const float4& _Pos, const float4& _Scale, const float4& _Rot)
	{
		DrawTexture(_Texture, GameEngineCore::GetCurLevel()->GetMainCamera(), _Pos, _Rot, _Scale);
	}

	void DrawTexture(GameEngineTexture* _Texture, GameEngineCamera* _Camera, const float4& _Pos, const float4& _Scale, const float4& _Rot)
	{
		static GameEngineTransform DebugTrans;

		if (nullptr == _Texture)
		{
			MsgBoxAssert("존재하지 않는 텍스처를 디버그 랜더링 하려고 했습니다");
		}

		DebugTrans.SetLocalPosition(_Pos);
		DebugTrans.SetLocalRotate(_Rot);
		DebugTrans.SetLocalScale(_Scale);

		if (_Scale.CompareInt2D(float4::ZERO))
		{
			DebugTrans.SetLocalScale(_Texture->GetScale());
		}

		DebugTrans.SetView(_Camera->GetView());
		DebugTrans.SetProjection(_Camera->GetProjectionMatrix());
		DebugTrans.CalculateWorldViewProjection();


		DebugData.push_back(DebugRenderData{ DebugInfo(DebugRenderType::Box, float4::WHITE) , DebugTrans.GetTransformData(), _Texture });

	}


	void DrawSphere(const GameEngineTransform& _Trans, const float4& _Color) 
	{
		DrawSphere(_Trans, GameEngineCore::GetCurLevel()->GetMainCamera(), _Color);
	}
	void DrawSphere(const GameEngineTransform& _Trans, GameEngineCamera* _Camera, const float4& _Color) 
	{
		static GameEngineTransform DebugTrans;

		DebugTrans.Copy(_Trans);
		DebugTrans.SetView(_Camera->GetView());
		DebugTrans.SetProjection(_Camera->GetProjectionMatrix());
		DebugTrans.CalculateWorldViewProjection();

		DebugData.push_back(DebugRenderData{ DebugInfo(DebugRenderType::Sphere, _Color) , DebugTrans.GetTransformData() });
	}

	GameEngineRenderUnit* DebugRenderUnit;
	GameEngineRenderUnit* DebugTextureRenderUnit;

	void Debug3DDestroy() 
	{
		if (nullptr != DebugRenderUnit)
		{
			delete DebugRenderUnit;
			DebugRenderUnit = nullptr;
		}

		if (nullptr != DebugTextureRenderUnit)
		{
			delete DebugTextureRenderUnit;
			DebugTextureRenderUnit = nullptr;
		}
	}

	void Debug3DInitialize() 
	{
		static bool IsOnce = false;

		if (true == IsOnce)
		{
			return;
		}

		DebugRenderUnit = new GameEngineRenderUnit();

		DebugRenderUnit->SetMesh("Box");
		DebugRenderUnit->SetPipeLine("3DDebug");

		//DebugRenderingPipeLine = GameEngineMaterial::Find("3DDebug");
		//DebugShaderResources.ResourcesCheck(DebugRenderingPipeLine);

		DebugTextureRenderUnit = new GameEngineRenderUnit();

		DebugTextureRenderUnit->SetPipeLine("3DDebug");

		//TextureRenderingPipeLine = GameEngineMaterial::Find("DebugTexture");
		//TextureShaderResources.ResourcesCheck(TextureRenderingPipeLine);

		IsOnce = true;
	}


	void Debug3DRender()
	{
		for (size_t i = 0; i < DebugData.size(); i++)
		{
			if (nullptr == DebugData[i].Texture)
			{
				DebugRenderUnit->ShaderResources.SetConstantBufferLink("TransformData", DebugData[i].Data);
				DebugRenderUnit->ShaderResources.SetConstantBufferLink("DebugInfo", DebugData[i].Info);
				DebugRenderUnit->Render(GameEngineTime::GetDeltaTime());
			}
			else 
			{
				DebugTextureRenderUnit->ShaderResources.SetConstantBufferLink("TransformData", DebugData[i].Data);
				DebugTextureRenderUnit->ShaderResources.SetConstantBufferLink("DebugInfo", DebugData[i].Info);
				DebugTextureRenderUnit->ShaderResources.SetTexture("Tex", DebugData[i].Texture);
				DebugTextureRenderUnit->Render(GameEngineTime::GetDeltaTime());
			}
		}

		DebugData.clear();
		int a = 0;
	}
	
};