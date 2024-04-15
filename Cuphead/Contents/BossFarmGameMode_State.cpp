#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Potato.h"

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("OnionBattle");

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

	StateManager.SetFunction("OnionBattle",
		std::bind(&ABossFarmGameMode::OnionBattleStart, this),
		std::bind(&ABossFarmGameMode::OnionBattle, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::OnionBattleEnd, this)
	);

	StateManager.ChangeState("Intro");
}


void ABossFarmGameMode::IntroStart()
{
	// 페이드 애니메이션
	
	// Ready Wallop 애니메이션

	// 감자 등장 애니메이션
	Potato->PlayGroundIntroAnimation();
	Potato->SetGroundFrameCallback("ground_intro", 27, [this]() {
		Potato->PlayGroundIdleAnimation();
	});
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
	Potato->TransToAttackState();
}

void ABossFarmGameMode::PotatoBattle(float _DeltaTime)
{
	if (GStateName::Finish == Potato->GetCurStateName())
	{
		Potato->Destroy();
		StateManager.ChangeState("OnionBattle");
	}
}

void ABossFarmGameMode::PotatoBattleEnd()
{
}

void ABossFarmGameMode::OnionBattleStart()
{
}

void ABossFarmGameMode::OnionBattle(float _DeltaTime)
{
}

void ABossFarmGameMode::OnionBattleEnd()
{
}

void ABossFarmGameMode::CarrotBattleStart()
{
}

void ABossFarmGameMode::CarrotBattle(float _DeltaTime)
{
}

void ABossFarmGameMode::CarrotBattleEnd()
{
}