#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"

void APlayer::StateInit()
{
	StateManager.CreateState(GStateName::Idle);
	StateManager.CreateState(GStateName::Run);
	StateManager.CreateState(GStateName::Sit);
	StateManager.CreateState(GStateName::Dash);
	StateManager.CreateState(GStateName::Jump);

	StateManager.SetStartFunction(GStateName::Idle, std::bind(&APlayer::IdleStart, this));
	StateManager.SetUpdateFunction(GStateName::Idle, std::bind(&APlayer::Idle, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Idle, std::bind(&APlayer::IdleEnd, this));

	StateManager.SetStartFunction(GStateName::Run, std::bind(&APlayer::RunStart, this));
	StateManager.SetUpdateFunction(GStateName::Run, std::bind(&APlayer::Run, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Run, std::bind(&APlayer::RunEnd, this));

	StateManager.SetStartFunction(GStateName::Jump, std::bind(&APlayer::JumpStart, this));
	StateManager.SetUpdateFunction(GStateName::Jump, std::bind(&APlayer::Jump, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Jump, std::bind(&APlayer::JumpEnd, this));

	StateManager.SetStartFunction(GStateName::Dash, std::bind(&APlayer::DashStart, this));
	StateManager.SetUpdateFunction(GStateName::Dash, std::bind(&APlayer::Dash, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Dash, std::bind(&APlayer::DashEnd, this));

	StateManager.SetStartFunction(GStateName::Sit, std::bind(&APlayer::SitStart, this));
	StateManager.SetUpdateFunction(GStateName::Sit, std::bind(&APlayer::Sit, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Sit, std::bind(&APlayer::SitEnd, this));
}

void APlayer::ChangeState(std::string _StateName)
{
	PrevStateName = CurStateName;
	StateManager.ChangeState(_StateName);
	CurStateName = _StateName;
}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerIdle);
	Velocity = FVector::Zero;
}

void APlayer::Idle(float _DeltaTime)
{
	Fire();
	RefreshIdleAnimation();

	if (true == IsPressArrowKey())
	{
		ChangeState(GStateName::Run);
		return;
	}

	if (true == IsDown('Z'))
	{
		ChangeState(GStateName::Jump);
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		ChangeState(GStateName::Dash);
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		ChangeState(GStateName::Sit);
		return;
	}
}

void APlayer::IdleEnd()
{
}

void APlayer::RunStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerRun);
	IsFire = false;
}

void APlayer::Run(float _DeltaTime)
{
	Fire();
	RefreshRunAnimation();

	if (false == IsPressArrowKey())
	{
		ChangeState(GStateName::Idle);
		return;
	}

	Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * RunSpeed;

	if (true == IsDown('Z'))
	{
		ChangeState(GStateName::Jump);
		return;
	}

	if (true == IsDown(VK_SHIFT))
	{
		ChangeState(GStateName::Dash);
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		ChangeState(GStateName::Sit);
		return;
	}
}

void APlayer::RunEnd()
{
}

void APlayer::JumpStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerJump);
	if (true == IsDashed)
	{
		Velocity.Y = 0.0f;
		return;
	}

	Velocity += JumpImpulse;
}

void APlayer::Jump(float _DeltaTime)
{
	Fire();

	if (true == OnGroundValue)
	{
		ChangeState(GStateName::Idle);
		IsDashed = false;
		return;
	}

	EEngineDir PrevDirection = Direction;
	RefreshDirection();

	if (true == IsPressArrowKey())
	{
		Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * RunSpeed;
	}
	else
	{
		Velocity.X = 0.0f;
	}

	if (true == IsDown(VK_SHIFT) && false == IsDashed)
	{
		IsDashed = true;
		ChangeState(GStateName::Dash);
		return;
	}
}

void APlayer::JumpEnd()
{
}

void APlayer::DashStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerDash);
	Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * DashSpeed;
	Velocity.Y = 0.0f;
	ApplyGravity = false;
	DelayCallBack(DashTime, [this]() {
		ApplyGravity = true;
		Velocity -= JumpImpulse;
		UEngineDebug::OutPutDebugText(PrevStateName);
		ChangeState(PrevStateName);
		});
}

void APlayer::Dash(float _DeltaTime)
{
}

void APlayer::DashEnd()
{
}

void APlayer::SitStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerSit);
	Velocity = FVector::Zero;
}

void APlayer::Sit(float _DeltaTime)
{
	Fire();

	if (true == IsPress('Z'))
	{
		ChangeState(GStateName::Jump);
		return;
	}

	if (false == IsPress(VK_DOWN))
	{
		ChangeState(GStateName::Idle);
		return;
	}
}

void APlayer::SitEnd()
{
}

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

	FireTime = FireDelay;
}

FVector APlayer::GetBulletSpawnLocation()
{
	EDirection BulletDirection = GetBulletSpawnDirection();
	FVector BulletDirectionVector = UConverter::ConvDirectionToFVector(BulletDirection);
	return GetActorLocation() + BulletDirectionVector * FireRadius;
}

EDirection APlayer::GetBulletSpawnDirection()
{
	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::LeftUp;
		}
	}

	if (true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::RightUp;
		}
	}

	if (Direction == EEngineDir::Left)
	{
		if (true == IsPress(VK_UP))
		{
			return EDirection::Up;
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
		else
		{
			return EDirection::Right;
		}
	}

	return EDirection::Right;
}

void APlayer::RefreshIdleAnimation()
{
	std::string AnimName;

	// Idle
	if (false == IsPress('X'))
	{
		AnimName = GAnimName::PlayerIdle;
		ChangeAnimationIfChanged(AnimName);
		return;
	}

	// Shoot
	EDirection ArrowDirection = UConverter::ConvActorInputToDirection(this);

	switch (ArrowDirection)
	{
	case EDirection::Zero:
	case EDirection::Left:
	case EDirection::Right:
		AnimName = GAnimName::PlayerShootForward;
		break;
	case EDirection::Up:
	case EDirection::LeftUp:
	case EDirection::RightUp:
		AnimName = GAnimName::PlayerShootUp;
		break;
	case EDirection::Down:
	case EDirection::LeftDown:
	case EDirection::RightDown:
		AnimName = GAnimName::PlayerShootDown;
		break;
	default:
		MsgBoxAssert("Idle 상태에서 방향이 " + std::to_string(static_cast<int>(ArrowDirection)) + "일 수 없습니다.");
		break;
	}

	ChangeAnimationIfChanged(AnimName);
}

void APlayer::RefreshRunAnimation()
{
	std::string AnimName;

	// Run
	if (false == IsPress('X'))
	{
		AnimName = GAnimName::PlayerRun;
		ChangeAnimationIfChanged(AnimName);
		return;
	}

	// RunShoot
	if (true == IsPress(VK_UP))
	{
		AnimName = GAnimName::PlayerRunShootHalfUp;
	}
	else
	{
		AnimName = GAnimName::PlayerRunShootForward;
	}

	ChangeAnimationIfChanged(AnimName);
}
