#pragma once
#include <string.h>
#include "GameEngineRes.h"
#include "GameEngineInstancingBuffer.h"

// 설명 :
class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineIndexBuffer;
class GameEngineMesh : public GameEngineRes<GameEngineMesh>
{
public:
	static std::shared_ptr < GameEngineMesh> Create(const std::string& _Name);

	static std::shared_ptr < GameEngineMesh> Create(const std::string& _Name, const std::string& _Vtx, const std::string& _Idx);

	static std::shared_ptr < GameEngineMesh> Create(std::shared_ptr < GameEngineVertexBuffer> _Vtx, std::shared_ptr < GameEngineIndexBuffer> _Idx);

public:
	// constrcuter destructer
	GameEngineMesh();
	~GameEngineMesh();

	// delete Function
	GameEngineMesh(const GameEngineMesh& _Other) = delete;
	GameEngineMesh(GameEngineMesh&& _Other) noexcept = delete;
	GameEngineMesh& operator=(const GameEngineMesh& _Other) = delete;
	GameEngineMesh& operator=(GameEngineMesh&& _Other) noexcept = delete;

	// 점의 구조를 알려주는 인풋레이아웃도 이 단계에서 세팅된다.
	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	// 그렇게 해서 변환된 점을 어떻게 조합해서 면으로 만들것이냐를 여기서 처리합니다.
	// 인덱스 버퍼가 세팅된다.
	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	void SetInputAssembler1VertexBuffer(std::shared_ptr < GameEngineVertexBuffer> _Res);
	void SetInputAssembler2IndexBuffer(std::shared_ptr < GameEngineIndexBuffer> _Res);

	void InputAssembler1VertexBufferSetting();

	void InputAssembler2IndexBufferSetting();

	void Setting();

	void SettingInstancing(std::shared_ptr < GameEngineInstancingBuffer> _Buffer);

	void Render();

	void RenderInstancing(size_t _InstancingCount);

	const class GameEngineLayOutDesc& GetLayOutDesc();

protected:

private:
	std::shared_ptr < GameEngineVertexBuffer> VertexBuffer; // 인풋어셈블러1 세팅
	// HLSL이라는 다른 언어를 사용하는 단계에요.
	// HLSL은 그래픽카드에 특정 데이터에 대한 처리 단계를 우리가 직접 작성해서
	// 그래픽카드에 올려줄수 있는 겁니다.
	std::shared_ptr < GameEngineIndexBuffer> IndexBuffer; // 인풋어셈블러2 세팅

};

