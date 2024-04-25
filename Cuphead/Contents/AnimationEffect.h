#pragma once

struct FCreateAnimationParameter
{
public:
	FCreateAnimationParameter()
		: AnimName(""), ImageName(""), Interval(0.0f)
	{
	}

	FCreateAnimationParameter(std::string_view _AnimName, std::string_view _ImageName, float _Interval)
		: AnimName(_AnimName), ImageName(_ImageName), Interval(_Interval)
	{
	}

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
	void SetAutoDestroyCallback(std::function<void()> _Callback);

protected:
	void Tick(float _DeltaTime) override;
private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	bool AutoDestroy = false;
	std::function<void()> AutoDestroyCallback = nullptr;
};

