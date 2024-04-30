#pragma once
#include "CupheadGameMode.h"

class APlayResultManager;

class APlayResultGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	APlayResultGameMode();
	~APlayResultGameMode();

	APlayResultGameMode(const APlayResultGameMode& _Other) = delete;
	APlayResultGameMode(APlayResultGameMode&& _Other) noexcept = delete;
	APlayResultGameMode& operator=(const APlayResultGameMode& _Other) = delete;
	APlayResultGameMode& operator=(APlayResultGameMode&& _Other) noexcept = delete;

	static void Refresh(float _PlaySeconds, int _RemainHp, int _ParryCount, int _ExUsageCount, int _Difficulty = 2);

protected:


private:
	void BeginPlay() override;

	APlayResultManager* Manager = nullptr;

	static float PlaySeconds;
	static int RemainHp;
	static int ParryCount;
	static int ExUsageCount;
	static int Difficulty;
};

