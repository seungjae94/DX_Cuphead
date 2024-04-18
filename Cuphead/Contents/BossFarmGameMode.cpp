#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Player.h"
#include "Potato.h"
#include "Onion.h"
#include "BossFarmMap.h"

ABossFarmGameMode::ABossFarmGameMode()
{
}

ABossFarmGameMode::~ABossFarmGameMode()
{
}

void ABossFarmGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->SpawnActor<APlayer>("Player").get();
	Map = GetWorld()->SpawnActor<ABossFarmMap>("Map").get();

	HpWidget = CreateWidget<UImage>(GetWorld(), "Hp");
	HpWidget->SetScale({79.0f, 33.0f});

	FVector LeftBotPivotedPos = -GEngine->EngineWindow.GetWindowScale().Half2D() + HpWidget->GetWorldScale().Half2D();
	HpWidget->SetPosition(LeftBotPivotedPos + FVector{25.0f, 20.0f});
	HpWidget->AddToViewPort();
	HpWidget->SetSprite("ui_hp3.png");

	StateInit();

	InputOn();
}

void ABossFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ABossFarmGameMode::DebugUpdate(float _DeltaTime)
{
	std::string Msg = std::format("Game State : {}\n", StateManager.GetCurStateName());
	UEngineDebugMsgWindow::PushMsg(Msg);
}
