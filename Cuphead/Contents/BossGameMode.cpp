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
	BattleMessage->CreateAnimation("ready_wallop", "ready_wallop", 1 / 24.0f, false);
	BattleMessage->CreateAnimation("knockout", "knockout", 1 / 24.0f, false);
	BattleMessage->SetScale({ 1280.0f, 720.0f });
	BattleMessage->SetPosition(FVector::Zero);
	BattleMessage->SetActive(false);
}

void ABossGameMode::ShowReadyWallopMessage()
{
	BattleMessage->ChangeAnimation("ready_wallop");
	BattleMessage->SetActive(true);
}

void ABossGameMode::ShowKnockOutMessage()
{
	BattleMessage->ChangeAnimation("knockout");
	BattleMessage->SetActive(true);
}
