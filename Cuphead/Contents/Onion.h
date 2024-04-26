#pragma once
#include "FaintableBoss.h"

class AOnion : public AFaintableBoss
{
	GENERATED_BODY(AFaintableBoss)
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

	void Damage(int _Damage) override;
protected:
private:
	void BeginPlay() override;
private:
	void RendererInit();
	void StateInit();
private:
	// 렌더러
	USpriteRenderer* GroundFrontRenderer = nullptr;
	UCropSpriteRenderer* OnionRenderer = nullptr;
	USpriteRenderer* LeftTearRenderer = nullptr;
	USpriteRenderer* RightTearRenderer = nullptr;
private:
	// 로직 처리
	const float AttackWaitTime = 2.0f;
	float AttackWaitTimer = 0.0f;

	const float AttackTotalTime = 10.0f;
	const float AttackInterval = 1.0f;
	float AttackTotalTimer = 0.0f;
	float AttackTimer = 0.0f;

	const float ShrinkWaitTime = 2.0f;
	float ShrinkTimer = 0.0f;
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

	void FaintStart() override;
	void Faint(float _DeltaTime) override;
	void FaintEnd() override;
};

