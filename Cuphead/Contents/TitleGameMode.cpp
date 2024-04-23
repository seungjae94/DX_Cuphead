#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleScreen.h"

ATitleGameMode::ATitleGameMode() 
{
}

ATitleGameMode::~ATitleGameMode() 
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");

	InputOn();
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsAnykeyDown() 
		&& false == IsDown(VK_LBUTTON) 
		&& false == IsDown(VK_RBUTTON) 
		&& false == IsDown(GEngine->GetEngineOption().FreeCameraKey))
	{
		ChangeLevelWithFadeEffect(GLevelName::OverworldLevel);
	}
}

