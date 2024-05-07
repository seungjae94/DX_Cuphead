#pragma once

// 공통 컴포넌트 보유
// Finish 상태 처리
// Hp 관리
class ABoss : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABoss();
	~ABoss();

	ABoss(const ABoss& _Other) = delete;
	ABoss(ABoss&& _Other) noexcept = delete;
	ABoss& operator=(const ABoss& _Other) = delete;
	ABoss& operator=(ABoss&& _Other) noexcept = delete;

	void SetHp(int _Hp);
	virtual void Damage(int _Damage) = 0;
	bool IsFinished() const;
	void BodyDamageOff();

protected:
	int Hp = 0;
	static FVector HitPlusColor;
protected:
	// 보스 공통 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	UCollision* Collision = nullptr;
	UStateManager StateManager;
	UEngineRandom Random;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	virtual void DebugUpdate(float _DeltaTime);
protected:
	void FinishStart() {};
	void Finish(float _DeltaTime) {};
	void FinishEnd() {};
private:
	void BodyDamageCheck();
	bool HasBodyDamage = true;

};

