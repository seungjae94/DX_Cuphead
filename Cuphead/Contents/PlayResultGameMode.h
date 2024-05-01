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

	void Refresh(float _PlaySeconds, int _RemainHp, int _ParryCount, int _ExUsageCount, int _Difficulty = 2);

	std::string GetPrevLevelName() const;

protected:


private:
	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;
	void Tick(float _DeltaTime) override;

	APlayResultManager* Manager = nullptr;
	std::string PrevLevelName;

	const float WaitTime = 1.0f;
	float WaitTimer = 0.0f;
};

