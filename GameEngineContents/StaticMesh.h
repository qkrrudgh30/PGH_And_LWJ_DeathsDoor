#pragma once

#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class StaticMesh : public GameEngineActor
{
public:
	// constrcuter destructer
	StaticMesh();
	~StaticMesh();

	// delete Function
	StaticMesh(const StaticMesh& _Other) = delete;
	StaticMesh(StaticMesh&& _Other) noexcept = delete;
	StaticMesh& operator=(const StaticMesh& _Other) = delete;
	StaticMesh& operator=(StaticMesh&& _Other) noexcept = delete;

	class GameEngineFBXRenderer* GetFBXRenderer() { return mpFBXRenderer; };
	void SetPriorityInitialize(void) { mbPriorityInitialzed = false; };
	void UnsetWithCollision(void) { mbWithCollision = false; };

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}


private:
	class GameEngineFBXRenderer* mpFBXRenderer;
	class GameEngineCollision* mpCollider;
	bool mbPriorityInitialzed;
	bool mbWithCollision;

};

