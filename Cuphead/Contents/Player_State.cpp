#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "AnimationEffect.h"

void APlayer::StateInit()
{
	StateManager.CreateState(GStateName::Idle);
	StateManager.CreateState(GStateName::Run);
	StateManager.CreateState(GStateName::Sit);
	StateManager.CreateState(GStateName::Hit);
	StateManager.CreateState(GStateName::Dash);
	StateManager.CreateState(GStateName::Jump);
	StateManager.CreateState(GStateName::Parry);

	StateManager.SetStartFunction(GStateName::Idle, std::bind(&APlayer::IdleStart, this));
	StateManager.SetUpdateFunction(GStateName::Idle, std::bind(&APlayer::Idle, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Idle, std::bind(&APlayer::IdleEnd, this));

	StateManager.SetStartFunction(GStateName::Run, std::bind(&APlayer::RunStart, this));
	StateManager.SetUpdateFunction(GStateName::Run, std::bind(&APlayer::Run, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Run, std::bind(&APlayer::RunEnd, this));

	StateManager.SetStartFunction(GStateName::Jump, std::bind(&APlayer::JumpStart, this));
	StateManager.SetUpdateFunction(GStateName::Jump, std::bind(&APlayer::Jump, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Jump, std::bind(&APlayer::JumpEnd, this));

	StateManager.SetStartFunction(GStateName::Parry, std::bind(&APlayer::ParryStart, this));
	StateManager.SetUpdateFunction(GStateName::Parry, std::bind(&APlayer::Parry, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Parry, std::bind(&APlayer::ParryEnd, this));

	StateManager.SetStartFunction(GStateName::Dash, std::bind(&APlayer::DashStart, this));
	StateManager.SetUpdateFunction(GStateName::Dash, std::bind(&APlayer::Dash, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Dash, std::bind(&APlayer::DashEnd, this));

	StateManager.SetStartFunction(GStateName::Sit, std::bind(&APlayer::SitStart, this));
	StateManager.SetUpdateFunction(GStateName::Sit, std::bind(&APlayer::Sit, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Sit, std::bind(&APlayer::SitEnd, this));

	StateManager.SetStartFunction(GStateName::Hit, std::bind(&APlayer::HitStart, this));
	StateManager.SetUpdateFunction(GStateName::Hit, std::bind(&APlayer::Hit, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Hit, std::bind(&APlayer::HitEnd, this));
}

void APlayer::ChangeState(std::string _StateName)
{
	PrevStateName = CurStateName;
	CurStateName = _StateName;
	StateManager.ChangeState(_StateName);
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

bool APlayer::IsParrying()
{
	return false;
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
	if (GStateName::Idle == CurStateName)
	{
		AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("AnimationEffect").get();
		Effect->SetActorLocation(GetActorLocation());
		Effect->Init(ERenderingOrder::Character, { GAnimName::PlayerLandingDust, GImageName::PlayerLandingDust, 0.1f }, true);
	}
}

void APlayer::ParryStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerParry);
	IsParryingValue = true;
}

void APlayer::Parry(float _DeltaTime)
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

void APlayer::ParryEnd()
{
	IsParryingValue = false;

	if (GStateName::Idle == CurStateName)
	{
		AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("AnimationEffect").get();
		Effect->SetActorLocation(GetActorLocation());
		Effect->Init(ERenderingOrder::Character, { GAnimName::PlayerLandingDust, GImageName::PlayerLandingDust, 0.1f }, true);
	}
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

	// 대시 먼지
	AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("AnimationEffect").get();
	Effect->SetActorLocation(GetActorLocation() + DashDustPos);
	Effect->Init(ERenderingOrder::Character, { GAnimName::PlayerDashDust, GImageName::PlayerDashDust, 1 / 24.0f }, true);
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

	Collision->SetScale(CollisionSitScale);
	Collision->SetPosition(CollisionSitPosition);
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
	Collision->SetScale(CollisionDefaultScale);
	Collision->SetPosition(CollisionDefaultPosition);
}

void APlayer::HitStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerHit);
	Velocity = FVector::Zero;
	DelayCallBack(0.5f, [this]() {
		if (GStateName::Dash == PrevStateName)
		{
			if (true == OnGroundValue)
			{
				StateManager.ChangeState(GStateName::Idle);
				return;
			}

			StateManager.ChangeState(GStateName::Jump);
			return;
		}

		StateManager.ChangeState(PrevStateName);
	});
	Collision->SetActive(false);
}

void APlayer::Hit(float _DeltaTime)
{
}

void APlayer::HitEnd()
{
	DelayCallBack(NoHitTime, [this]() {
		Collision->SetActive(true);
	});
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
