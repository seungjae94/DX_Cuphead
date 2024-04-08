#pragma once

class AOverworldPlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	AOverworldPlayer();
	~AOverworldPlayer();

	AOverworldPlayer(const AOverworldPlayer& _Other) = delete;
	AOverworldPlayer(AOverworldPlayer&& _Other) noexcept = delete;
	AOverworldPlayer& operator=(const AOverworldPlayer& _Other) = delete;
	AOverworldPlayer& operator=(AOverworldPlayer&& _Other) noexcept = delete;

protected:


private:
	USpriteRenderer* Renderer = nullptr;

	// ImageScaleMap[AnimName][Scale]
	std::map<std::string, FVector> ImageScaleMap;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 유틸 함수
	void InitImageScaleMap();
	void ChangeAnimation(std::string _AnimName);
};

