#pragma once

enum class RunState
{
	Run,
	RunShootHalfUp,
	RunShootForward,
};

class AAnimationEffect;

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

	void SetColMapName(std::string_view _ColMapName);

	void Damage();
	void AddSuperMeter(float _Value);
	bool IsParrying();
	void ParrySuccess();
	int GetDamageCoeff() const;

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* HitBox = nullptr;
	UCollision* BotCollision = nullptr;
	UCollision* LeftCollision = nullptr;
	UCollision* RightCollision = nullptr;
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

	// Fire
	const float FireDelay = 1 / 7.5f;
	float FireTime = 0.0f;
	const float Atk = 10.0f; /*원작 총알의 데미지는 4*/
	bool IsFire = false;
	FTransform BulletSpawnTrans;
	AAnimationEffect* HandBulletSpawnEffect = nullptr;
	UEngineRandom Random;

	// Move
	const float RunSpeed = 400.0f;
	const float DashSpeed = 800.0f;
	const float DashTime = 0.3f;
	float DashTimer = 0.0f;
	const FVector DashDustPos = { 0.0f, 50.0f, 0.0f };
	EEngineDir Direction = EEngineDir::Right;
	bool IsDashed = false;

	// Hit
	const float HitTime = 0.5f;
	float HitTimer = 0.0f;
	bool IsGroundHit = false;
	float DamageGroundY = -320.0f;

	// Jump
	const float DownJumpCheckScale = 10.0f;

	// Collision
	std::string ColMapName = "";
	const FVector BodyCollisionDefaultPosition = { 0.0f, 62.0f };
	const FVector BodyCollisionDefaultScale = { 60.0f, 80.0f };
	const FVector BodyCollisionSitPosition = { 0.0f, 32.0f };
	const FVector BodyCollisionSitScale = {60.0f, 30.0f};
	const float NoHitTime = 2.0f;

	// Parry
	bool IsParryingValue = false;

	// Sit
	bool IsSitting = false;
	bool IsStanding = false;

	// UI
	UImage* HpWidget = nullptr;
	std::vector<UImage*> CardWidgets;
private:
	int Hp = 3;
	float SuperMeter = 2.0f;
	bool DamageX10 = true;
	int DamageCoeff = 1;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void SpriteDirUpdate(float _DeltaTime);
	void PlatformMovementUpdate(float _DeltaTime);
	void ChildRenderersUpdate(float _DeltaTime);
	void DebugUpdate(float _DeltaTime);
private:
	// 애니메이션
	void AnimationInit();

	// UI
	void UIInit();
	void RefreshSuperMeterUI();

	// 상태
	void StateInit();
	void ChangeState(std::string _StateName);

	void IntroStart();
	void Intro(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void RunStart();
	void Run(float _DeltaTime);
	void RunEnd();

	void JumpStart();
	void Jump(float _DeltaTime);
	void JumpEnd();

	void ParryStart();
	void Parry(float _DeltaTime);
	void ParryEnd();

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
	FVector GetBulletSpawnLocalLocation_Jump();
	FVector GetBulletSpawnLocalLocation_Idle();
	FVector GetBulletSpawnLocalLocation_Run();
	FVector GetBulletSpawnLocalLocation_Sit();
	EDirection GetBulletSpawnDirection();

private:
	// 달리기 먼지 발생
	const float RunDustInterval = 0.25f;
	float RunDustTimer = 0.0f;
	void SpawnRunDustEffect(float _DeltaTime);

private:
	// 유틸 함수
	bool IsPressArrowKey();
	bool IsDirectionLeft() const;
	void RefreshDirection();
	void RefreshIdleAnimation();
	void RefreshRunAnimation();
	void RefreshSitAnimation();

	bool IsLeftCollisionOccur();
	bool IsRightCollisionOccur();
	bool IsGroundCollisionOccur();
	void MoveUpToGround();
	bool TestDownJump();

	bool CheckPixelCollision(const FVector& _Point);
	void DamageCheat();
};

