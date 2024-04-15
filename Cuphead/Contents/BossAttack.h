#pragma once

enum class EChaseType
{
	None,
	Temporal,
	Permanent,
	InitialPosition,
	Special
};

class BossAttack : public AActor
{
	GENERATED_BODY(AActor)
public:
	BossAttack();
	~BossAttack();

	BossAttack(const BossAttack& _Other) = delete;
	BossAttack(BossAttack&& _Other) noexcept = delete;
	BossAttack& operator=(const BossAttack& _Other) = delete;
	BossAttack& operator=(BossAttack&& _Other) noexcept = delete;

protected:

private:
	// 컴포넌트
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
private:
	// 로직
	bool Destroyable = false;
	bool Parrayable = false;
	EChaseType ChaseType = EChaseType::None;
};

