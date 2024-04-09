#include "PreCompile.h"
#include "OverworldPlayer.h"

AOverworldPlayer::AOverworldPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

AOverworldPlayer::~AOverworldPlayer()
{
}

void AOverworldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, 0.0f, 0.0f });

	Renderer->SetSprite(GImageName::OverworldCharDownIdle);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Character);

	AnimationInit();
	StateInit();

	InputOn();
}

void AOverworldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
}
