#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>


// final�� ����ϸ� ���� ULevel ��ӹ��� Ŭ������ ������� �����.

// ���� :
class AActor;
class AGameMode;
class UEngineCore;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend UEngineCore;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	template<typename ActorType>
	void SpawnActor(int _Order = 0, std::string _Name = "")
	{
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		Actors[_Order].push_back(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	void PushActor(std::shared_ptr<AActor> _Actor);
};

