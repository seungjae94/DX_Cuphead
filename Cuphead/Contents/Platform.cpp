#include "PreCompile.h"
#include "Platform.h"

UPlatform::UPlatform()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Renderer->SetParent(Root);
	Collision->SetParent(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Platform);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

UPlatform::~UPlatform()
{
}

void UPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void UPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 충돌 처리
	if (nullptr != OnStepEnter)
	{
		Collision->CollisionEnter(ECollisionGroup::Player, OnStepEnter);
	}
	if (nullptr != OnStepStay)
	{
		Collision->CollisionStay(ECollisionGroup::Player, OnStepStay);
	}
	if (nullptr != OnStepExit)
	{
		Collision->CollisionExit(ECollisionGroup::Player, OnStepExit);
	}
}

void UPlatform::CreateAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Interval, bool _Loop)
{
	Renderer->CreateAnimation(_AnimName, _SpriteName, _Interval, _Loop);
}

void UPlatform::ChangeAnimation(std::string_view _AnimName)
{
	Renderer->ChangeAnimation(_AnimName);
}

void UPlatform::SetCollisionPosition(const FVector& _Position)
{
	Collision->SetPosition(_Position);
}

void UPlatform::SetCollisionScale(const FVector& _Scale)
{
	Collision->SetScale(_Scale);
}

void UPlatform::SetOnStepEnter(std::function<void(std::shared_ptr<UCollision>)> _OnStepEnter)
{
	OnStepEnter = _OnStepEnter;
}

void UPlatform::SetOnStepStay(std::function<void(std::shared_ptr<UCollision>)> _OnStepStay)
{
	OnStepStay = _OnStepStay;
}

void UPlatform::SetOnStepExit(std::function<void(std::shared_ptr<UCollision>)> _OnStepExit)
{
	OnStepExit = _OnStepExit;
}

void UPlatform::SetFrameCallback(std::string_view _AnimName, int _Index, std::function<void()> _Callback)
{
	Renderer->SetFrameCallback(_AnimName, _Index, _Callback);
}
