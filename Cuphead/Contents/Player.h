#pragma once

class APlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

protected:

private:
	std::string PrevStateName = GStateName::Idle;

	const FVector JumpImpulse = { 0.0f, 1250.0f, 0.0f };
	const FVector Gravity = { 0.0f, -3200.0f, 0.0f };
	FVector Velocity = FVector::Zero;

	bool OnGroundValue = true;
	bool ApplyGravity = true;

	FVector ColCenter = FVector::Down * 50.0f;
	const float ColRadius = 40.0f;

	const float FireRadius = 40.0f;

	const float RunSpeed = 400.0f;
	const float DashSpeed = 4000.0f;

	EDirection Direction = EDirection::Right;
	UStateManager StateManager;
	USpriteRenderer* Renderer = nullptr;

	const float FireDelay = 0.15f;
	float FireTime = 0.0f;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void PhysicsUpdate(float _DeltaTime);
private:
	// �ִϸ��̼� �ʱ�ȭ
	void AnimationInit();

	// �ִϸ��̼� �Լ�
	void ChangeAnimationIf(bool _Cond, std::string_view _IfAnim, std::string_view _ElseAnim);

	// ���� �ʱ�ȭ
	void StateInit();

	// ���� �Լ�
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void RunStart();
	void Run(float _DeltaTime);
	void RunEnd();

	void JumpStart();
	void Jump(float _DeltaTime);
	void JumpEnd();

	void DashStart();
	void Dash(float _DeltaTime);
	void DashEnd();

	void SitStart();
	void Sit(float _DeltaTime);
	void SitEnd();

	void Fire();

private:
	// ��ƿ �Լ�
	bool IsPressArrowKey();
	bool IsDirectionLeft() const;
	void RefreshDirection();
	bool CheckCollision();
	FVector GetBulletSpawnLocation();
	EDirection GetBulletSpawnDirection();
};

