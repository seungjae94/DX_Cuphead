#pragma once
#include "CupheadGameMode.h"

class ABossDragonGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	ABossDragonGameMode();
	~ABossDragonGameMode();

	ABossDragonGameMode(const ABossDragonGameMode& _Other) = delete;
	ABossDragonGameMode(ABossDragonGameMode&& _Other) noexcept = delete;
	ABossDragonGameMode& operator=(const ABossDragonGameMode& _Other) = delete;
	ABossDragonGameMode& operator=(ABossDragonGameMode&& _Other) noexcept = delete;

protected:


private:
	void BeginPlay() override;
};

