#include "PreCompile.h"
#include "BossGameMode.h"

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


//void ABossGameMode::ShowKnockOutMessage()
//{
//	BattleMessage->ChangeAnimation("knockout");
//	BattleMessage->SetActive(true);
//}

void ABossGameMode::IntroStart()
{
	DelayCallBack(0.5f, [this]() {
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
