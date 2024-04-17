#pragma once

enum class RunState
{
	Run,
	RunShootHalfUp,
	RunShootForward,
};

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

	void Damage();
	void AddSuperMeter(float _Value);
	bool IsParrying();

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
private:
	// State
	std::string CurStateName = GStateName::Idle;
	std::string PrevStateName = GStateName::Idle;
	std::string CurAnimName = GAnimName::PlayerIdle;
	UStateManager StateManager;

	// Physics
	const FVector JumpImpulse = { 0.0f, 1250.0f, 0.0f };
	const FVector Gravity = { 0.0f, -3200.0f, 0.0f };
	FVector Velocity = FVector::Zero;
	bool OnGroundValue = true;
	bool ApplyGravity = true;

	FVector ColBotPoint = FVector::Zero;
	FVector ColLeftPoint = { -30.0f, 50.0f, 0.0f };
	FVector ColRightPoint = { 30.0f, 50.0f, 0.0f };

	// Fire
	const float FireDelay = 1 / 7.5f;
	float FireTime = 0.0f;
	const float Atk = 10.0f; /*원작 총알의 데미지는 4*/
	bool IsFire = false;
	FTransform BulletSpawnTrans;

	// Move
	const float RunSpeed = 400.0f;
	const float DashSpeed = 800.0f;
	const float DashTime = 0.3f;
	const FVector DashDustPos = { 0.0f, 50.0f, 0.0f };
	EEngineDir Direction = EEngineDir::Right;
	bool IsDashed = false;

	// Collision
	const FVector CollisionDefaultPosition = { 0.0f, 62.0f };
	const FVector CollisionDefaultScale = { 100.0f, 125.0f };
	const FVector CollisionSitPosition = { 0.0f, 32.0f };
	const FVector CollisionSitScale = {100.0f, 50.0f};
	const float NoHitTime = 1.0f;

private:
	int Hp = 3;
	float SuperMeter = 0.0f;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SpriteDirUpdate(float _DeltaTime);
	void PhysicsUpdate(float _DeltaTime);
	void DebugUpdate(float _DeltaTime);
private:
	// 애니메이션
	void AnimationInit();
	void ChangeAnimationIfChanged(std::string _AnimName);

	// 상태
	void StateInit();
	void ChangeState(std::string _StateName);

	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void AimStart();
	void Aim(float _DeltaTime);
	void AimEnd();

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

	void HitStart();
	void Hit(float _DeltaTime);
	void HitEnd();

private:
	// 공격
	void Fire();
	FVector GetBulletSpawnLocation();
	FVector GetBulletSpawnLocation_Jump();
	FVector GetBulletSpawnLocation_Idle();
	FVector GetBulletSpawnLocation_Run();
	FVector GetBulletSpawnLocation_Sit();
	EDirection GetBulletSpawnDirection();

private:
	// 유틸 함수
	bool IsPressArrowKey();
	bool IsDirectionLeft() const;
	void RefreshDirection();
	void RefreshIdleAnimation();
	void RefreshRunAnimation();

	bool CheckCollision(const FVector& _ColPoint);
};

