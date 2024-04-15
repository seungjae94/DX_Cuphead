#pragma once
#include "CupheadGameMode.h"

class ABossFarmMap;
class APotato;

class ABossFarmGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
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
	ABossFarmMap* Map = nullptr;
	APotato* Potato = nullptr;
	UStateManager StateManager;
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

	void OnionBattleStart();
	void OnionBattle(float _DeltaTime);
	void OnionBattleEnd();

	void CarrotBattleStart();
	void CarrotBattle(float _DeltaTime);
	void CarrotBattleEnd();
};

