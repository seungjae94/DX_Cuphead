#include "PreCompile.h"
#include "IntroGameMode.h"
#include "Book.h"

AIntroGameMode::AIntroGameMode()
{
}

AIntroGameMode::~AIntroGameMode()
{
}

void AIntroGameMode::BeginPlay()
{
	Super::BeginPlay();

	Book = GetWorld()->SpawnActor<ABook>("Book").get();
	Book->Init("intro_book_", 6);

	InputOn();
}

void AIntroGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == Book->IsCurAnimationEnd())
	{
		return;
	}

	if (true == IsDown('Z'))
	{
		Book->IncBookIndex();

		if (true == Book->OverMaxBookIndex())
		{
			ChangeLevelWithFadeEffect(GLevelName::OverworldLevel);
			return;
		}
		return;
	}
}

void AIntroGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BgmPlayer = UEngineSound::SoundPlay("intro_bgm.mp3");
	BgmPlayer.SetVolume(0.5f);
	BgmPlayer.Loop(-1);
}

void AIntroGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	BgmPlayer.Off();
}
