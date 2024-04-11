#pragma once

class ABullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABullet();
	~ABullet();

	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	EDirection Direction = EDirection::Right;
	const float Speed = 500.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	
	
};

