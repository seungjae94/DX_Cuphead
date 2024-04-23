#pragma once
#include "FaintableBoss.h"

class APotato : public AFaintableBoss
{
	GENERATED_BODY(AFaintableBoss)
public:
	APotato();
	~APotato();

	APotato(const APotato& _Other) = delete;
	APotato(APotato&& _Other) noexcept = delete;
	APotato& operator=(const APotato& _Other) = delete;
	APotato& operator=(APotato&& _Other) noexcept = delete;

	void PlayGroundIntroAnimation();
	void PlayPotatoIntroAnimation();
	void PlayGroundIdleAnimation();
	void PlayPotatoIdleAnimation();
	void SetPotatoFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void StateChangeToAttack();

	void Damage(int _Damage) override;

protected:

private:
	// ������Ʈ
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* PotatoRenderer = nullptr;
private:
	// ���� ó��
	int AttackPhase = -1;
	const float AttackWaitTime = 3.0f;
	float AttackWaitTimer = 0.0f;

	const int MaxAttackCount = 4;
	int AttackCount = 0;

	const std::vector<float> AttackDelays = { 1.0f, 0.8f, 0.6f };
	float AttackTimer = 0.0f;

	const float ShrinkWaitTime = 2.0f;
	float ShrinkTimer = 0.0f;

private:
	void BeginPlay() override;
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

	void AttackWaitStart();
	void AttackWait(float _DeltaTime);
	void AttackWaitEnd();

	void FaintStart() override;
	void Faint(float _DeltaTime) override;
	void FaintEnd() override;
};

