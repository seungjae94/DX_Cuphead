#pragma once
#include "Boss.h"

class APlayer;

class ADragon1 : public ABoss
{
	GENERATED_BODY(ABoss)
public:
	ADragon1();
	~ADragon1();

	ADragon1(const ADragon1& _Other) = delete;
	ADragon1(ADragon1&& _Other) noexcept = delete;
	ADragon1& operator=(const ADragon1& _Other) = delete;
	ADragon1& operator=(ADragon1&& _Other) noexcept = delete;

	void PlayIntroAnimation();

	void ChangeAnimation(std::string_view _AnimName);
	void SetState(std::string_view StateName);
	void SetFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void Damage(int _Damage) override;

	void SetPlayer(APlayer* _Player);

protected:


private:
	// 컴포넌트
	USpriteRenderer* BodyRenderer = nullptr;
	//USpriteRenderer* TailRenderer = nullptr;
private:
	// 로직 처리
	const float AttackDecisionTime = 3.0f;
	float AttackDecisionTimer = 3.0f;

	// 메테오
	const int MaxAttackCount = 2;
	int AttackCount = 2;
	const float AttackInterval = 3.0f;
	float AttackTimer = AttackInterval;

	// 빔
	APlayer* Player = nullptr;
private:
	void BeginPlay() override;
private:
	void RendererInit();
	void StateInit();
private:
	// 상태 함수
	void IntroStart();
	void Intro(float _DeltaTime);
	void IntroEnd();

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
private:
	void SpawnAttackProj();
	void SpawnBeamProj();
};

