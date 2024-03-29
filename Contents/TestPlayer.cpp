#include "PreCompile.h"
#include "TestPlayer.h"
#include <EngineCore/Renderer.h>

ATestPlayer::ATestPlayer() 
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
}

ATestPlayer::~ATestPlayer() 
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

