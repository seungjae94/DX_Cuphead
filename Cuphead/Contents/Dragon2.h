#pragma once
#include "FinalBoss.h"

class ADragon2 : public AFinalBoss
{
	GENERATED_BODY(AFinalBoss)
public:
	ADragon2();
	~ADragon2();

	ADragon2(const ADragon2& _Other) = delete;
	ADragon2(ADragon2&& _Other) noexcept = delete;
	ADragon2& operator=(const ADragon2& _Other) = delete;
	ADragon2& operator=(ADragon2&& _Other) noexcept = delete;

	void Damage(int _Damage) override;
	void ChangeState(std::string_view _StateName);
	void SetFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback);

protected:


private:
	// 컴포넌트
	USpriteRenderer* DashRenderer = nullptr;
	USpriteRenderer* BodyRenderer = nullptr;
	USpriteRenderer* TongueRenderer = nullptr;
	USpriteRenderer* FireRenderer = nullptr;
private:
	// 로직 처리
	const float IntroMoveTime = 0.5f;
	float IntroMoveTimer = 0.0f;

	const float FireTime = 3.0f;
	float FireTimer = 0.0f;
	bool FireAnimation = false;

	const float SpawnTime = 1.0f;
	float SpawnTimer = 0.0f;
	const int JumperPeriod = 5;
	int JumperCounter = 0;
private:
	void BeginPlay() override;
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

	void FaintStart() override;
};

