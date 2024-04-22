#pragma once
#include "Enemy.h"

class ADragon2 : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	ADragon2();
	~ADragon2();

	ADragon2(const ADragon2& _Other) = delete;
	ADragon2(ADragon2&& _Other) noexcept = delete;
	ADragon2& operator=(const ADragon2& _Other) = delete;
	ADragon2& operator=(ADragon2&& _Other) noexcept = delete;

	bool IsFinished();
	void Damage(int _Damage) override;

protected:


private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* DashRenderer = nullptr;
	USpriteRenderer* BodyRenderer = nullptr;
	USpriteRenderer* TongueRenderer = nullptr;
	UCollision* Collision = nullptr;
private:
	// 로직 처리
	UStateManager StateManager;
	UEngineRandom Random;
	
	const float IntroMoveTime = 0.5f;
	float IntroMoveTimer = 0.0f;

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);
private:
	void RendererInit();
	void StateInit();
private:
	// 상태 함수
	void DashStart();
	void Dash(float _DeltaTime);
	void DashEnd();

	void IntroStart();
	void Intro(float _DeltaTime);
	void IntroEnd();

	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void FaintStart();
	void Faint(float _DeltaTime);
	void FaintEnd();

	void FinishStart();
	void Finish(float _DeltaTime);
	void FinishEnd();
};

