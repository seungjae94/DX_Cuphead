#pragma once
#include "BossAttack.h"

class ACarrotBeam : public ABossAttack
{
	GENERATED_BODY(ABossAttack)
public:
	ACarrotBeam();
	~ACarrotBeam();

	ACarrotBeam(const ACarrotBeam& _Other) = delete;
	ACarrotBeam(ACarrotBeam&& _Other) noexcept = delete;
	ACarrotBeam& operator=(const ACarrotBeam& _Other) = delete;
	ACarrotBeam& operator=(ACarrotBeam&& _Other) noexcept = delete;

protected:


private:
	void Tick(float _DeltaTime) override;

};

