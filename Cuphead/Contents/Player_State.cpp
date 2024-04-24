#include "PreCompile.h"
#include "Player.h"
#include "Bullet.h"
#include "AnimationEffect.h"

void APlayer::StateInit()
{
	StateManager.CreateState(GStateName::Intro);
	StateManager.CreateState(GStateName::Idle);
	StateManager.CreateState(GStateName::Run);
	StateManager.CreateState(GStateName::Sit);
	StateManager.CreateState(GStateName::Hit);
	StateManager.CreateState(GStateName::Dash);
	StateManager.CreateState(GStateName::Jump);
	StateManager.CreateState(GStateName::Parry);

	StateManager.SetFunction(GStateName::Intro,
		std::bind(&APlayer::IntroStart, this),
		std::bind(&APlayer::Intro, this, std::placeholders::_1),
		std::bind(&APlayer::IntroEnd, this)
	);

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

	StateManager.ChangeState(GStateName::Intro);
}

void APlayer::ChangeState(std::string _StateName)
{
	PrevStateName = CurStateName;
	CurStateName = _StateName;
	StateManager.ChangeState(_StateName);
}

void APlayer::IntroStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerIntro);
}

void APlayer::Intro(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		StateManager.ChangeState("Idle");
	}
}

void APlayer::IntroEnd()
{
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
		// 아래 점프 테스트
		if (true == IsPress(VK_DOWN) && true == TestDownJump())
		{
			AddActorLocation(FVector::Down * DownJumpCheckScale);
			ChangeState(GStateName::Jump);
			return;
		}

		AddActorLocation(FVector::Up * DownJumpCheckScale);
		Velocity += JumpImpulse;
		ChangeState(GStateName::Jump);
		return;
	}

	if (false == IsGroundCollisionOccur())
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
	RunDustTimer = RunDustInterval;
}

void APlayer::Run(float _DeltaTime)
{
	Fire();
	RefreshRunAnimation();
	SpawnRunDustEffect(_DeltaTime);

	if (false == IsPressArrowKey())
	{
		ChangeState(GStateName::Idle);
		return;
	}

	if (true == IsDown('Z'))
	{
		AddActorLocation(FVector::Up * 3.0f);
		Velocity += JumpImpulse;
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

	// 이동 및 충돌 처리
	Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * RunSpeed;
	float PrevPosX = GetActorLocation().X;
	float NextPosX = GetActorLocation().X + Velocity.X * _DeltaTime;
	float PosY = GetActorLocation().Y;
	SetActorLocation({ NextPosX, PosY, 0.0f });

	if (true == IsGroundCollisionOccur())
	{
		// 바닥을 밟는 경우
		if ((true == IsLeftCollisionOccur() && Velocity.X < 0.0f)
			|| (true == IsRightCollisionOccur() && Velocity.X > 0.0f))
		{
			SetActorLocation({ PrevPosX, PosY, 0.0f });
		}
	}
	else
	{
		// 바닥을 밟지 않게 되는 경우
		ChangeState(GStateName::Jump);
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
}

void APlayer::Jump(float _DeltaTime)
{
	Fire();

	// 대시 처리
	if (true == IsDown(VK_SHIFT) && false == IsDashed)
	{
		IsDashed = true;
		ChangeState(GStateName::Dash);
		return;
	}

	float PrevPosX = GetActorLocation().X;

	if (true == IsPressArrowKey())
	{
		Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * RunSpeed;
	}
	else
	{
		Velocity.X = 0.0f;
	}

	// 중력 적용
	Velocity += Gravity * _DeltaTime;
	AddActorLocation(Velocity * _DeltaTime);

	if ((true == IsLeftCollisionOccur() && Velocity.X < 0.0f) 
		|| (true == IsRightCollisionOccur() && Velocity.X > 0.0f))
	{
		float PosY = GetActorLocation().Y;
		SetActorLocation({ PrevPosX, PosY, 0.0f });
	}

	if (true == IsGroundCollisionOccur() && Velocity.Y <= 0.0f)
	{
		MoveUpToGround();
		ChangeState(GStateName::Idle);
		IsDashed = false;
		return;
	}

	// 패리 상태로 변경
	if (true == IsDown('Z'))
	{
		ChangeState(GStateName::Parry);
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

	if (true == IsDashed)
	{
		Velocity.Y = 0.0f;
		return;
	}
}

void APlayer::Parry(float _DeltaTime)
{
	Fire();

	// 대시 처리
	if (true == IsDown(VK_SHIFT) && false == IsDashed)
	{
		IsDashed = true;
		ChangeState(GStateName::Dash);
		return;
	}

	float PrevPosX = GetActorLocation().X;

	if (true == IsPressArrowKey())
	{
		Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * RunSpeed;
	}
	else
	{
		Velocity.X = 0.0f;
	}

	// 중력 적용
	Velocity += Gravity * _DeltaTime;
	AddActorLocation(Velocity * _DeltaTime);

	if ((true == IsLeftCollisionOccur() && Velocity.X < 0.0f)
		|| (true == IsRightCollisionOccur() && Velocity.X > 0.0f))
	{
		float PosY = GetActorLocation().Y;
		SetActorLocation({ PrevPosX, PosY, 0.0f });
	}

	if (true == IsGroundCollisionOccur())
	{
		MoveUpToGround();
		ChangeState(GStateName::Idle);
		IsDashed = false;
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

bool APlayer::IsParrying()
{
	return IsParryingValue;
}

void APlayer::DashStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerDash);
	Velocity.X = UConverter::ConvEngineDirToFVector(Direction).X * DashSpeed;
	Velocity.Y = 0.0f;
	DashTimer = DashTime;

	// 대시 먼지
	AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("AnimationEffect").get();
	Effect->SetActorLocation(GetActorLocation() + DashDustPos);
	Effect->Init(ERenderingOrder::Character, { GAnimName::PlayerDashDust, GImageName::PlayerDashDust, 1 / 24.0f }, true);
}

void APlayer::Dash(float _DeltaTime)
{
	DashTimer -= _DeltaTime;

	if (DashTimer > 0.0f)
	{
		AddActorLocation(Velocity * _DeltaTime);

		if ((true == IsLeftCollisionOccur() && Velocity.X < 0.0f)
			|| (true == IsRightCollisionOccur() && Velocity.X > 0.0f))
		{
			AddActorLocation(-Velocity * _DeltaTime);
			return;
		}

		return;
	}

	if ("Dash" == PrevStateName)
	{
		PrevStateName = "Idle";
	}

	ChangeState(PrevStateName);
}

void APlayer::DashEnd()
{
}

void APlayer::SitStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerSitting);
	HitBox->SetScale(BodyCollisionSitScale);
	HitBox->SetPosition(BodyCollisionSitPosition);

	Velocity = FVector::Zero;

	IsSitting = true;
	IsStanding = false;
}

void APlayer::Sit(float _DeltaTime)
{
	Fire();

	if (false == IsStanding && false == IsSitting)
	{
		RefreshSitAnimation();
	}

	if (true == IsDown('Z'))
	{
		// 아래 점프 테스트
		if (true == IsPress(VK_DOWN) && true == TestDownJump())
		{
			AddActorLocation(FVector::Down * DownJumpCheckScale);
			ChangeState(GStateName::Jump);
			return;
		}

		AddActorLocation(FVector::Up * DownJumpCheckScale);
		Velocity += JumpImpulse;
		ChangeState(GStateName::Jump);
		return;
	}

	if (false == IsGroundCollisionOccur())
	{
		ChangeState(GStateName::Jump);
		return;
	}

	if (false == IsPress(VK_DOWN))
	{
		IsStanding = true;
		Renderer->ChangeAnimation(GAnimName::PlayerStanding);
		return;
	}
}

void APlayer::SitEnd()
{
	HitBox->SetScale(BodyCollisionDefaultScale);
	HitBox->SetPosition(BodyCollisionDefaultPosition);
}

void APlayer::HitStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerHit);
	HitTimer = HitTime;
	HitBox->SetActive(false);

	Velocity = FVector::Zero;
	if (true == IsGroundHit)
	{
		IsGroundHit = false;
		FVector CurPos = GetActorLocation();
		SetActorLocation({ CurPos.X, DamageGroundY + 5.0f, 0.0f });
		Velocity = JumpImpulse * 1.2f;
	}
}

void APlayer::Hit(float _DeltaTime)
{
	HitTimer -= _DeltaTime;

	// 중력 적용
	Velocity += Gravity * _DeltaTime;
	AddActorLocation(Velocity * _DeltaTime);

	if (true == IsGroundCollisionOccur() && Velocity.Y <= 0.0f)
	{
		MoveUpToGround();
		IsDashed = false;
	}

	if (HitTimer > 0.0f)
	{
		return;
	}

	if (GStateName::Dash == PrevStateName)
	{
		if (true == IsGroundCollisionOccur())
		{
			StateManager.ChangeState(GStateName::Idle);
			return;
		}

		StateManager.ChangeState(GStateName::Jump);
		return;
	}

	StateManager.ChangeState(PrevStateName);
}

void APlayer::HitEnd()
{
	DelayCallBack(NoHitTime, [this]() {
		HitBox->SetActive(true);
		});
}

void APlayer::RefreshIdleAnimation()
{
	std::string AnimName;

	// Idle
	if (false == IsPress('X'))
	{
		AnimName = GAnimName::PlayerIdle;
		Renderer->ChangeAnimation(AnimName);
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

	Renderer->ChangeAnimation(AnimName);
}

void APlayer::RefreshRunAnimation()
{
	std::string AnimName;

	// Run
	if (false == IsPress('X'))
	{
		AnimName = GAnimName::PlayerRun;
		Renderer->ChangeAnimation(AnimName);
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

	Renderer->ChangeAnimation(AnimName);
}

void APlayer::RefreshSitAnimation()
{
	std::string AnimName;

	// Sit
	if (false == IsPress('X'))
	{
		AnimName = GAnimName::PlayerSit;
		Renderer->ChangeAnimation(AnimName);
		return;
	}

	// SitShoot
	AnimName = GAnimName::PlayerSitShootForward;
	Renderer->ChangeAnimation(AnimName);
}
