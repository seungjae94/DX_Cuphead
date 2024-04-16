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

	std::shared_ptr<AOverworldPlayer> Player = GetWorld()->SpawnActor<AOverworldPlayer>("Player");
	Player->SetNoise(Noise);
	Map = GetWorld()->SpawnActor<AOverworldMap>("Map");

	InputOn();
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
