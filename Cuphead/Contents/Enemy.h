#pragma once

class AEnemy : public AActor
{
	GENERATED_BODY(AActor)
public:
	AEnemy();
	~AEnemy();

	AEnemy(const AEnemy& _Other) = delete;
	AEnemy(AEnemy&& _Other) noexcept = delete;
	AEnemy& operator=(const AEnemy& _Other) = delete;
	AEnemy& operator=(AEnemy&& _Other) noexcept = delete;

	void SetHp(int _Hp);
	virtual void Damage(int _Damage) = 0;

protected:
	int Hp = 0;

private:
};

