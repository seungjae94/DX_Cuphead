#pragma once
#include "CupheadGameMode.h"

class ABook;

class AIntroGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	AIntroGameMode();
	~AIntroGameMode();

	AIntroGameMode(const AIntroGameMode& _Other) = delete;
	AIntroGameMode(AIntroGameMode&& _Other) noexcept = delete;
	AIntroGameMode& operator=(const AIntroGameMode& _Other) = delete;
	AIntroGameMode& operator=(AIntroGameMode&& _Other) noexcept = delete;

protected:


private:
	ABook* Book = nullptr;
	UEngineSoundPlayer BgmPlayer;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

};

