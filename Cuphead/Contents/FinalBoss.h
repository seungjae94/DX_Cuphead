#pragma once
#include "FaintableBoss.h"

// Knock Out ����Ʈ�� ���� Faint�� ����, Resume�ϴ� ��� �߰�
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

