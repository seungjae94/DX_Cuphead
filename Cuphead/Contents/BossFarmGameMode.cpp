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

	GetWorld()->SpawnActor<APlayer>("Player");
	Map = GetWorld()->SpawnActor<ABossFarmMap>("Map").get();
	Potato = GetWorld()->SpawnActor<APotato>("Potato").get();

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
