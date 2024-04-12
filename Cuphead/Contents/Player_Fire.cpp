#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"

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
	Bullet->SetActorLocation(GetActorLocation() + GetBulletSpawnLocation());
	Bullet->SetDirection(GetBulletSpawnDirection());

	FireTime = FireDelay;
}

FVector APlayer::GetBulletSpawnLocation()
{
	if (GStateName::Jump == CurStateName)
	{
		return GetBulletSpawnLocation_Jump();
	}

	if (GStateName::Idle == CurStateName)
	{
		return GetBulletSpawnLocation_Idle();
	}

	if (GStateName::Run == CurStateName)
	{
		return GetBulletSpawnLocation_Run();
	}

	if (GStateName::Sit == CurStateName)
	{
		return GetBulletSpawnLocation_Sit();
	}

	return FVector::Zero;
}

FVector APlayer::GetBulletSpawnLocation_Jump()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -30.0f, 25.0f };
	case EDirection::Right:
		return { 30.0f, 25.0f };
	case EDirection::LeftUp:
		return { -25.0f, 45.0f };
	case EDirection::RightUp:
		return { 25.0f, 45.0f };
	case EDirection::LeftDown:
		return { -25.0f, -5.0f };
	case EDirection::RightDown:
		return { 20.0f, -5.0f };
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

FVector APlayer::GetBulletSpawnLocation_Idle()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -35.0f, 75.0f };
	case EDirection::Right:
		return { 35.0f, 75.0f };
	case EDirection::Up:
		if (EEngineDir::Left == Direction)
		{
			return { -20.0f, 120.0f };
		}
		return { 20.0f, 120.0f };
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

FVector APlayer::GetBulletSpawnLocation_Run()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -30.0f, 65.0f };
	case EDirection::Right:
		return { 30.0f, 65.0f };
	case EDirection::LeftUp:
		return { -25.0f, 80.0f };
	case EDirection::RightUp:
		return { 25.0f, 80.0f };
	default:
		break;
	}

	return FVector::Zero;
}

FVector APlayer::GetBulletSpawnLocation_Sit()
{
	EDirection BulletDirection = GetBulletSpawnDirection();

	switch (BulletDirection)
	{
	case EDirection::Left:
		return { -30.0f, 30.0f };
	case EDirection::Right:
		return { 30.0f, 30.0f };
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
