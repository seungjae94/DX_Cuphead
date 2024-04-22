#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "AnimationEffect.h"

void APlayer::Fire()
{
	if (false == IsPress('X'))
	{
		IsFire = false;
		return;
	}

	IsFire = true;

	if (FireTime > 0.0f)
	{
		return;
	}

	std::shared_ptr<ABullet> Bullet = GetWorld()->SpawnActor<ABullet>("Bullet");
	Bullet->SetActorLocation(GetBulletSpawnLocation());
	Bullet->SetDirection(GetBulletSpawnDirection());
	Bullet->SetPlayer(this);

	// 총알 스폰 이펙트
	float RandomAngle = Random.RandomFloat(0.0f, 360.0f);
	AAnimationEffect* SpawnEffect = GetWorld()->SpawnActor<AAnimationEffect>("SpawnEffect").get();
	SpawnEffect->SetActorLocation(GetBulletSpawnLocation());
	SpawnEffect->SetActorRotation({ 0.0f, 0.0f, RandomAngle });
	SpawnEffect->Init(ERenderingOrder::BulletSpawn, FCreateAnimationParameter{ "bullet_spawn", "bullet_spawn.png", 1 / 24.0f }, true);

	// 점프 또는 패리 상태일 경우에만 현재 위치에 고정
	if ("Jump" != CurStateName && "Parry" != CurStateName)
	{
		if (nullptr != HandBulletSpawnEffect)
		{
			HandBulletSpawnEffect->Destroy();
		}

		HandBulletSpawnEffect = SpawnEffect;
		HandBulletSpawnEffect->SetAutoDestroyCallback([this]() {
			HandBulletSpawnEffect = nullptr;
			});
	}

	FireTime = FireDelay;
}

FVector APlayer::GetBulletSpawnLocation()
{
	FVector BulletSpawnLocalLocation = FVector::Zero;

	if (GStateName::Jump == CurStateName)
	{
		BulletSpawnLocalLocation = GetBulletSpawnLocalLocation_Jump();
	}
	else if (GStateName::Idle == CurStateName)
	{
		BulletSpawnLocalLocation = GetBulletSpawnLocalLocation_Idle();
	}
	else if (GStateName::Run == CurStateName)
	{
		BulletSpawnLocalLocation = GetBulletSpawnLocalLocation_Run();
	}
	else if (GStateName::Sit == CurStateName)
	{
		BulletSpawnLocalLocation = GetBulletSpawnLocalLocation_Sit();
	}

	return GetActorLocation() + BulletSpawnLocalLocation;
}

FVector APlayer::GetBulletSpawnLocalLocation_Jump()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -50.0f, 25.0f };
	case EDirection::Right:
		return { 50.0f, 25.0f };
	case EDirection::LeftUp:
		return { -35.0f, 45.0f };
	case EDirection::RightUp:
		return { 35.0f, 45.0f };
	case EDirection::LeftDown:
		return { -35.0f, -5.0f };
	case EDirection::RightDown:
		return { 35.0f, -5.0f };
	case EDirection::Up:
		if (EEngineDir::Left == Direction)
		{
			return { -20.0f, 70.0f };
		}
		return { 20.0f, 70.0f };
	case EDirection::Down:
		if (EEngineDir::Left == Direction)
		{
			return { -15.0f, -20.0f };
		}
		return { 15.0f, -20.0f };
	default:
		break;
	}

	return FVector::Zero;
}

FVector APlayer::GetBulletSpawnLocalLocation_Idle()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -70.0f, 80.0f };
	case EDirection::Right:
		return { 70.0f, 80.0f };
	case EDirection::Up:
		if (EEngineDir::Left == Direction)
		{
			return { -20.0f, 165.0f };
		}
		return { 20.0f, 165.0f };
	case EDirection::Down:
		if (EEngineDir::Left == Direction)
		{
			return { -15.0f, 20.0f };
		}
		return { 15.0f, 20.0f };
	default:
		break;
	}

	return FVector::Zero;
}

FVector APlayer::GetBulletSpawnLocalLocation_Run()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -60.0f, 65.0f };
	case EDirection::Right:
		return { 60.0f, 65.0f };
	case EDirection::LeftUp:
		return { -60.0f, 120.0f };
	case EDirection::RightUp:
		return { 60.0f, 120.0f };
	default:
		break;
	}

	return FVector::Zero;
}

FVector APlayer::GetBulletSpawnLocalLocation_Sit()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -85.0f, 50.0f };
	case EDirection::Right:
		return { 85.0f, 50.0f };
	default:
		break;
	}

	return FVector::Zero;
}

EDirection APlayer::GetBulletSpawnDirection()
{
	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::LeftUp;
		}
		else if (true == IsPress(VK_DOWN) && GStateName::Jump == CurStateName)
		{
			return EDirection::LeftDown;
		}
	}

	if (true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::RightUp;
		}
		else if (true == IsPress(VK_DOWN) && GStateName::Jump == CurStateName)
		{
			return EDirection::RightDown;
		}
	}

	if (Direction == EEngineDir::Left)
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::Up;
		}
		else if (true == IsPress(VK_DOWN) && GStateName::Jump == CurStateName)
		{
			return EDirection::Down;
		}
		else
		{
			return EDirection::Left;
		}
	}

	if (Direction == EEngineDir::Right)
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::Up;
		}
		else if (true == IsPress(VK_DOWN) && GStateName::Jump == CurStateName)
		{
			return EDirection::Down;
		}
		else
		{
			return EDirection::Right;
		}
	}

	return EDirection::Right;
}

void APlayer::SpawnRunDustEffect(float _DeltaTime)
{
	RunDustTimer -= _DeltaTime;
	if (RunDustTimer >= 0.0f)
	{
		return;
	}

	AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("RunDust").get();
	Effect->SetActorLocation(GetActorLocation() + FVector::Up * 45.0f);
	Effect->Init(ERenderingOrder::Character, { GAnimName::PlayerRunDust, GImageName::PlayerRunDust, 1 / 24.0f }, true);

	RunDustTimer = RunDustInterval;
}
