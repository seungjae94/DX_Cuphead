#include "PreCompile.h"
#include "OverworldPlayer.h"

void AOverworldPlayer::StateInit()
{
	StateManager.CreateState(GStateName::Idle);
	StateManager.CreateState(GStateName::Walk);

	StateManager.SetStartFunction(GStateName::Idle, std::bind(&AOverworldPlayer::IdleStart, this));
	StateManager.SetUpdateFunction(GStateName::Idle, std::bind(&AOverworldPlayer::Idle, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Idle, std::bind(&AOverworldPlayer::IdleEnd, this));

	StateManager.SetStartFunction(GStateName::Walk, std::bind(&AOverworldPlayer::WalkStart, this));
	StateManager.SetUpdateFunction(GStateName::Walk, std::bind(&AOverworldPlayer::Walk, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Walk, std::bind(&AOverworldPlayer::WalkEnd, this));

	StateManager.ChangeState(GStateName::Idle);
}

void AOverworldPlayer::IdleStart()
{
	std::string AnimName = TransDirectionToAnimName(Direction, true);
	Renderer->ChangeAnimation(AnimName);
}

void AOverworldPlayer::Idle(float _DeltaTime)
{
	if (true == IsDown(VK_LEFT)
		|| true == IsDown(VK_RIGHT)
		|| true == IsDown(VK_UP)
		|| true == IsDown(VK_DOWN))
	{
		StateManager.ChangeState(GStateName::Walk);
	}
}

void AOverworldPlayer::IdleEnd()
{
}

void AOverworldPlayer::WalkStart()
{

}

void AOverworldPlayer::Walk(float _DeltaTime)
{
	if (false == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}

	// 방향 갱신
	RefreshDirection();
	DirectionVector = UConverter::ConvDirectionToFVector(Direction);

	// 애니메이션 갱신
	std::string AnimName = TransDirectionToAnimName(Direction, false);
	Renderer->ChangeAnimation(AnimName);

	// 이동 처리
	AddActorLocation(DirectionVector * MoveSpeed * _DeltaTime);
}

void AOverworldPlayer::WalkEnd()
{
}

bool AOverworldPlayer::IsPressArrowKey()
{
	return IsPress(VK_LEFT) || IsPress(VK_RIGHT) || IsPress(VK_UP) || IsPress(VK_DOWN);
}

void AOverworldPlayer::RefreshDirection()
{
	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			Direction = EDirection::LeftUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			Direction = EDirection::LeftDown;
		}
		else
		{
			Direction = EDirection::Left;
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_UP))
		{
			Direction = EDirection::RightUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			Direction = EDirection::RightDown;
		}
		else
		{
			Direction = EDirection::Right;
		}
	}
	else if (true == IsPress(VK_UP))
	{
		Direction = EDirection::Up;
	}
	else if (true == IsPress(VK_DOWN))
	{
		Direction = EDirection::Down;
	}
}