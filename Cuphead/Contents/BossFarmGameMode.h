#pragma once
#include "CupheadGameMode.h"

class ABossFarmGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

