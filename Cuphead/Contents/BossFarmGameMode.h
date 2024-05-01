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
	UEngineSoundPlayer BgmPlayer;
	ABossFarmMap* Map = nullptr;
	APotato* Potato = nullptr;
	AOnion* Onion = nullptr;
	ACarrot* Carrot = nullptr;
private:
	const float AnnounceInterval = 2.5f;
	float AnnounceTimer = 0.0f;
	int AnnounceIndex = 0;
private:
	// 초기화 함수
	void StateInit();
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	// 상태 함수
	void IntroStart() override;
	void Intro(float _DeltaTime) override;
	void IntroEnd() override;

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

	void FinishStart();
	void Finish(float _DeltaTime);
	void FinishEnd();
};

