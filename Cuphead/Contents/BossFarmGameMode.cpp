#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Player.h"
#include "BossFarmMap.h"

ABossFarmGameMode::ABossFarmGameMode()
{
}

ABossFarmGameMode::~ABossFarmGameMode()
{
}

void ABossFarmGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<APlayer>("Player");
	GetWorld()->SpawnActor<ABossFarmMap>("Map");
}

void ABossFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
