#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleScreen.h"
#include "Constant.h"

ATitleGameMode::ATitleGameMode() 
{
	InputOn();
}

ATitleGameMode::~ATitleGameMode() 
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsAnykeyDown() && false == IsDown(VK_LBUTTON))
	{
		GEngine->ChangeLevel(LevelName::OverworldLevel);
	}
}

