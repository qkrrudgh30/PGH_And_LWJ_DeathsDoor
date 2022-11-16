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

	std::shared_ptr<class GameEngineFBXStaticRenderer> GetFBXRenderer() { return mpFBXStaticRenderer; };
	void SetPriorityInitialize(void) { mbPriorityInitialzed = false; };
	void UnsetWithCollision(void) { mbWithCollision = false; };

	std::shared_ptr<class GameEngineCollision> GetCollider() { return mpCollider; }

protected:
	void Start() override;
	void Update(float _DeltaTime);
	void End() {}


private:
	std::shared_ptr<class GameEngineFBXStaticRenderer> mpFBXStaticRenderer;
	std::shared_ptr<class GameEngineCollision> mpCollider;
	bool mbPriorityInitialzed;
	bool mbWithCollision;

	bool m_bRenderOncheck = false;

	CollisionReturn PlayerCollision(GameEngineCollision* _This, GameEngineCollision* _Other);




};

