#pragma once
#include <vector>
#include "TickObject.h"

// ���� : ���Ͱ� Ʈ�������� �����°� �ƴ϶�
class ULevel;
class USceneComponent;
class AActor : public UTickObject
{
	friend ULevel;

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime);

private:
	// ���Ͱ� ��Ʈ ������Ʈ�� ������ 
	USceneComponent* RootComponent = nullptr;
	// std::vector<UActorComponent*> Components;
};

