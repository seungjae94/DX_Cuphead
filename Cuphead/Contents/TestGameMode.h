#pragma once
#include "CupheadGameMode.h"

class ATestGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	// constructor destructor
	ATestGameMode();
	~ATestGameMode();

	// delete Function
	ATestGameMode(const ATestGameMode& _Other) = delete;
	ATestGameMode(ATestGameMode&& _Other) noexcept = delete;
	ATestGameMode& operator=(const ATestGameMode& _Other) = delete;
	ATestGameMode& operator=(ATestGameMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

