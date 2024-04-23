#pragma once
#include "CupheadGameMode.h"

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
	UStateManager StateManager;
	UEngineRandom Random;

	void BeginPlay() override;
	virtual void IntroStart();
	virtual void Intro(float _DeltaTime);
	virtual void IntroEnd();

	void ShowKnockOutMessage(std::function<void()> _Callback);
private:
	UImage* BattleMessage = nullptr;

	void FadeWaitStart();
	void FadeWait(float _DeltaTime);
	void FadeWaitEnd();
};

