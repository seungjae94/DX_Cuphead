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
	Bullet->AnimationInit(
		FCreateAnimationParameter{ GAnimName::BulletMove, GImageName::BulletMove, 1 / 12.0f },
		FCreateAnimationParameter{ GAnimName::BulletDestroy, GImageName::BulletDestroy, 1 / 24.0f }
	);
	Bullet->SetDamage(4);
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

bool APlayer::EXAttack()
{
	if (false == IsDown('V'))
	{
		return false;
	}

	int SuperMeterInt = std::lround(SuperMeter);
	if (SuperMeterInt <= 0)
	{
		return false;
	}

	SuperMeter -= 1.0f;

	ChangeState(GStateName::EX);
	return true;
}

std::string APlayer::GetEXAnimationName()
{
	if (true == IsGroundCollisionOccur())
	{
		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			if (true == IsPress(VK_UP))
			{
				return GAnimName::PlayerGroundExHalfUp;
			}
			else if (true == IsPress(VK_DOWN))
			{
				return GAnimName::PlayerGroundExHalfDown;
			}
			else
			{
				return GAnimName::PlayerGroundExForward;
			}
		}
		else if (true == IsPress(VK_UP))
		{
			return GAnimName::PlayerGroundExUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			return GAnimName::PlayerGroundExDown;
		}
		else
		{
			// 아무 키도 누르지 않은 경우
			return GAnimName::PlayerGroundExForward;
		}
	}
	else
	{
		if (true == IsPress(VK_RIGHT) || true == IsPress(VK_LEFT))
		{
			if (true == IsPress(VK_UP))
			{
				return GAnimName::PlayerAirExHalfUp;
			}
			else if (true == IsPress(VK_DOWN))
			{
				return GAnimName::PlayerAirExHalfDown;
			}
			else
			{
				return GAnimName::PlayerAirExForward;
			}
		}
		else if (true == IsPress(VK_UP))
		{
			return GAnimName::PlayerAirExUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			return GAnimName::PlayerAirExDown;
		}
		else
		{
			// 아무 키도 누르지 않은 경우
			return GAnimName::PlayerAirExForward;
		}
	}
}

FVector APlayer::GetEXBulletSpawnLocation()
{
	FVector SpawnLocalLocation = FVector::Zero;

	EDirection BulletDirection = GetEXBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		SpawnLocalLocation = { -50.0f, 45.0f };
		break;
	case EDirection::Right:
		SpawnLocalLocation = { 50.0f, 45.0f };
		break;
	case EDirection::LeftUp:
		SpawnLocalLocation = { -35.0f, 55.0f };
		break;
	case EDirection::RightUp:
		SpawnLocalLocation = { 35.0f, 55.0f };
		break;
	case EDirection::LeftDown:
		SpawnLocalLocation = { -35.0f, -5.0f };
		break;
	case EDirection::RightDown:
		SpawnLocalLocation = { 35.0f, -5.0f };
		break;
	case EDirection::Up:
		if (EEngineDir::Left == Direction)
		{
			SpawnLocalLocation = { -20.0f, 70.0f };
		}
		SpawnLocalLocation = { 20.0f, 70.0f };
		break;
	case EDirection::Down:
		if (EEngineDir::Left == Direction)
		{
			SpawnLocalLocation = { -10.0f, -25.0f };
		}
		SpawnLocalLocation = { 10.0f, -25.0f };
		break;
	default:
		break;
	}

	return GetActorLocation() + SpawnLocalLocation;
}

FVector APlayer::GetEXDustLocation()
{
	FVector SpawnLocalLocation = FVector::Zero;

	EDirection BulletDirection = GetEXBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		SpawnLocalLocation = { 75.0f, 25.0f };
		break;
	case EDirection::Right:
		SpawnLocalLocation = { -65.0f, 85.0f };
		break;
	case EDirection::LeftUp:
		SpawnLocalLocation = { 25.0f, -20.0f };
		break;
	case EDirection::RightUp:
		SpawnLocalLocation = { -65.0f, 25.0f };
		break;
	case EDirection::LeftDown:
		SpawnLocalLocation = { 95.0f, 125.0f };
		break;
	case EDirection::RightDown:
		SpawnLocalLocation = { -25.0f, 155.0f };
		break;
	case EDirection::Up:
		SpawnLocalLocation = { -35.0f, 0.0f };
		break;
	case EDirection::Down:
		SpawnLocalLocation = { 40.0f, 175.0f };
		break;
	default:
		break;
	}

	return GetActorLocation() + SpawnLocalLocation;
}

FVector APlayer::GetEXDustRotation()
{
	EDirection Direction = GetEXBulletSpawnDirection();

	switch (Direction)
	{
	case EDirection::Right:
		return { 0.0f, 0.0f, 0.0f };
	case EDirection::RightUp:
		return { 0.0f, 0.0f, 45.0f };
	case EDirection::Up:
		return { 0.0f, 0.0f, 90.0f };
	case EDirection::LeftUp:
		return { 0.0f, 0.0f, 135.0f };
	case EDirection::Left:
		return { 0.0f, 0.0f, 180.0f };
	case EDirection::LeftDown:
		return { 0.0f, 0.0f, -135.0f };
	case EDirection::Down:
		return { 0.0f, 0.0f, -90.0f };
	case EDirection::RightDown:
		return { 0.0f, 0.0f, -45.0f };
	default:
		break;
	}

	return FVector::Zero;
}

EDirection APlayer::GetEXBulletSpawnDirection()
{
	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::LeftUp;
		}
		else if (true == IsPress(VK_DOWN))
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
		else if (true == IsPress(VK_DOWN))
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
		else if (true == IsPress(VK_DOWN))
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
		else if (true == IsPress(VK_DOWN))
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
