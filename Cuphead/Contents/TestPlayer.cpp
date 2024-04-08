#include "PreCompile.h"
#include "TestPlayer.h"
#include <EngineBase/EngineMath.h>

ATestPlayer::ATestPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetSprite("test_rect.png");
}

ATestPlayer::~ATestPlayer()
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Renderer->Transform.SetPosition(FVector::Zero);
	Renderer->Transform.SetScale({ 50.0f, 50.0f, 1.0f });
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

