#pragma once
#include <vector>
#include <string>

// 설명 :
class GameEngineRenderingEvent
{
public:
	std::string ResourcesName;

	unsigned int CurFrame;

	std::vector<unsigned int> Frames;

	float PlayTime;

	float CurFrameTime;

	float Inter; // 0.1f

	bool Loop;
	// 아틀라스 애니메이션

	class GameEngineRenderer* Renderer;

public:
	GameEngineRenderingEvent()
		: Loop(false)
		, Inter(0.1f)
		, CurFrame(-1)
		, CurFrameTime(0.0f)
		, PlayTime(0.0f)
	{

	}

	GameEngineRenderingEvent(const std::string _ResourcesName, unsigned int _Start, unsigned int _End, float _Inter, bool _Loop = true)
		: ResourcesName(_ResourcesName)
		, Loop(_Loop)
		, Inter(_Inter)
		, CurFrame(0)
		, CurFrameTime(0.0f)
		, PlayTime(0.0f)
	{
		for (unsigned int i = _Start; i <= _End; i++)
		{
			Frames.push_back(i);
		}
	}

	GameEngineRenderingEvent(const std::string _ResourcesName, const std::vector<unsigned int>& _Frames, float _Inter, bool _Loop = true)
		: ResourcesName(_ResourcesName)
		, Loop(_Loop)
		, Inter(_Inter)
		, Frames(_Frames)
		, CurFrameTime(0.0f)
		, CurFrame(0)
		, PlayTime(0.0f)
	{

	}


	GameEngineRenderingEvent(const std::string _ResourcesName, float _Inter, bool _Loop = true)
		: ResourcesName(_ResourcesName)
		, Loop(_Loop)
		, Inter(_Inter)
		, CurFrame(0)
		, CurFrameTime(0.0f)
		, PlayTime(0.0f)
	{

	}
};

