#pragma once
#include "Enemy.h"

class APlayer;

class ADragon1 : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	ADragon1();
	~ADragon1();

	ADragon1(const ADragon1& _Other) = delete;
	ADragon1(ADragon1&& _Other) noexcept = delete;
	ADragon1& operator=(const ADragon1& _Other) = delete;
	ADragon1& operator=(ADragon1&& _Other) noexcept = delete;

	void PlayIntroAnimation();
	bool IsFinished();

	void Damage(int _Damage) override;

	void SetPlayer(APlayer* _Player);

protected:


private:
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* BodyRenderer = nullptr;
	//USpriteRenderer* TailRenderer = nullptr;
	UCollision* Collision = nullptr;
private:
	// ���� ó��
	UStateManager StateManager;
	UEngineRandom Random;
	const float AttackDecisionTime = 3.0f;
	float AttackDecisionTimer = 3.0f;

	// ���׿�
	const int MaxAttackCount = 2;
	int AttackCount = 2;
	const float AttackInterval = 3.0f;
	float AttackTimer = AttackInterval;

	// ��
	APlayer* Player = nullptr;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void RendererInit();
	void StateInit();
private:
	// ���� �Լ�
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void AttackStart();
	void Attack(float _DeltaTime);
	void AttackEnd();

	void BeamStart();
	void Beam(float _DeltaTime);
	void BeamEnd();

	void RunAwayStart();
	void RunAway(float _DeltaTime);
	void RunAwayEnd();

	void FinishStart();
	void Finish(float _DeltaTime);
	void FinishEnd();
private:
	void SpawnAttackProj();
	void SpawnBeamProj();
};

