#pragma once

class ATitleScreen : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ATitleScreen();
	~ATitleScreen();

	// delete Function
	ATitleScreen(const ATitleScreen& _Other) = delete;
	ATitleScreen(ATitleScreen&& _Other) noexcept = delete;
	ATitleScreen& operator=(const ATitleScreen& _Other) = delete;
	ATitleScreen& operator=(ATitleScreen&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Background = nullptr;
	USpriteRenderer* Characters = nullptr;
	USpriteRenderer* Text = nullptr;
	float4 Color;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	const float TextToggleTime = 2.0f;
	float TextToggleTimer = 0.0f;
};

