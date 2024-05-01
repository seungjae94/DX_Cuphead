#pragma once
#include "CupheadGameMode.h"

class ATitleGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	// constructor destructor
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

protected:

private:
	UEngineSoundPlayer BgmPlayer;

	void BeginPlay() override;
	void LevelStart(ULevel* _PrevLevel) override;
	void Tick(float _DeltaTime) override;
	void LevelEnd(ULevel* _NextLevel) override;
};

