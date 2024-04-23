#pragma once
#include "FaintableBoss.h"

// Knock Out 이펙트를 위해 Faint를 정지, Resume하는 기능 추가
class AFinalBoss : public AFaintableBoss
{
	GENERATED_BODY(AFaintableBoss)
public:
	AFinalBoss();
	~AFinalBoss();

	AFinalBoss(const AFinalBoss& _Other) = delete;
	AFinalBoss(AFinalBoss&& _Other) noexcept = delete;
	AFinalBoss& operator=(const AFinalBoss& _Other) = delete;
	AFinalBoss& operator=(AFinalBoss&& _Other) noexcept = delete;

	void ResumeFaint();
protected:
	void FaintStart() override;

private:
};

