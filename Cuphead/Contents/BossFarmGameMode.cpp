#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Player.h"
#include "Potato.h"
#include "Onion.h"
#include "Carrot.h"
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
	Player->SetColMapName("boss_farm_map_col.png");
	Player->SetActorLocation({-300.0f, -285.0f, 0.0f});

	Map = GetWorld()->SpawnActor<ABossFarmMap>("Map").get();

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

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("OnionIntro");
	StateManager.CreateState("OnionBattle");
	StateManager.CreateState("CarrotIntro");
	StateManager.CreateState("CarrotBattle");

	StateManager.SetFunction("PotatoBattle",
		std::bind(&ABossFarmGameMode::PotatoBattleStart, this),
		std::bind(&ABossFarmGameMode::PotatoBattle, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::PotatoBattleEnd, this)
	);

	StateManager.SetFunction("OnionIntro",
		std::bind(&ABossFarmGameMode::OnionIntroStart, this),
		std::bind(&ABossFarmGameMode::OnionIntro, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::OnionIntroEnd, this)
	);

	StateManager.SetFunction("OnionBattle",
		std::bind(&ABossFarmGameMode::OnionBattleStart, this),
		std::bind(&ABossFarmGameMode::OnionBattle, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::OnionBattleEnd, this)
	);

	StateManager.SetFunction("CarrotIntro",
		std::bind(&ABossFarmGameMode::CarrotIntroStart, this),
		std::bind(&ABossFarmGameMode::CarrotIntro, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::CarrotIntroEnd, this)
	);

	StateManager.SetFunction("CarrotBattle",
		std::bind(&ABossFarmGameMode::CarrotBattleStart, this),
		std::bind(&ABossFarmGameMode::CarrotBattle, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::CarrotBattleEnd, this)
	);

	StateManager.ChangeState("Intro");
	//StateManager.ChangeState("CarrotIntro");
}


void ABossFarmGameMode::IntroStart()
{
	Super::IntroStart();

	// ���� ���� �ִϸ��̼�
	Potato = GetWorld()->SpawnActor<APotato>("Potato").get();
	Potato->PlayGroundIntroAnimation();
	Potato->SetPotatoFrameCallback("potato_intro", 9, [this]() {
		StateManager.ChangeState("PotatoBattle");
		});
}

void ABossFarmGameMode::Intro(float _DeltaTime)
{
}

void ABossFarmGameMode::IntroEnd()
{
}

void ABossFarmGameMode::PotatoBattleStart()
{
	Potato->StateChangeToAttack();
}

void ABossFarmGameMode::PotatoBattle(float _DeltaTime)
{
	if (true == Potato->IsFinished())
	{
		Potato->Destroy();
		StateManager.ChangeState("OnionIntro");
	}
}

void ABossFarmGameMode::PotatoBattleEnd()
{
}

void ABossFarmGameMode::OnionIntroStart()
{
	// ���� ���� �ִϸ��̼�
	Onion = GetWorld()->SpawnActor<AOnion>("Onion").get();
	Onion->PlayGroundIntroAnimation();
	Onion->SetOnionFrameCallback("onion_cry_intro", 5, [this]() {
		StateManager.ChangeState("OnionBattle");
		});
}

void ABossFarmGameMode::OnionIntro(float _DeltaTime)
{
}

void ABossFarmGameMode::OnionIntroEnd()
{
}

void ABossFarmGameMode::OnionBattleStart()
{
	Onion->StateChangeToAttack();
}

void ABossFarmGameMode::OnionBattle(float _DeltaTime)
{
	if (true == Onion->IsFinished())
	{
		Onion->Destroy();
		StateManager.ChangeState("CarrotIntro");
	}
}

void ABossFarmGameMode::OnionBattleEnd()
{
}

void ABossFarmGameMode::CarrotIntroStart()
{
	// ��� ���� �ִϸ��̼�
	Carrot = GetWorld()->SpawnActor<ACarrot>("Carrot").get();
	Carrot->SetPlayer(Player);
	Carrot->PlayGroundIntroAnimation();
	Carrot->SetCarrotFrameCallback("carrot_intro", 24, [this]() {
		StateManager.ChangeState("CarrotBattle");
		});
}

void ABossFarmGameMode::CarrotIntro(float _DeltaTime)
{

}

void ABossFarmGameMode::CarrotIntroEnd()
{

}

void ABossFarmGameMode::CarrotBattleStart()
{
	Carrot->StateChangeToAttack();
}

void ABossFarmGameMode::CarrotBattle(float _DeltaTime)
{
	if (true == Carrot->IsFinished())
	{
		// TODO: ���� ���� ó��
	}
}

void ABossFarmGameMode::CarrotBattleEnd()
{
}
