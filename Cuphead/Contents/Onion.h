#pragma once
#include "Enemy.h"

class AOnion : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	AOnion();
	~AOnion();

	AOnion(const AOnion& _Other) = delete;
	AOnion(AOnion&& _Other) noexcept = delete;
	AOnion& operator=(const AOnion& _Other) = delete;
	AOnion& operator=(AOnion&& _Other) noexcept = delete;

	void PlayGroundIntroAnimation();
	void PlayOnionIntroAnimation();

	void PlayGroundIdleAnimation();
	void PlayOnionIdleAnimation();

	void SetOnionFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void Damage(int _Damage) override;

	void StateChangeToAttack();

protected:
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void RendererInit();
	void StateInit();
private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* OnionRenderer = nullptr;
	UCollision* Collision = nullptr;
private:
	// 로직 처리
	UStateManager StateManager;
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

