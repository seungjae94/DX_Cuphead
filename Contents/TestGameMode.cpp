#include "PreCompile.h"
#include "TestGameMode.h"
#include "TestPlayer.h"

ATestGameMode::ATestGameMode() 
{
}

ATestGameMode::~ATestGameMode() 
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ATestPlayer>("TestPlayer");
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

