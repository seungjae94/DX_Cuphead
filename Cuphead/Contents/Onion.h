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

	void StateChangeToAttack();
	bool IsFinished() const;

	void Damage(int _Damage) override;
protected:
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void RendererInit();
	void StateInit();
private:
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* OnionRenderer = nullptr;
	USpriteRenderer* LeftTearRenderer = nullptr;
	USpriteRenderer* RightTearRenderer = nullptr;
	UCollision* Collision = nullptr;
private:
	// ���� ó��
	UStateManager StateManager;
	
	const float AttackWaitTime = 2.0f;
	float AttackWaitTimer = 0.0f;

	UEngineRandom Random;
	const float AttackTotalTime = 10.0f;
	const float AttackInterval = 1.0f;
	float AttackTotalTimer = 0.0f;
	float AttackTimer = 0.0f;

	const float ShrinkWaitTime = 2.0f;
	float ShrinkTimer = 0.0f;
private:
	// ���� �Լ�
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
