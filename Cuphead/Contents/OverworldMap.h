#pragma once

class AOverworldMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	AOverworldMap();
	~AOverworldMap();

	AOverworldMap(const AOverworldMap& _Other) = delete;
	AOverworldMap(AOverworldMap&& _Other) noexcept = delete;
	AOverworldMap& operator=(const AOverworldMap& _Other) = delete;
	AOverworldMap& operator=(AOverworldMap&& _Other) noexcept = delete;

	void ToggleColMap();

protected:


private:
	USpriteRenderer* Back = nullptr;
	USpriteRenderer* Front = nullptr;
	USpriteRenderer* Col = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

