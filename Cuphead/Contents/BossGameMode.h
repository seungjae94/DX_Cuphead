#pragma once
#include "CupheadGameMode.h"

class APlayer;

class ABossGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	ABossGameMode();
	~ABossGameMode();

	ABossGameMode(const ABossGameMode& _Other) = delete;
	ABossGameMode(ABossGameMode&& _Other) noexcept = delete;
	ABossGameMode& operator=(const ABossGameMode& _Other) = delete;
	ABossGameMode& operator=(ABossGameMode&& _Other) noexcept = delete;

protected:
	APlayer* Player = nullptr;
	UStateManager StateManager;
	UEngineRandom Random;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	virtual void IntroStart();
	virtual void Intro(float _DeltaTime);
	virtual void IntroEnd();

	void ShowKnockOutMessage(std::function<void()> _Callback);
private:
	UImage* BattleMessage = nullptr;

	void FadeWaitStart();
	void FadeWait(float _DeltaTime);
	void FadeWaitEnd();
private:
	const float AnnounceInterval = 2.5f;
	float AnnounceTimer = 0.0f;
	int AnnounceIndex = 0;
private:
	void PlayIntroAnnounce(float _DeltaTime);
};

