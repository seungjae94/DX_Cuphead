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
	UStateManager StateManager;
	EDirection Direction = EDirection::Down;
	FVector DirectionVector = FVector::Down;
	FVector ColCenter = FVector::Down * 30.0f;
	const float ColRadius = 20.0f;
	const float MoveSpeed = 200.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 유틸 함수
	static std::string TransDirectionToAnimName(EDirection _Direction, bool _IsIdle);

	void AnimationInit();
	void StateInit();
	void BringCamera();

	// 상태 함수
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void Walk(float _DeltaTime);
	void WalkEnd();

	bool IsPressArrowKey();
	void RefreshDirection();
	void RefreshFlip();
	bool CheckCollision();
};

