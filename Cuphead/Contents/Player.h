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
	FVector Velocity = FVector::Zero;

	const float JumpAcc = 2000.0f;
	const float Gravity = 980.0f;
	const float RunSpeed = 500.0f;
	EDirection Direction = EDirection::Right;
	UStateManager StateManager;
	USpriteRenderer* Renderer = nullptr;

	const float FireDelay = 0.25f;
	float FireTime = 0.0f;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

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

private:
	// ��ƿ �Լ�
	bool IsPressArrowKey();
	bool IsDirectionLeft() const;
	void RefreshDirection();
};

