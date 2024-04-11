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

	FireTime -= _DeltaTime;
	StateManager.Update(_DeltaTime);
	PhysicsUpdate(_DeltaTime);

	// 디버그 메시지
	{
		std::string Msg = std::format("Player Position : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player Velocity : {}\n", Velocity.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void APlayer::PhysicsUpdate(float _DeltaTime)
{
	// 이동 시뮬레이션
	if (true == ApplyGravity)
	{
		Velocity += Gravity * _DeltaTime;
	}

	if (Velocity.X > RunSpeed)
	{
		Velocity.X = RunSpeed;
	}

	if (Velocity.X < -RunSpeed)
	{
		Velocity.X = -RunSpeed;
	}

	if (true == OnGroundValue && Velocity.Y < 0.0f)
	{
		Velocity.Y = 0.0f;
	}

	FVector PrevPos = GetActorLocation();
	AddActorLocation(Velocity * _DeltaTime);

	if (true == CheckCollision(FVector::Left)
		|| true == CheckCollision(FVector::Right))
	{
		SetActorLocation(PrevPos);
	}

	// 바닥 충돌 체크
	if (true == CheckCollision(FVector::Down))
	{
		OnGroundValue = true;
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

bool APlayer::CheckCollision(const FVector& _Direction)
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes("boss_farm_map_col.png");
	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector CollisionCenterPos = GetActorLocation() + ColCenter;
	FVector TestPixel = CollisionCenterPos + _Direction * ColRadius - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}
