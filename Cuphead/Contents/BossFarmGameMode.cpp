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
	Player->SetActorLocation({ -300.0f, -285.0f, 0.0f });

	Map = GetWorld()->SpawnActor<ABossFarmMap>("Map").get();

	StateInit();

	InputOn();
}

void ABossFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PlayIntroAnnounce(_DeltaTime);
	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ABossFarmGameMode::DebugUpdate(float _DeltaTime)
{
	std::string Msg = std::format("Game State : {}\n", StateManager.GetCurStateName());
	UEngineDebugMsgWindow::PushMsg(Msg);
}

void ABossFarmGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BgmPlayer = UEngineSound::SoundPlay("boss_farm_bgm.mp3");
	BgmPlayer.SetVolume(0.5f);
	BgmPlayer.Loop(-1);
}

void ABossFarmGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ABossFarmGameMode::PlayIntroAnnounce(float _DeltaTime)
{
	if (AnnounceIndex == 2)
	{
		return;
	}

	AnnounceTimer -= _DeltaTime;

	if (AnnounceTimer < 0.0f)
	{
		UEngineSound::SoundPlay("announce_farm_intro_" + std::to_string(AnnounceIndex) + ".mp3");
		++AnnounceIndex;
		AnnounceTimer = AnnounceInterval;
		return;
	}
}

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("OnionIntro");
	StateManager.CreateState("OnionBattle");
	StateManager.CreateState("CarrotIntro");
	StateManager.CreateState("CarrotBattle");
	StateManager.CreateState("Finish");

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

	StateManager.SetFunction("Finish",
		std::bind(&ABossFarmGameMode::FinishStart, this),
		std::bind(&ABossFarmGameMode::Finish, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::FinishEnd, this)
	);

	StateManager.CreateState("End");
	StateManager.SetFunction("End", []() {}, [](float _DeltaTime) {}, []() {});

	StateManager.ChangeState("Intro");
	//StateManager.ChangeState("CarrotIntro");
}


void ABossFarmGameMode::IntroStart()
{
	Super::IntroStart();

	// 감자 등장 애니메이션
	Potato = GetWorld()->SpawnActor<APotato>("Potato").get();
	Potato->PlayGroundIntroAnimation();
	Potato->SetPotatoFrameCallback("potato_intro", 9, [this]() {
		DelayCallBack(1.5f, [this]() {
			StateManager.ChangeState("PotatoBattle");
			});
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
	// 양파 등장 애니메이션
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
	// 당근 등장 애니메이션
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
	if (true == Carrot->IsFainted())
	{
		StateManager.ChangeState("Finish");
		ShowKnockOutMessage([this]() {
			Carrot->ResumeFaint();
			});
		return;
	}
}

void ABossFarmGameMode::CarrotBattleEnd()
{
}

void ABossFarmGameMode::FinishStart()
{

}

void ABossFarmGameMode::Finish(float _DeltaTime)
{
	if (true == Carrot->IsFinished())
	{
		ChangeLevelWithFadeEffect(GLevelName::PlayResultLevel);
		StateManager.ChangeState("End");
		BgmPlayer.Off();
	}
}

void ABossFarmGameMode::FinishEnd()
{
}