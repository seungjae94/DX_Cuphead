#pragma once
#include <vector>
#include "TickObject.h"
#include "WorldObject.h"
#include "Level.h"

// ���� : ���Ͱ� Ʈ�������� �����°� �ƴ϶�
class ULevel;
class UActorComponent;
class USceneComponent;
class AActor : public UTickObject, public UWorldObject
{
	friend ULevel;
	GENERATED_BODY(UTickObject)

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	// ������ �����ڿ����� ȣ��ɼ� �ְ� ����� ���´�.
	// �𸮾� �����ҷ��� �׳� ��.
	template<typename ComponentType>
	std::shared_ptr<ComponentType> CreateDefaultSubobject(std::string_view _Name)
	{
		if (false == ULevel::IsActorConstructer)
		{
			MsgBoxAssert("�𸮾󿡼��� �����ڿ����ۿ� ������Ʈ�� �����Ҽ� �����ϴ�.");
		}
		
		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();

		PushComponent(NewComponent, _Name);

		return std::dynamic_pointer_cast<ComponentType>(NewComponent);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// ���Ͱ� ��Ʈ ������Ʈ�� ������ 
	USceneComponent* RootComponent = nullptr;
	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);


};

