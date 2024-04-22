#pragma once

class APlatform : public AActor
{
	GENERATED_BODY(AActor)
public:
	APlatform();
	~APlatform();

	APlatform(const APlatform& _Other) = delete;
	APlatform(APlatform&& _Other) noexcept = delete;
	APlatform& operator=(const APlatform& _Other) = delete;
	APlatform& operator=(APlatform&& _Other) noexcept = delete;

	void CreateAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Interval, bool _Loop);
	void ChangeAnimation(std::string_view _AnimName);
	void SetCollisionPosition(const FVector& _Position);
	void SetCollisionScale(const FVector& _Scale);
	void SetRenderingOrder(ERenderingOrder _Order);

	void SetOnStepEnter(std::function<void(std::shared_ptr<UCollision>)> _OnStepEnter);
	void SetOnStepStay(std::function<void(std::shared_ptr<UCollision>)> _OnStepStay);
	void SetOnStepExit(std::function<void(std::shared_ptr<UCollision>)> _OnStepExit);
	void SetFrameCallback(std::string_view _AnimName, int _Index, std::function<void()> _Callback);

	void SetVelocity(const FVector& _Velocity);
	FVector GetVelocity() const;

	void MoveStart();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
	FVector Velocity = FVector::Zero;

	bool MoveStarted = false;

	std::function<void(std::shared_ptr<UCollision>)> OnStepEnter;
	std::function<void(std::shared_ptr<UCollision>)> OnStepStay;
	std::function<void(std::shared_ptr<UCollision>)> OnStepExit;
};

