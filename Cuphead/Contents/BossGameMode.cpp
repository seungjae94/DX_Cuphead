#include "PreCompile.h"
#include "BossGameMode.h"
#include "PlayResultGameMode.h"
#include "Player.h"

ABossGameMode::ABossGameMode()
{
}

ABossGameMode::~ABossGameMode()
{
}

void ABossGameMode::BeginPlay()
{
	Super::BeginPlay();

	BattleMessage = CreateWidget<UImage>(GetWorld(), "BattleMessage");
	BattleMessage->AddToViewPort(ERenderingOrder::Fade);
	BattleMessage->CreateAnimation("ready_wallop", "ready_wallop", 1 / 18.0f, false);
	BattleMessage->CreateAnimation("knockout", "knockout", 1 / 18.0f, false);
	BattleMessage->SetScale({ 1280.0f, 720.0f });
	BattleMessage->SetPosition(FVector::Zero);
	BattleMessage->SetActive(false);

	StateManager.CreateState("FadeWait");
	StateManager.CreateState("Intro");

	StateManager.SetFunction("FadeWait",
		std::bind(&ABossGameMode::FadeWaitStart, this),
		std::bind(&ABossGameMode::FadeWait, this, std::placeholders::_1),
		std::bind(&ABossGameMode::FadeWaitEnd, this)
	);

	StateManager.SetFunction("Intro",
		std::bind(&ABossGameMode::IntroStart, this),
		std::bind(&ABossGameMode::Intro, this, std::placeholders::_1),
		std::bind(&ABossGameMode::IntroEnd, this)
	);
}

void ABossGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PlayIntroAnnounce(_DeltaTime);
}

void ABossGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	AnnounceTimer = 0.0f;
}

void ABossGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	APlayResultGameMode* PRGameMode = dynamic_cast<APlayResultGameMode*>(_NextLevel->GetGameMode().get());

	if (nullptr == PRGameMode)
	{
		return;
	}

	PRGameMode->Refresh(Player->GetPlaySeconds(), Player->GetRemainHp(), Player->GetParryCount(), Player->GetExUsageCount());
}


void ABossGameMode::ShowKnockOutMessage(std::function<void()> _Callback)
{
	BattleMessage->SetFrameCallback("knockout", 27, _Callback);
	BattleMessage->ChangeAnimation("knockout");
	BattleMessage->SetActive(true);
}

void ABossGameMode::IntroStart()
{
	DelayCallBack(1.0f, [this]() {
		BattleMessage->ChangeAnimation("ready_wallop");
		BattleMessage->SetActive(true);
		});
}

void ABossGameMode::Intro(float _DeltaTime)
{

}

void ABossGameMode::IntroEnd()
{

}

void ABossGameMode::FadeWaitStart()
{

}

void ABossGameMode::FadeWait(float _DeltaTime)
{
	if (false == IsFadeIn())
	{
		StateManager.ChangeState("Intro");
	}
}

void ABossGameMode::FadeWaitEnd()
{
}


void ABossGameMode::PlayIntroAnnounce(float _DeltaTime)
{
	if (AnnounceIndex == 2)
	{
		return;
	}

	AnnounceTimer -= _DeltaTime;

	if (AnnounceTimer < 0.0f)
	{
		UEngineSound::SoundPlay("announce_intro_" + std::to_string(AnnounceIndex) + ".mp3");
		++AnnounceIndex;
		AnnounceTimer = AnnounceInterval;
		return;
	}
}
