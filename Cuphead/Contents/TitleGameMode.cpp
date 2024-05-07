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

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BgmPlayer = UEngineSound::SoundPlay("title_screen_bgm.mp3");
	BgmPlayer.Loop(-1);
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

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	BgmPlayer.Off();
}

