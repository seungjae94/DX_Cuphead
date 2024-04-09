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

	// ImageNameMap[AnimName] = ImageName
	std::map<std::string, std::string> ImageNameMap;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 유틸 함수
	void CreateAnimation(std::string _AnimName, std::string _ImageName, float _Inter);
	void ChangeAnimation(std::string _AnimName);
};

