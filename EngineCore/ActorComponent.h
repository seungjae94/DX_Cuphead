#pragma once
#include "Actor.h"
#include "TickObject.h"
#include <EngineBase/NameObject.h>
#include "WorldObject.h"

// ���� : �׳� ������ ���ϴ� �ֵ��� �ְ�
class UActorComponent : public UTickObject, public UNameObject, public UWorldObject
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

