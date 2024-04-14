#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Potato.h"

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("PotatoBattle");
	StateManager.CreateState("PotatoDestroy");

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

	StateManager.ChangeState("Intro");
}


void ABossFarmGameMode::IntroStart()
{
	// ���̵� �ִϸ��̼�
	
	// Ready Wallop �ִϸ��̼�

	// ���� ���� �ִϸ��̼�
	Potato->PlayGroundIntroAnimation();
	Potato->SetGroundFrameCallback("ground_intro", 27, [this]() {
		Potato->PlayGroundIdleAnimation();
	});
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
	Potato->PlayPotatoIdleAnimation();
}

void ABossFarmGameMode::PotatoBattle(float _DeltaTime)
{
}

void ABossFarmGameMode::PotatoBattleEnd()
{
}
