#include "PreCompile.h"
#include "BossAttack.h"
#include "cmath"
#include "Player.h"
#include "AnimationEffect.h"

ABossAttack::ABossAttack()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::BossAttack);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

ABossAttack::~ABossAttack()
{
}

void ABossAttack::SetRenderingOrder(ERenderingOrder _Order)
{
	Renderer->SetOrder(_Order);
}

void ABossAttack::SetSprite(std::string_view _ImageName)
{
	Renderer->SetSprite(_ImageName);
	Renderer->SetAutoSize(1.0f, true);
}

void ABossAttack::SetAnimation(std::string_view _AnimName, std::string_view _ImageName, float _Inter, bool _Loop)
{
	SetSprite(_ImageName);

	Renderer->CreateAnimation(_AnimName, _ImageName, _Inter, _Loop);
	Renderer->ChangeAnimation(_AnimName);
}

void ABossAttack::SetVelocity(const FVector& _Velocity, bool _RotateImage, const FVector& _RotationDeg)
{
	Velocity = _Velocity;

	if (true == _RotateImage)
	{
		Renderer->SetRotationDeg(_RotationDeg);
	}
}

void ABossAttack::SetChaseType(EChaseType _Type, AActor* _Target)
{
	ChaseType = _Type;
	Target = _Target;
}

void ABossAttack::SetChaseTime(float _Time)
{
	ChaseTimeSetted = true;
	ChaseTimer = _Time;
}

void ABossAttack::SetDestroyTime(float _Time)
{
	DelayCallBack(_Time, [this]() {
		if (nullptr == this)
		{
			return;
		}

		Destroy();
		});
}

void ABossAttack::SetParryable(bool _Value)
{
	Parryable = _Value;
}

void ABossAttack::SetDestroyable(bool _Value, std::string_view _DestroyAnimName, std::string_view _DestroySpriteName, float _Inter)
{
	Destroyable = _Value;
	DestroyAnimName = _DestroyAnimName;
	Renderer->CreateAnimation(DestroyAnimName, _DestroySpriteName, _Inter, false);
	Renderer->SetLastFrameCallback(DestroyAnimName, [this]() {
		Destroy();
	});
}

void ABossAttack::SetTrailEffect(FCreateAnimationParameter _AnimParam, float _TrailTime)
{
	TrailEffectAnimParam = _AnimParam;
	HasTrail = true;
	TrailTime = _TrailTime;
	TrailTimer = _TrailTime;
}

void ABossAttack::SetCollisionType(ECollisionType _Type)
{
	Collision->SetCollisionType(_Type);
}

void ABossAttack::SetCollisionPosition(const FVector& _Pos)
{
	Collision->SetPosition(_Pos);
}

void ABossAttack::SetCollisionScale(const FVector& _Scale)
{
	Collision->SetScale(_Scale);
}

void ABossAttack::SetVelocityGenerator(std::function<FVector()> _VelocityGenerator)
{
	VelocityGenerator = _VelocityGenerator;
}

void ABossAttack::BeginPlay()
{
	Super::BeginPlay();
}

void ABossAttack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 이동
	if (EChaseType::None == ChaseType)
	{
		if (nullptr != VelocityGenerator)
		{
			Velocity = VelocityGenerator();
		}
	}
	else if (EChaseType::Permanent == ChaseType)
	{
		ChaseTimer -= _DeltaTime;

		if (true == ChaseTimeSetted && ChaseTimer < 0.0f)
		{
			ChaseType = EChaseType::None;
			return;
		}

		float AngularSpeed = 90.0f;
		float Speed = Velocity.Size2D();

		FVector PrevDirection = -GetActorUpVector();
		FVector LookAtDirection = (Target->GetActorLocation() - GetActorLocation()).Normalize2DReturn();

		float PrevTheta = UCupheadMath::DirectionToDeg(PrevDirection);
		float LookAtTheta = UCupheadMath::DirectionToDeg(LookAtDirection);

		float DiffTheta = UCupheadMath::SubtractDeg(LookAtTheta, PrevTheta);

		if (DiffTheta > AngularSpeed * _DeltaTime)
		{
			DiffTheta = AngularSpeed * _DeltaTime;
		}
		else if (DiffTheta < -AngularSpeed * _DeltaTime)
		{
			DiffTheta = -AngularSpeed * _DeltaTime;
		}

		AddActorRotation({ 0.0f, 0.0f, DiffTheta});
		FVector NewDirection = -GetActorUpVector();

		Velocity = NewDirection * Speed;
	}

	AddActorLocation(Velocity * _DeltaTime);

	// 플레이어와 충돌 처리
	Collision->CollisionEnter(ECollisionGroup::PlayerHitBox, [=](std::shared_ptr<UCollision> _Collision)
		{
			// 상태, 애니메이션 변경
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());

			if (nullptr == Player)
			{
				return;
			}

			if (true == Parryable && true == Player->IsParrying())
			{
				Player->AddSuperMeter(1.0f);
				return;
			}

			Player->Damage();
		});

	// 총알과 충돌 처리
	if (true == Destroyable)
	{
		Collision->CollisionEnter(ECollisionGroup::Bullet, [this](std::shared_ptr<UCollision> _Other) 
			{
				Collision->SetActive(false);
				Renderer->ChangeAnimation(DestroyAnimName);
			});
	}

	// trail 이펙트
	if (true == HasTrail)
	{
		TrailTimer -= _DeltaTime;
		if (TrailTimer < 0.0f)
		{
			AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("Effect").get();
			Effect->SetActorLocation(GetActorLocation());
			ERenderingOrder AttackOrder = static_cast<ERenderingOrder>(Renderer->GetOrder());
			Effect->Init(AttackOrder, TrailEffectAnimParam, true);
			TrailTimer = TrailTime;
		}
	}
}
