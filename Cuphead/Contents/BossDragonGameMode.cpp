#include "PreCompile.h"
#include "BossDragonGameMode.h"
#include "BossDragonMap.h"

ABossDragonGameMode::ABossDragonGameMode()
{
}

ABossDragonGameMode::~ABossDragonGameMode()
{
}

void ABossDragonGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ABossDragonMap>("Map");
}
