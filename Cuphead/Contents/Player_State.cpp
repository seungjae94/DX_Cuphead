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
}

void APlayer::IdleStart()
{
	Velocity.X = 0.0f;
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftIdle, GAnimName::PlayerRightIdle);
}

void APlayer::Idle(float _DeltaTime)
{
	FireTime -= _DeltaTime;

	if (true == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Run);
		return;
	}

	if (true == IsPress('X'))
	{
		if (FireTime > 0.0f)
		{
			return;
		}

		std::shared_ptr<ABullet> Bullet = GetWorld()->SpawnActor<ABullet>("Bullet");
		Bullet->SetDirection(Direction);

		FireTime = FireDelay;
	}

	if (true == IsDown('Z'))
	{
		StateManager.ChangeState(GStateName::Jump);
		return;
	}
}

void APlayer::IdleEnd()
{
}

void APlayer::RunStart()
{
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftRun, GAnimName::PlayerRightRun);
}

void APlayer::Run(float _DeltaTime)
{
	FireTime -= _DeltaTime;

	if (false == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}

	EDirection PrevDirection = Direction;

	RefreshDirection();

	if (PrevDirection != Direction)
	{
		ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftRun, GAnimName::PlayerRightRun);
	}

	Velocity.X = UConverter::ConvDirectionToFVector(Direction).X * RunSpeed;

	if (true == IsDown('Z'))
	{
		StateManager.ChangeState(GStateName::Jump);
		return;
	}
}

void APlayer::RunEnd()
{
}

void APlayer::JumpStart()
{
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftJump, GAnimName::PlayerRightJump);
	Velocity += JumpImpulse;
}

void APlayer::Jump(float _DeltaTime)
{
	if (true == OnGroundValue)
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}

	EDirection PrevDirection = Direction;
	RefreshDirection();

	if (true == IsPressArrowKey())
	{
		Velocity.X = UConverter::ConvDirectionToFVector(Direction).X * RunSpeed;
	}
	else
	{
		Velocity.X = 0.0f;
	}

	// ÃÑ¾Ë ·ÎÁ÷
}

void APlayer::JumpEnd()
{
}

void APlayer::DashStart()
{
}

void APlayer::Dash(float _DeltaTime)
{
}

void APlayer::DashEnd()
{
}
