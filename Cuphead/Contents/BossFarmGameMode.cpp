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
	Map = GetWorld()->SpawnActor<ABossFarmMap>("Map");

	InputOn();
}

void ABossFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_F2))
	{
		Map->ToggleColMap();
	}
}
