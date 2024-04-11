#pragma once

class APlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

protected:

private:
	const float RunSpeed = 100.0f;
	bool IsLeft = false;
	UStateManager StateManager;
	USpriteRenderer* Renderer = nullptr;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 상태 함수
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void RunStart();
	void Run(float _DeltaTime);
	void RunEnd();
};

