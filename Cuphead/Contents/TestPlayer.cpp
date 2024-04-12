#include "PreCompile.h"
#include "TestPlayer.h"
#include <EngineBase/EngineMath.h>

ATestPlayer::ATestPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetParent(Root);
}

ATestPlayer::~ATestPlayer()
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Renderer->SetSprite("test_rect.png");
	Renderer->SetPosition(FVector::Zero);
	Renderer->SetScale({ 50.0f, 50.0f, 1.0f });
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

