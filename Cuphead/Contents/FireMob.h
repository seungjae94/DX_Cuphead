#pragma once

class AFireMob : public AActor
{
	GENERATED_BODY(AActor)
public:
	AFireMob();
	~AFireMob();

	AFireMob(const AFireMob& _Other) = delete;
	AFireMob(AFireMob&& _Other) noexcept = delete;
	AFireMob& operator=(const AFireMob& _Other) = delete;
	AFireMob& operator=(AFireMob&& _Other) noexcept = delete;

	void SetPlayer(AActor* _Player);
	void StateChange(std::string_view _StateName);

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UStateManager StateManager;
	UEngineRandom Random;

	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;

	AActor* Player = nullptr;
	FVector Velocity;

private:
	void RendererInit();
	void StateInit();

private:
	void RunStart();
	void Run(float _DeltaTime);
	void RunEnd();

	void JumpStart();
	void Jump(float _DeltaTime);
	void JumpEnd();

	void AirStart();
	void Air(float _DeltaTime);
	void AirEnd();
};

