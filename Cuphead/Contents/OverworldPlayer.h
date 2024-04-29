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

	void SetZButtonActive(bool _Value);
	void SetInputActive(bool _Value);

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	USpriteRenderer* ZButtonRenderer = nullptr;

private:
	UStateManager StateManager;
	EDirection Direction = EDirection::Down;
	FVector DirectionVector = FVector::Down;
	FVector ColCenter = FVector::Down * 30.0f;
	const float ColRadius = 20.0f;
	const float MoveSpeed = 250.0f;
	std::string PrevAnimName = "";

	bool IsLeftFoot = true;
	const float DustTime = 1 / 3.0f;
	float DustTimer = 0.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void AnimationInit();
	void StateInit();
	void BringCamera();

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
	void CreateDustAnimationEffect(float _DeltaTime);
};

