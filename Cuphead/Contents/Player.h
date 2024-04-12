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
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	// State
	std::string CurStateName = GStateName::Idle;
	std::string PrevStateName = GStateName::Idle;
	UStateManager StateManager;

	// Physics
	const FVector JumpImpulse = { 0.0f, 1250.0f, 0.0f };
	const FVector Gravity = { 0.0f, -3200.0f, 0.0f };
	FVector Velocity = FVector::Zero;
	bool OnGroundValue = true;
	bool ApplyGravity = true;

	FVector ColCenter = FVector::Down * 50.0f;
	const float ColRadius = 40.0f;

	// Fire
	const float FireDelay = 1 / 7.5f;
	float FireTime = 0.0f;
	const float FireRadius = 40.0f;
	const float Atk = 10.0f; /*���� �Ѿ��� �������� 4*/
	bool IsFire = false;

	// Move
	const float RunSpeed = 400.0f;
	const float DashSpeed = 800.0f;
	const float DashTime = 0.3f;
	EEngineDir Direction = EEngineDir::Right;
	bool IsDashed = false;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void PhysicsUpdate(float _DeltaTime);
	void DebugMsgUpdate(float _DeltaTime);
private:
	// �ִϸ��̼�
	void AnimationInit();
	void ChangeAnimationIf(bool _Cond, std::string_view _IfAnim, std::string_view _ElseAnim);

	// ����
	void StateInit();
	void ChangeState(std::string _StateName);

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
	bool CheckCollision(const FVector& _Direction);
	FVector GetBulletSpawnLocation();
	EDirection GetBulletSpawnDirection();
};

