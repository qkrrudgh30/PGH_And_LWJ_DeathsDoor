#pragma once
#include "UnitBase.h"

// Ό³Έν :
class WorldLight : public UnitBase
{
public:
	// constrcuter destructer
	WorldLight();
	~WorldLight();

	// delete Function
	WorldLight(const WorldLight& _Other) = delete;
	WorldLight(WorldLight&& _Other) noexcept = delete;
	WorldLight& operator=(const WorldLight& _Other) = delete;
	WorldLight& operator=(WorldLight&& _Other) noexcept = delete;

	static WorldLight* GetWorldLight() { return s_rptrWorldLight; }
	static float4 GetWorldLightColor() { return s_f4LightColor; }
	static void SetWorldLightColor(float4 _f4Color) { s_f4LightColor = _f4Color; }

protected:
	void Start() override;
	void Update(float _fDeltatime);
	void End() {}

private:

public:

protected:

private:
	static WorldLight* s_rptrWorldLight;
	static float4 s_f4LightColor;

};

