#pragma once
#include "CupheadGameMode.h"

class AOverworldMap;

class AOverworldGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	AOverworldGameMode();
	~AOverworldGameMode();

	AOverworldGameMode(const AOverworldGameMode& _Other) = delete;
	AOverworldGameMode(AOverworldGameMode&& _Other) noexcept = delete;
	AOverworldGameMode& operator=(const AOverworldGameMode& _Other) = delete;
	AOverworldGameMode& operator=(AOverworldGameMode&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<AOverworldMap> Map = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

