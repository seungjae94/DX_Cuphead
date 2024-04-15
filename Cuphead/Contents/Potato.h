#pragma once

class APotato : public AActor
{
	GENERATED_BODY(AActor)
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
	void SetGroundFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);
	void SetPotatoFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

	void TransToAttackState();
	bool IsFinished();

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* PotatoRenderer = nullptr;

private:
	// 로직 처리
	UStateManager StateManager;
	int AttackPhase = -1;
	const float AttackWaitTime = 3.0f;
	float AttackWaitTimer = 0.0f;

	const int MaxAttackCount = 4;
	int AttackCount = 0;

	const std::vector<float> AttackDelays = { 1.0f, 0.8f, 0.6f };
	float AttackTimer = 0.0f;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugMsgUpdate(float _DeltaTime);
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
};

