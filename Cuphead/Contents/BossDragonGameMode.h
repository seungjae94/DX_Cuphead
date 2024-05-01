#pragma once
#include "BossGameMode.h"

class ABossDragonMap;
class ADragon1;
class ADragon2;
class ADragon3;
class APlayer;
class APlatform;

class ABossDragonGameMode : public ABossGameMode
{
	GENERATED_BODY(ABossGameMode)
public:
	ABossDragonGameMode();
	~ABossDragonGameMode();

	ABossDragonGameMode(const ABossDragonGameMode& _Other) = delete;
	ABossDragonGameMode(ABossDragonGameMode&& _Other) noexcept = delete;
	ABossDragonGameMode& operator=(const ABossDragonGameMode& _Other) = delete;
	ABossDragonGameMode& operator=(ABossDragonGameMode&& _Other) noexcept = delete;

protected:
private:
	UEngineSoundPlayer BgmPlayer;
	ABossDragonMap* Map = nullptr;
	ADragon1* Dragon1 = nullptr;
	ADragon2* Dragon2 = nullptr;
	ADragon3* Dragon3 = nullptr;
private:
	const float CloudSpawnInterval = 2.5f;
	float CloudSpawnTimer = 0.0f;

	float LastCloudY = 0.0f;
	float SecondLastCloudY = 0.0f;
private:
	// 초기화 함수
	void StateInit();
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;
private:
	// 상태 함수
	void IntroStart() override;
	void Intro(float _DeltaTime) override;
	void IntroEnd() override;

	void Phase1Start();
	void Phase1(float _DeltaTime);
	void Phase1End();

	void Phase2IntroStart();
	void Phase2Intro(float _DeltaTime);
	void Phase2IntroEnd();

	void Phase2Start();
	void Phase2(float _DeltaTime);
	void Phase2End();

	void FinishStart();
	void Finish(float _DeltaTime);
	void FinishEnd();

	void Phase3IntroStart();
	void Phase3Intro(float _DeltaTime);
	void Phase3IntroEnd();

	void Phase3Start();
	void Phase3(float _DeltaTime);
	void Phase3End();
private:
	std::list<APlatform*> Clouds;
	void SpawnClouds(float _DeltaTime);
	APlatform* SpawnCloud(bool _SetLocation, const FVector& _Location = FVector::Zero);
};

