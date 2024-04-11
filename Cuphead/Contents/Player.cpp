#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, -190.0f, 0.0f });

	Renderer->SetSprite(GImageName::PlayerRightIdle);
	Renderer->SetOrder(ERenderingOrder::Character);
	Renderer->SetAutoSize(1.0f, true);

	AnimationInit();
	StateInit();
	StateManager.ChangeState(GStateName::Idle);

	InputOn();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	PhysicsUpdate(_DeltaTime);
}

void APlayer::PhysicsUpdate(float _DeltaTime)
{
	// 이동 시뮬레이션
	Velocity += Gravity * _DeltaTime;

	if (true == OnGroundValue && Velocity.Y < 0.0f)
	{
		Velocity.Y = 0.0f;
	}

	FVector PrevPos = GetActorLocation();
	AddActorLocation(Velocity * _DeltaTime);

	// 바닥 충돌 체크
	if (true == CheckCollision())
	{
		OnGroundValue = true;
		SetActorLocation(PrevPos);
	}
	else
	{
		OnGroundValue = false;
	}
}

bool APlayer::IsPressArrowKey()
{
	return IsPress(VK_LEFT) || IsPress(VK_RIGHT);
}

bool APlayer::IsDirectionLeft() const
{
	return Direction == EDirection::Left;
}

void APlayer::RefreshDirection()
{
	if (true == IsPress(VK_RIGHT))
	{
		Direction = EDirection::Right;
	}
	else if (true == IsPress(VK_LEFT))
	{
		Direction = EDirection::Left;
	}
}

bool APlayer::CheckCollision()
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes("boss_farm_map_col.png");
	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector CollisionCenterPos = GetActorLocation() + ColCenter;
	FVector TestPixel = CollisionCenterPos + FVector::Down * ColRadius - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}
