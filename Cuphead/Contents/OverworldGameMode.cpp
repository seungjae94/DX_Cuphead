#include "PreCompile.h"
#include "OverworldGameMode.h"
#include "OverworldMap.h"
#include "OverworldPlayer.h"
#include "Constant.h"

AOverworldGameMode::AOverworldGameMode()
{
	InputOn();
}

AOverworldGameMode::~AOverworldGameMode()
{
}

void AOverworldGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AOverworldPlayer>("Player");
	GetWorld()->SpawnActor<AOverworldMap>("Map");
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// ���� ������ �̵�
	if (true == IsDown('B'))
	{
		GEngine->ChangeLevel(LevelName::BossDragonLevel);
	}
}
