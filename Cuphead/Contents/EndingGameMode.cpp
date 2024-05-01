#include "PreCompile.h"
#include "EndingGameMode.h"
#include "Book.h"

AEndingGameMode::AEndingGameMode()
{
}

AEndingGameMode::~AEndingGameMode()
{
}

void AEndingGameMode::BeginPlay()
{
	Super::BeginPlay();

	Book = GetWorld()->SpawnActor<ABook>("Book").get();
	Book->Init("ending_book_", 6);

	InputOn();
}

void AEndingGameMode::Tick(float _DeltaTime)
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
			// TODO: 게임 종료
			return;
		}
		return;
	}

	if (nullptr == ThankYouForPlayingText && true == Book->IsMaxBookIndex())
	{
		ThankYouForPlayingText = CreateWidget<UTextWidget>(GetWorld(), "LastText");
		ThankYouForPlayingText->SetFont("굴림");
		ThankYouForPlayingText->SetScale(80.0f);
		ThankYouForPlayingText->SetColor(Color8Bit::Yellow);
		ThankYouForPlayingText->SetPosition({ 0.0f, 100.0f });
		ThankYouForPlayingText->SetText("플레이 해주셔서 감사합니다!");
		ThankYouForPlayingText->AddToViewPort(0);
	}
}

void AEndingGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BgmPlayer = UEngineSound::SoundPlay("ending_bgm.mp3");
	BgmPlayer.Loop(-1);
	BgmPlayer.SetVolume(0.5f);
}

void AEndingGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
	BgmPlayer.Off();
}
