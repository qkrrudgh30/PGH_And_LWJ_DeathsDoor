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

	class GameEngineFBXStaticRenderer* GetFBXRenderer() { return mpFBXStaticRenderer; };
	void SetPriorityInitialize(void) { mbPriorityInitialzed = false; };
	void UnsetWithCollision(void) { mbWithCollision = false; };

	class GameEngineCollision* GetCollider() { return mpCollider; }

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}


private:
	class GameEngineFBXStaticRenderer* mpFBXStaticRenderer;
	class GameEngineCollision* mpCollider;
	bool mbPriorityInitialzed;
	bool mbWithCollision;

};

