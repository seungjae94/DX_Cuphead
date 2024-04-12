#pragma once

class ANoise;

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

	void SetNoise(ANoise* _Noise);

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	UStateManager StateManager;
	EDirection Direction = EDirection::Down;
	FVector DirectionVector = FVector::Down;
	FVector ColCenter = FVector::Down * 30.0f;
	const float ColRadius = 20.0f;
	const float MoveSpeed = 200.0f;
	std::string PrevAnimName = "";

	ANoise* Noise = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugMsgUpdate(float _DeltaTime);
private:
	void AnimationInit();
	void StateInit();
	void BringCamera();
	void BringNoise();

private:
	// 상태 함수
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void Walk(float _DeltaTime);
	void WalkEnd();

private:
	// 유틸 함수
	static std::string TransDirectionToAnimName(EDirection _Direction, bool _IsIdle);
	bool IsPressArrowKey();
	void RefreshDirection();
	void RefreshFlip();
	bool CheckCollision();
};

