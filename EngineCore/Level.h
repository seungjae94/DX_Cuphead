#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>



// final�� ����ϸ� ���� ULevel ��ӹ��� Ŭ������ ������� �����.

// ���� :
class AActor;
class UCamera;
class URenderer;
class AGameMode;
class UEngineCore;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend URenderer;
	friend UEngineCore;
	static bool IsActorConstructer;

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
	void SpawnActor(std::string _Name, int _Order = 0)
	{
		// �� ���̿����� ������Ʈ�� �����Ҽ� �־�� �Ѵ�.
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		IsActorConstructer = false;
		// ��
		//NewActor->SetWorld(this);
		//NewActor->BeginPlay();

		PushActor(NewActor);

		// Actors[_Order].push_back(NewActor);
	}

protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

private:
	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;

	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;

	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
};

