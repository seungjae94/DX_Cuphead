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
	const FVector JumpImpulse = { 0.0f, 1250.0f, 0.0f };
	const FVector Gravity = { 0.0f, -3200.0f, 0.0f };
	FVector Velocity = FVector::Zero;

	bool OnGroundValue = true;
	bool ApplyGravity = false;

	FVector ColCenter = FVector::Down * 50.0f;
	const float ColRadius = 40.0f;

	const float RunSpeed = 400.0f;

	EDirection Direction = EDirection::Right;
	UStateManager StateManager;
	USpriteRenderer* Renderer = nullptr;

	const float FireDelay = 0.25f;
	float FireTime = 0.0f;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void PhysicsUpdate(float _DeltaTime);
private:
	// 애니메이션 초기화
	void AnimationInit();

	// 애니메이션 함수
	void ChangeAnimationIf(bool _Cond, std::string_view _IfAnim, std::string_view _ElseAnim);

	// 상태 초기화
	void StateInit();

	// 상태 함수
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

private:
	// 유틸 함수
	bool IsPressArrowKey();
	bool IsDirectionLeft() const;
	void RefreshDirection();
	bool CheckCollision();
};

