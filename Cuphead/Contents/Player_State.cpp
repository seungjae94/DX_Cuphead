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

void APlayer::IdleStart()
{
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftIdle, GAnimName::PlayerRightIdle);
	Velocity = FVector::Zero;
}

void APlayer::Idle(float _DeltaTime)
{
	FireTime -= _DeltaTime;
	PrevStateName = GStateName::Idle;

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

	if (true == IsDown(VK_SHIFT))
	{
		StateManager.ChangeState(GStateName::Dash);
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		StateManager.ChangeState(GStateName::Sit);
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
	PrevStateName = GStateName::Run;

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

	if (true == IsDown(VK_SHIFT))
	{
		StateManager.ChangeState(GStateName::Dash);
		return;
	}

	if (true == IsPress(VK_DOWN))
	{
		StateManager.ChangeState(GStateName::Sit);
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
	PrevStateName = GStateName::Jump;

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

	if (true == IsDown(VK_SHIFT))
	{
		StateManager.ChangeState(GStateName::Dash);
		return;
	}
}

void APlayer::JumpEnd()
{
}

void APlayer::DashStart()
{
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftDash, GAnimName::PlayerRightDash);
	Velocity.X = UConverter::ConvDirectionToFVector(Direction).X* RunSpeed;
	Velocity.Y = 0.0f;
	ApplyGravity = false;
	DelayCallBack(0.5f, [this]() {
		ApplyGravity = true;
		Velocity -= JumpImpulse;
		StateManager.ChangeState(PrevStateName);
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
	ChangeAnimationIf(IsDirectionLeft(), GAnimName::PlayerLeftSit, GAnimName::PlayerRightSit);
	Velocity = FVector::Zero;
}

void APlayer::Sit(float _DeltaTime)
{
	if (true == IsPress('Z'))
	{
		StateManager.ChangeState(GStateName::Jump);
		return;
	}

	if (false == IsPress(VK_DOWN))
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}
}

void APlayer::SitEnd()
{
}