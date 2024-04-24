#pragma once
#include "AnimationEffect.h"

enum class EChaseType
{
	None,
	Temporal,
	Permanent,
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
	void SetChaseType(EChaseType _Type, AActor* _Target);
	void SetChaseTime(float _Time);
	void SetDestroyTime(float _Time);
	void SetParryable(bool _Value);
	void SetDestroyable(bool _Value, std::string_view _DestroyAnimName, std::string_view _DestroySpriteName, float _Inter);
	void SetTrailEffect(FCreateAnimationParameter _AnimParam, float _TrailTime);

	void SetCollisionType(ECollisionType _Type);
	void SetCollisionPosition(const FVector& _Pos);
	void SetCollisionScale(const FVector& _Scale);
	void SetVelocityGenerator(std::function<FVector()> _VelocityGenerator);
protected:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	void Tick(float _DeltaTime) override;
private:
	// 로직
	bool Destroyable = false;
	std::string DestroyAnimName;

	bool Parryable = false;

	bool ChaseTimeSetted = false;
	float ChaseTimer = 0.0f;
	EChaseType ChaseType = EChaseType::None;

	bool HasTrail = false;
	float TrailTime = 0.0f;
	float TrailTimer = 0.0f;
	FCreateAnimationParameter TrailEffectAnimParam;

	FVector Velocity = FVector::Zero;

	AActor* Target = nullptr;

	std::function<FVector()> VelocityGenerator;
private:
	void BeginPlay() override;
};

