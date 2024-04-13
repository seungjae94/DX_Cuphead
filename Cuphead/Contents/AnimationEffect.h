#pragma once

struct FCreateAnimationParameter
{
public:
	std::string AnimName;
	std::string ImageName;
	float Interval;
};

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

protected:
	void Tick(float _DeltaTime) override;
private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	bool AutoDestroy = false;
};

