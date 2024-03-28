#pragma once
#include "Actor.h"

// ���� : �׳� ������ ���ϴ� �ֵ��� �ְ�
class UActorComponent
{
public:
	// constrcuter destructer
	UActorComponent();
	~UActorComponent();

	// delete Function
	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

protected:

private:
	AActor* Actor = nullptr;

};

