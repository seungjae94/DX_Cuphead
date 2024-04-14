#pragma once

class APotato : public AActor
{
	GENERATED_BODY(AActor)
public:
	APotato();
	~APotato();

	APotato(const APotato& _Other) = delete;
	APotato(APotato&& _Other) noexcept = delete;
	APotato& operator=(const APotato& _Other) = delete;
	APotato& operator=(APotato&& _Other) noexcept = delete;

	void PlayGroundIntroAnimation();
	void PlayPotatoIntroAnimation();
	void PlayGroundIdleAnimation();
	void PlayPotatoIdleAnimation();
	void SetGroundFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);
	void SetPotatoFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);
protected:


private:
	// ÄÄÆ÷³ÍÆ®
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* GroundRenderer = nullptr;
	USpriteRenderer* PotatoRenderer = nullptr;

private:
	void BeginPlay() override;
};

