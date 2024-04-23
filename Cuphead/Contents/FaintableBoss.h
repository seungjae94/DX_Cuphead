#pragma once
#include "Boss.h"

class AFaintableBoss : public ABoss
{
	GENERATED_BODY(ABoss)
public:
	AFaintableBoss();
	~AFaintableBoss();

	AFaintableBoss(const AFaintableBoss& _Other) = delete;
	AFaintableBoss(AFaintableBoss&& _Other) noexcept = delete;
	AFaintableBoss& operator=(const AFaintableBoss& _Other) = delete;
	AFaintableBoss& operator=(AFaintableBoss&& _Other) noexcept = delete;

	bool IsFainted() const;
	void SetFaintRange(const float4& _FaintRange);

protected:
	void BeginPlay() override;
	virtual void FaintStart();
	virtual void Faint(float _DeltaTime);
	virtual void FaintEnd();
	bool FaintActive = true;
private:
	float4 FaintRange;
	const float FaintTime = 5.0f;
	float FaintTimer = 0.0f;
	const float BossExplosionInterval = 0.5f;
	float BossExplosionTimer = 0.5f;
};

