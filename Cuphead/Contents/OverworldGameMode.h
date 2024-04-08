#pragma once

class AOverworldGameMode : public AGameMode
{
	GENERATED_BODY(AActor)
public:
	AOverworldGameMode();
	~AOverworldGameMode();

	AOverworldGameMode(const AOverworldGameMode& _Other) = delete;
	AOverworldGameMode(AOverworldGameMode&& _Other) noexcept = delete;
	AOverworldGameMode& operator=(const AOverworldGameMode& _Other) = delete;
	AOverworldGameMode& operator=(AOverworldGameMode&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

