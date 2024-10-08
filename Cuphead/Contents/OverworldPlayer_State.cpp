#include "PreCompile.h"
#include "OverworldPlayer.h"
#include "AnimationEffect.h"

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
	PrevAnimName = AnimName;
	RefreshFlip();
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
	RefreshFlip();

	// 애니메이션 갱신
	std::string AnimName = TransDirectionToAnimName(Direction, false);
	if (AnimName != PrevAnimName)
	{
		Renderer->ChangeAnimation(AnimName);
		PrevAnimName = AnimName;
	}

	// 먼지 애니메이션 이펙트 생성
	CreateDustAnimationEffect(_DeltaTime);

	// 이동 시뮬레이션
	FVector OriginalPos = GetActorLocation();
	AddActorLocation(DirectionVector * MoveSpeed * _DeltaTime);

	// 충돌 체크
	// - 충돌이 발생한 경우 위치를 되돌린다.
	if (true == CheckCollision())
	{
		SetActorLocation(OriginalPos);
		return;
	}
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

void AOverworldPlayer::RefreshFlip()
{
	switch (Direction)
	{
	case EDirection::Right:
	case EDirection::RightUp:
	case EDirection::RightDown:
	case EDirection::Up:
	case EDirection::Down:
		Renderer->SetDir(EEngineDir::Right);
		break;
	case EDirection::LeftUp:
	case EDirection::Left:
	case EDirection::LeftDown:
		Renderer->SetDir(EEngineDir::Left);
		break;
	}
}

bool AOverworldPlayer::CheckCollision()
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes(GImageName::OverworldIsle1Pixel);
	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector CollisionCenterPos = GetActorLocation() + ColCenter;
	FVector TestPixel = CollisionCenterPos + DirectionVector * ColRadius - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}

void AOverworldPlayer::CreateDustAnimationEffect(float _DeltaTime)
{
	DustTimer -= _DeltaTime;

	if (DustTimer >= 0.0f)
	{
		return;
	}
	DustTimer = DustTime;

	AAnimationEffect* Effect = GetWorld()->SpawnActor<AAnimationEffect>("Effect").get();

	UEngineSound::SoundPlay("overworld_foot_se_" + std::to_string(FootSEIndex) + ".mp3");
	FootSEIndex = (FootSEIndex + 1) % 5;

	if (true == IsLeftFoot)
	{
		Effect->SetActorLocation(GetActorLocation() + FVector::Left * 15.0f);
	}
	else
	{
		Effect->SetActorLocation(GetActorLocation() + FVector::Right * 15.0f);
	}
	IsLeftFoot = !IsLeftFoot;

	Effect->Init(ERenderingOrder::Back1, { GAnimName::OverworldCharDust, GImageName::OverworldCharDust, 1 / 24.0f }, true);
}
