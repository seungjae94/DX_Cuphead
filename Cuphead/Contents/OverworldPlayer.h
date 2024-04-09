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
	const float MoveSpeed = 200.0f;

	// ImageNameMap[AnimName] = ImageName
	std::map<std::string, std::string> ImageNameMap;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 유틸 함수
	static std::string TransDirectionToAnimName(EDirection _Direction, bool _IsIdle);

	void AnimationInit();
	void StateInit();

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

