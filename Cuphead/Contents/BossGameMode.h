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
	void BeginPlay() override;

	void ShowReadyWallopMessage();
	void ShowKnockOutMessage();

private:
	UImage* BattleMessage = nullptr;
};

