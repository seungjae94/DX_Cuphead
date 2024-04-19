#pragma once

class UPlatform : public AActor
{
	GENERATED_BODY(AActor)
public:
	UPlatform();
	~UPlatform();

	UPlatform(const UPlatform& _Other) = delete;
	UPlatform(UPlatform&& _Other) noexcept = delete;
	UPlatform& operator=(const UPlatform& _Other) = delete;
	UPlatform& operator=(UPlatform&& _Other) noexcept = delete;

	void CreateAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Interval, bool _Loop);
	void ChangeAnimation(std::string_view _AnimName);
	void SetCollisionPosition(const FVector& _Position);
	void SetCollisionScale(const FVector& _Scale);

	void SetOnStepEnter(std::function<void(std::shared_ptr<UCollision>)> _OnStepEnter);
	void SetOnStepStay(std::function<void(std::shared_ptr<UCollision>)> _OnStepStay);
	void SetOnStepExit(std::function<void(std::shared_ptr<UCollision>)> _OnStepExit);
	void SetFrameCallback(std::string_view _AnimName, int _Index, std::function<void()> _Callback);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	std::function<void(std::shared_ptr<UCollision>)> OnStepEnter;
	std::function<void(std::shared_ptr<UCollision>)> OnStepStay;
	std::function<void(std::shared_ptr<UCollision>)> OnStepExit;
};

