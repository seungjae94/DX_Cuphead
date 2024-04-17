#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Potato.h"
#include "Onion.h"
#include "Carrot.h"

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("OnionIntro");
	StateManager.CreateState("OnionBattle");
	StateManager.CreateState("CarrotIntro");
	StateManager.CreateState("CarrotBattle");

	StateManager.SetFunction("Intro",
		std::bind(&ABossFarmGameMode::IntroStart, this),
		std::bind(&ABossFarmGameMode::Intro, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::IntroEnd, this)
	);

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

	//StateManager.ChangeState("Intro");
	StateManager.ChangeState("CarrotIntro");
}


void ABossFarmGameMode::IntroStart()
{
	// 페이드 애니메이션
	
	// Ready Wallop 애니메이션

	// 감자 등장 애니메이션
	Potato = GetWorld()->SpawnActor<APotato>("Potato").get();
	Potato->PlayGroundIntroAnimation();
	Potato->SetPotatoFrameCallback("potato_intro", 9, [this]() {
		StateManager.ChangeState("PotatoBattle");
	});

	// 플레이어 인트로 애니메이션
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
	if (true == Carrot->IsFinished())
	{
		// TODO: 전투 종료 처리
	}
}

void ABossFarmGameMode::CarrotBattleEnd()
{
}