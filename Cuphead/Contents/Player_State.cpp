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
	StateManager.CreateState(GStateName::EX);

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

	StateManager.SetStartFunction(GStateName::EX, std::bind(&APlayer::EXStart, this));
	StateManager.SetUpdateFunction(GStateName::EX, std::bind(&APlayer::EX, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::EX, std::bind(&APlayer::EXEnd, this));

	ChangeState(GStateName::Intro);
}

void APlayer::ChangeState(std::string _StateName)
{
	PrevStateName = CurStateName;
	CurStateName = _StateName;
	StateManager.ChangeState(_StateName);
}

void APlayer::IntroStart()
{
	DirUpdateActive = false;

	Renderer->ChangeAnimation(GAnimName::PlayerIntro);
	HitBox->SetActive(false);
}

void APlayer::Intro(float _DeltaTime)
{
	if (true == Renderer->IsCurAnimationEnd())
	{
		ChangeState("Idle");
	}
}

void APlayer::IntroEnd()
{
	DirUpdateActive = true;
	HitBox->SetActive(true);
}

void APlayer::IdleStart()
{
	Renderer->ChangeAnimation(GAnimName::PlayerIdle);
	Velocity = FVector::Zero;
}

void APlayer::Idle(float _DeltaTime)
{
	Fire();

	if (true == EXAttack())
	{
		return;
	}

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

	if (true == EXAttack())
	{
		return;
	}

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

	if (true == IsGroundHit)
	{
		IsGroundHit = false;
		return;
	}

	if (true == IsDashed)
	{
		Velocity.Y = 0.0f;
		return;
	}
}

void APlayer::Jump(float _DeltaTime)
{
	Fire();

	if (false == AirEXUsed)
	{
		if (true == EXAttack())
		{
			return;
		}
	}

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
		AirEXUsed = false;
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

	if (false == AirEXUsed)
	{
		if (true == EXAttack())
		{
			return;
		}
	}

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
		AirEXUsed = false;
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

void APlayer::ParrySuccess()
{
	Velocity.Y = JumpImpulse.Y;

	AAnimationEffect* ParryEffect = GetWorld()->SpawnActor<AAnimationEffect>("ParryEffect").get();
	ParryEffect->Init(ERenderingOrder::VFX0, FCreateAnimationParameter{ "player_parry_effect", "player_parry_effect", 1 / 12.0f }, true);
	ParryEffect->SetActorLocation(GetActorLocation());
}

int APlayer::GetDamageCoeff() const
{
	return DamageCoeff;
}

void APlayer::DashStart()
{
	DirUpdateActive = false;

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
	DirUpdateActive = true;
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
	if (true == EXAttack())
	{
		return;
	}

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
	DirUpdateActive = false;

	Renderer->ChangeAnimation(GAnimName::PlayerHit);
	HitTimer = HitTime;
	HitBox->SetActive(false);

	AAnimationEffect* HitEffect = GetWorld()->SpawnActor<AAnimationEffect>("HitEffect").get();
	HitEffect->Init(ERenderingOrder::VFX0, FCreateAnimationParameter{ "player_hit_effect", "player_hit_effect", 1 / 24.0f }, true);
	HitEffect->SetActorLocation(GetActorLocation() + FVector{ 0.0f, 50.0f, 0.0f });

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

	if (GStateName::Dash == PrevStateName || GStateName::EX == PrevStateName)
	{
		if (true == IsGroundCollisionOccur())
		{
			ChangeState(GStateName::Idle);
			return;
		}

		ChangeState(GStateName::Jump);
		return;
	}

	ChangeState(PrevStateName);
}

void APlayer::HitEnd()
{
	// 알파 처리
	int AlphaChangeCount = 60;
	for (int i = 1; i <= AlphaChangeCount; ++i)
	{
		int Remainder = i % 20;
		int Dist = Remainder - 10;

		if (Dist < 0)
		{
			Dist = -Dist;
		}

		float Alpha = Dist / 10.0f;
		float DelayTime = NoHitTime * (i / static_cast<float>(AlphaChangeCount));

		DelayCallBack(DelayTime, [this, Alpha]() {
			Renderer->SetMulColor({ 1.0f, 1.0f, 1.0f, Alpha });
		});
	}

	DelayCallBack(NoHitTime, [this]() {
		HitBox->SetActive(true);
		});

	DirUpdateActive = true;
}

void APlayer::EXStart()
{
	// 변수 설정
	DirUpdateActive = false;
	if (false == IsGroundCollisionOccur())
	{
		AirEXUsed = true;
	}

	// 애니메이션 재생
	Renderer->ChangeAnimation(GetEXAnimationName());

	// 총알 이펙트 생성 및 발사
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>("Bullet").get();
	Bullet->AnimationInit(
		FCreateAnimationParameter{ GAnimName::EXBulletMove, GImageName::EXBulletMove, 1 / 12.0f },
		FCreateAnimationParameter{ GAnimName::EXBulletDestroy, GImageName::EXBulletDestroy, 1 / 24.0f }
	);
	Bullet->SetDamage(25);
	Bullet->SetActorLocation(GetEXBulletSpawnLocation());
	Bullet->SetDirection(GetEXBulletSpawnDirection());
	Bullet->SetPlayer(this);

	// 연기 이펙트 생성
	AAnimationEffect* Dust = GetWorld()->SpawnActor<AAnimationEffect>("Dust").get();
	Dust->SetActorLocation(GetEXDustLocation());
	Dust->SetActorRotation(GetEXDustRotation());
	Dust->Init(ERenderingOrder::BulletSpawn, FCreateAnimationParameter{ "player_ex_dust", "player_ex_dust", 1 / 24.0f }, true);
}

void APlayer::EX(float _DeltaTime)
{
}

void APlayer::EXEnd()
{
	DirUpdateActive = true;
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
