#include "PreCompile.h"
#include "PlayResultGameMode.h"
#include "PlayResultManager.h"

float APlayResultGameMode::PlaySeconds;
int APlayResultGameMode::RemainHp;
int APlayResultGameMode::ParryCount;
int APlayResultGameMode::ExUsageCount;
int APlayResultGameMode::Difficulty;

APlayResultGameMode::APlayResultGameMode()
{
}

APlayResultGameMode::~APlayResultGameMode()
{
}

void APlayResultGameMode::Refresh(
	float _PlaySeconds, int _RemainHp, int _ParryCount, int _ExUsageCount, int _Difficulty /*= 2*/)
{
	PlaySeconds = _PlaySeconds;
	RemainHp = _RemainHp;
	ParryCount = _ParryCount;
	ExUsageCount = _ExUsageCount;
	Difficulty = _Difficulty;
}

void APlayResultGameMode::BeginPlay()
{
	Super::BeginPlay();

	Manager = GetWorld()->SpawnActor<APlayResultManager>("Manager").get();
}
