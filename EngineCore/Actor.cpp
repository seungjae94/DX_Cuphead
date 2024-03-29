#include "PreCompile.h"
#include "Actor.h"
#include "SceneComponent.h"
#include "DefaultSceneComponent.h"

AActor::AActor() 
{
	// 
}

AActor::~AActor() 
{
}

void AActor::RootCheck()
{
	if (nullptr == RootComponent)
	{
		RootComponent = CreateDefaultSubObject<UDefaultSceneComponent>("UDefaultSceneComponent");
	}
}

void AActor::BeginPlay()
{
	Super::BeginPlay();

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->SetWorld(GetWorld());
		Components[i]->BeginPlay();
	}
}

void AActor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < Components.size(); i++)
	{
		Components[i]->Tick(_DeltaTime);
	}
}

void AActor::PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name)
{

	_Component->SetName(_Name);
	Components.push_back(_Component);

	// shared_ptr�� �����ϰ� �ٿ�ĳ�����ϴ� �Լ�
	std::shared_ptr<USceneComponent> SceneComponent = std::dynamic_pointer_cast<USceneComponent>(_Component);

	if (nullptr == RootComponent && nullptr != SceneComponent)
	{
		// std::shared_ptr�� �׳� �����ͷ� �����ϴ� �Լ�
		RootComponent = SceneComponent.get();
	}
}