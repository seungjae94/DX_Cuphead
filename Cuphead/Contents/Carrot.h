#pragma once
#include "FinalBoss.h"

class APlayer;

class ACarrot : public AFinalBoss
{
	GENERATED_BODY(AFinalBoss)
public:
	ACarrot();
	~ACarrot();

	ACarrot(const ACarrot& _Other) = delete;
	ACarrot(ACarrot&& _Other) noexcept = delete;
	ACarrot& operator=(const ACarrot& _Other) = delete;
	ACarrot& operator=(ACarrot&& _Other) noexcept = delete;

	void PlayGroundIntroAnimation();
	void PlayCarrotIntroAnimation();
	void PlayCarrotIdleAnimation();
	void SetCarrotFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void StateChangeToAttack();

	void Damage(int _Damage) override;

	void SetPlayer(APlayer* _Player);

protected:

private:
	void BeginPlay() override;
private:
	void RendererInit();
	void StateInit();
private:
	// ������Ʈ
	USpriteRenderer* GroundFrontRenderer = nullptr;
	USpriteRenderer* GroundBackRenderer = nullptr;
	USpriteRenderer* CarrotRenderer = nullptr;
	USpriteRenderer* EyeRenderer = nullptr;

	// ���� �÷��̾�
	UEngineSoundPlayer CarrotAttackLoopSoundPlayer;
private:
	// ���� ó��
	APlayer* Player = nullptr;
	const int MaxAttackCount = 4;
	const float AttackInterval = 2.0f;
	int AttackCount = 4;
	float AttackTimer = 0.0f;


	const int MaxBeamCount = 3;
	int BeamCount = 3;

	const float BeamInterval = 2.0f;
	float BeamTimer = 0.0f;

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

	void BeamStart();
	void Beam(float _DeltaTime);
	void BeamEnd();

	void FaintStart() override;
	void Faint(float _DeltaTime) override;
	void FaintEnd() override;
};

