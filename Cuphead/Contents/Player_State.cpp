#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"

void APlayer::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Run");
	StateManager.CreateState("Sit");
	StateManager.CreateState("Dash");

	StateManager.SetStartFunction(GStateName::Idle, std::bind(&APlayer::IdleStart, this));
	StateManager.SetUpdateFunction(GStateName::Idle, std::bind(&APlayer::Idle, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Idle, std::bind(&APlayer::IdleEnd, this));

	StateManager.SetStartFunction(GStateName::Run, std::bind(&APlayer::RunStart, this));
	StateManager.SetUpdateFunction(GStateName::Run, std::bind(&APlayer::Run, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Run, std::bind(&APlayer::RunEnd, this));
}

void APlayer::IdleStart()
{
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

	AddActorLocation(UConverter::ConvDirectionToFVector(Direction) * RunSpeed * _DeltaTime);
}

void APlayer::RunEnd()
{
}
