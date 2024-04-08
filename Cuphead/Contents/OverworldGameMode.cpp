#include "PreCompile.h"
#include "OverworldGameMode.h"
#include "OverworldMap.h"
#include "OverworldPlayer.h"

AOverworldGameMode::AOverworldGameMode()
{
}

AOverworldGameMode::~AOverworldGameMode()
{
}

void AOverworldGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	GetWorld()->SpawnActor<AOverworldMap>("Map");
	GetWorld()->SpawnActor<AOverworldPlayer>("Player");
}
