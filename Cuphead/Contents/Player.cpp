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

	SetActorLocation({0.0f, -190.0f, 0.0f});

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
