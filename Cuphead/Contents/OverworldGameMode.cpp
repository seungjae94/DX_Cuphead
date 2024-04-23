#include "PreCompile.h"
#include "OverworldGameMode.h"
#include "OverworldMap.h"
#include "OverworldPlayer.h"
#include "BossLevelEntrance.h"

AOverworldGameMode::AOverworldGameMode()
{
}

AOverworldGameMode::~AOverworldGameMode()
{
}

void AOverworldGameMode::BeginPlay()
{
	Super::BeginPlay();

	AOverworldPlayer* Player = GetWorld()->SpawnActor<AOverworldPlayer>("Player").get();
	Map = GetWorld()->SpawnActor<AOverworldMap>("Map").get();

	ABossLevelEntrance* Farm = GetWorld()->SpawnActor<ABossLevelEntrance>("Farm").get();
	Farm->SetAnimation("overworld_farm", "overworld_farm.png", 1 / 12.0f);
	Farm->SetLevelName(GLevelName::BossFarmLevel);
	Farm->SetActorLocation({-80.0f, -380.0f, 0.0f});

	InputOn();
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
