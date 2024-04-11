#include "PreCompile.h"
#include "Player.h"

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
	if (Direction == EDirection::Left)
	{
		Renderer->ChangeAnimation(GAnimName::PlayerLeftIdle);
	}
	else
	{
		Renderer->ChangeAnimation(GAnimName::PlayerRightIdle);
	}
}

void APlayer::Idle(float _DeltaTime)
{
	if (true == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Run);
		return;
	}

}

void APlayer::IdleEnd()
{
}

void APlayer::RunStart()
{
	if (Direction == EDirection::Left)
	{
		Renderer->ChangeAnimation(GAnimName::PlayerLeftRun);
	}
	else
	{
		Renderer->ChangeAnimation(GAnimName::PlayerRightRun);
	}
}

void APlayer::Run(float _DeltaTime)
{
	if (false == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}

	bool DirectionChanged = false;
	EDirection PrevDirection = Direction;

	if (true == IsPress(VK_LEFT))
	{
		Direction = EDirection::Left;
	}
	else
	{
		Direction = EDirection::Right;
	}


	if (PrevDirection != Direction)
	{
		if (Direction == EDirection::Left)
		{
			Renderer->ChangeAnimation(GAnimName::PlayerLeftRun);
		}
		else
		{
			Renderer->ChangeAnimation(GAnimName::PlayerRightRun);
		}
	}

	AddActorLocation(UConverter::ConvDirectionToFVector(Direction) * RunSpeed * _DeltaTime);

}

void APlayer::RunEnd()
{
}
