#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleScreen.h"
#include "Constant.h"

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
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsAnykeyDown() && false == UEngineInput::IsDown(VK_LBUTTON))
	{
		GEngine->ChangeLevel(LevelName::OverworldLevel);
	}
}

