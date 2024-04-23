#pragma once
#include "BossGameMode.h"

class ABossFarmMap;
class APotato;
class AOnion;
class ACarrot;
class APlayer;

class ABossFarmGameMode : public ABossGameMode
{
	GENERATED_BODY(ABossGameMode)
public:
	// constructor destructor
	ABossFarmGameMode();
	~ABossFarmGameMode();

	// delete Function
	ABossFarmGameMode(const ABossFarmGameMode& _Other) = delete;
	ABossFarmGameMode(ABossFarmGameMode&& _Other) noexcept = delete;
	ABossFarmGameMode& operator=(const ABossFarmGameMode& _Other) = delete;
	ABossFarmGameMode& operator=(ABossFarmGameMode&& _Other) noexcept = delete;

protected:
private:
	UStateManager StateManager;
	ABossFarmMap* Map = nullptr;
	APlayer* Player = nullptr;
	APotato* Potato = nullptr;
	AOnion* Onion = nullptr;
	ACarrot* Carrot = nullptr;
private:
	// 초기화 함수
	void StateInit();
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	// 상태 함수
	void IntroStart();
	void Intro(float _DeltaTime);
	void IntroEnd();

	void PotatoBattleStart();
	void PotatoBattle(float _DeltaTime);
	void PotatoBattleEnd();

	void OnionIntroStart();
	void OnionIntro(float _DeltaTime);
	void OnionIntroEnd();

	void OnionBattleStart();
	void OnionBattle(float _DeltaTime);
	void OnionBattleEnd();

	void CarrotIntroStart();
	void CarrotIntro(float _DeltaTime);
	void CarrotIntroEnd();

	void CarrotBattleStart();
	void CarrotBattle(float _DeltaTime);
	void CarrotBattleEnd();
};

