#pragma once

class AAnimationEffect : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AAnimationEffect();
	~AAnimationEffect();

	// delete Function
	AAnimationEffect(const AAnimationEffect& _Other) = delete;
	AAnimationEffect(AAnimationEffect&& _Other) noexcept = delete;
	AAnimationEffect& operator=(const AAnimationEffect& _Other) = delete;
	AAnimationEffect& operator=(AAnimationEffect&& _Other) noexcept = delete;

	void Init(ERenderingOrder _Order, FCreateAnimationParameter _Parameter, bool _AutoDestroy = false);
	void SetAutoDestroyCallback(std::function<void()> _Callback);

protected:
	void Tick(float _DeltaTime) override;
private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	bool AutoDestroy = false;
	std::function<void()> AutoDestroyCallback = nullptr;
};

