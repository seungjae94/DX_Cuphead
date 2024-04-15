#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Potato.h"
#include "Onion.h"

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("OnionIntro");
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

	StateManager.ChangeState("Intro");
}


void ABossFarmGameMode::IntroStart()
{
	// ���̵� �ִϸ��̼�
	
	// Ready Wallop �ִϸ��̼�

	// ���� ���� �ִϸ��̼�
	Potato->PlayGroundIntroAnimation();
	Potato->SetPotatoFrameCallback("potato_intro", 9, [this]() {
		StateManager.ChangeState("PotatoBattle");
	});

	// �÷��̾� ��Ʈ�� �ִϸ��̼�
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
		StateManager.ChangeState("OnionIntro");
	}
}

void ABossFarmGameMode::PotatoBattleEnd()
{
}

void ABossFarmGameMode::OnionIntroStart()
{
	// ���� ���� �ִϸ��̼�
	Onion->PlayGroundIntroAnimation();
	Onion->SetOnionFrameCallback("onion_intro", 9, [this]() {
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
	//Onion->TransToAttackState();
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