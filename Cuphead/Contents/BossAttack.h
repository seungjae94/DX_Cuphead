#pragma once

enum class EChaseType
{
	None,
	Temporal,
	Permanent,
	InitialPosition,
	Special
};

class ABossAttack : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABossAttack();
	~ABossAttack();

	ABossAttack(const ABossAttack& _Other) = delete;
	ABossAttack(ABossAttack&& _Other) noexcept = delete;
	ABossAttack& operator=(const ABossAttack& _Other) = delete;
	ABossAttack& operator=(ABossAttack&& _Other) noexcept = delete;

	void SetRenderingOrder(ERenderingOrder _Order);
	void SetSprite(std::string_view _ImageName);
	void SetAnimation(std::string_view _AnimName, std::string_view _ImageName, float _Inter, bool _Loop = true);

	void SetVelocity(const FVector& _Velocity, bool _RotateImage = false, const FVector& _RotationDeg = FVector::Zero);

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	USpriteRenderer* CollisionRenderer = nullptr;
private:
	// 로직
	bool Destroyable = false;
	bool Parryable = false;
	EChaseType ChaseType = EChaseType::None;

	FVector Velocity = FVector::Zero;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

