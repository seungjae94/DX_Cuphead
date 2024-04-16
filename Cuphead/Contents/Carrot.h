#pragma once
#include "Enemy.h"

class ACarrot : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	ACarrot();
	~ACarrot();

	ACarrot(const ACarrot& _Other) = delete;
	ACarrot(ACarrot&& _Other) noexcept = delete;
	ACarrot& operator=(const ACarrot& _Other) = delete;
	ACarrot& operator=(ACarrot&& _Other) noexcept = delete;

	void PlayGroundIntroAnimation();
	void PlayCarrotIntroAnimation();
	void PlayGroundIdleAnimation();
	void PlayCarrotIdleAnimation();
	void SetCarrotFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void StateChangeToAttack();
	bool IsFinished();

	void Damage(int _Damage) override;

protected:


private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* CarrotRenderer = nullptr;
	UCollision* Collision = nullptr;
	USpriteRenderer* CollisionRenderer = nullptr;
private:
	// 로직 처리
	UStateManager StateManager;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void RendererInit();
	void StateInit();
private:
	// 상태 함수
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void AttackStart();
	void Attack(float _DeltaTime);
	void AttackEnd();

	void AttackWaitStart();
	void AttackWait(float _DeltaTime);
	void AttackWaitEnd();

	void FaintStart();
	void Faint(float _DeltaTime);
	void FaintEnd();

	void FinishStart();
	void Finish(float _DeltaTime);
	void FinishEnd();
};

