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

	GetWorld()->SpawnActor<AOverworldPlayer>("Player");
	Map = GetWorld()->SpawnActor<AOverworldMap>("Map");

	InputOn();
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 보스 레벨로 이동
	if (true == IsDown('B'))
	{
		GEngine->ChangeLevel(GLevelName::BossDragonLevel);
	}

	// 충돌맵 온오프
	if (true == IsDown('C'))
	{
		Map->ToggleColMap();
	}
}
