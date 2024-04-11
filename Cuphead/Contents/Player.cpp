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

	Renderer->SetSprite(GImageName::PlayerRightIdle);
	Renderer->SetAutoSize(1.0f, true);

	Renderer->CreateAnimation(GAnimName::PlayerLeftIdle, GImageName::PlayerLeftIdle, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightIdle, GImageName::PlayerRightIdle, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftShoot, GImageName::PlayerLeftShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightShoot, GImageName::PlayerRightShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRun, GImageName::PlayerLeftRun, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRun, GImageName::PlayerRightRun, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRunShoot, GImageName::PlayerLeftRunShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRunShoot, GImageName::PlayerRightRunShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftSit, GImageName::PlayerLeftSit, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightSit, GImageName::PlayerRightSit, 0.1f);

	Renderer->ChangeAnimation(GAnimName::PlayerRightIdle);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}