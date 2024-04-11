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

	void SetDirection(EDirection _Direction);

protected:

private:
	USpriteRenderer* Renderer = nullptr;
	UStateManager StateManager;
	EDirection Direction = EDirection::Right;
	const float Speed = 2000.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	// 초기화 함수
	void AnimationInit();
	void StateInit();
	
private:
	// 유틸 함수
	void RefreshRotation();

private:
	// 상태 함수
	void Move(float _DeltaTime);
};

