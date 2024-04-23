#include "PreCompile.h"
#include "FaintableBoss.h"
#include "AnimationEffect.h"

AFaintableBoss::AFaintableBoss()
{
}

AFaintableBoss::~AFaintableBoss()
{
}

bool AFaintableBoss::IsFainted() const
{
	return "Faint" == StateManager.GetCurStateName();
}

void AFaintableBoss::SetFaintRange(const float4& _FaintRange)
{
	FaintRange = _FaintRange;
}

void AFaintableBoss::BeginPlay()
{
	Super::BeginPlay();

	StateManager.CreateState("Faint");
	StateManager.SetFunction("Faint",
		std::bind(&AFaintableBoss::FaintStart, this),
		std::bind(&AFaintableBoss::Faint, this, std::placeholders::_1),
		std::bind(&AFaintableBoss::FaintEnd, this)
	);
}

void AFaintableBoss::FaintStart()
{
	BossExplosionTimer = 0.0f;
	FaintTimer = FaintTime;
}

void AFaintableBoss::Faint(float _DeltaTime)
{
	if (false == FaintActive)
	{
		return;
	}

	FaintTimer -= _DeltaTime;
	BossExplosionTimer -= _DeltaTime;

	if (FaintTimer < 0.0f)
	{
		StateManager.ChangeState("Finish");
	}

	if (BossExplosionTimer < 0.0f)
	{
		AAnimationEffect* Explosion = GetWorld()->SpawnActor<AAnimationEffect>("Explosion").get();
		Explosion->Init(ERenderingOrder::Collider, FCreateAnimationParameter{ "boss_explosion", "boss_explosion", 1 / 24.0f }, true);

		float PosX = Random.RandomFloat(FaintRange.X, FaintRange.Y);
		float PosY = Random.RandomFloat(FaintRange.Z, FaintRange.W);
		Explosion->SetActorLocation(GetActorLocation() + FVector{ PosX, PosY });

		BossExplosionTimer = BossExplosionInterval;
	}
}

void AFaintableBoss::FaintEnd()
{
}
