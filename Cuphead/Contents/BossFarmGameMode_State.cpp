#include "PreCompile.h"
#include "BossFarmGameMode.h"
#include "Potato.h"

void ABossFarmGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("Potato");
	StateManager.CreateState("PotatoDestroy");

	StateManager.SetFunction("Intro",
		std::bind(&ABossFarmGameMode::IntroStart, this),
		std::bind(&ABossFarmGameMode::Intro, this, std::placeholders::_1),
		std::bind(&ABossFarmGameMode::IntroEnd, this)
	);

	StateManager.ChangeState("Intro");
}


void ABossFarmGameMode::IntroStart()
{
	// ���̵� �ִϸ��̼�
	// ���� ���� �ִϸ��̼�
	// �÷��̾� ��Ʈ�� �ִϸ��̼�
	Potato->PlayGroundIntroAnimation();

	DelayCallBack(1.15f, [this]() {
		Potato->PlayPotatoIntroAnimation();
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
}

void ABossFarmGameMode::PotatoBattle(float _DeltaTime)
{
}

void ABossFarmGameMode::PotatoBattleEnd()
{
}
