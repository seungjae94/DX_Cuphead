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

	Renderer->SetAutoSize(1.0f, true);
}

void UPlatform::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 面倒 贸府
	if (nullptr != OnStepEnter)
	{
		Collision->CollisionEnter(ECollisionGroup::PlayerPhysicsBot, OnStepEnter);
	}
	if (nullptr != OnStepStay)
	{
		Collision->CollisionStay(ECollisionGroup::PlayerPhysicsBot, OnStepStay);
	}
	if (nullptr != OnStepExit)
	{
		Collision->CollisionExit(ECollisionGroup::PlayerPhysicsBot, OnStepExit);
	}

	// 捞悼 贸府
	if (true == MoveStarted)
	{
		AddActorLocation(Velocity * _DeltaTime);

		Collision->CollisionStay(ECollisionGroup::PlayerPhysicsBot, [this, _DeltaTime](std::shared_ptr<UCollision> _Collision) {
			_Collision->GetActor()->AddActorLocation(Velocity * _DeltaTime);
			});

		float PosX = GetActorLocation().X;

		if (PosX < -700.0f || PosX > 700.0f)
		{
			Destroy();
		}
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

void UPlatform::SetRenderingOrder(ERenderingOrder _Order)
{
	Renderer->SetOrder(_Order);
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

void UPlatform::SetVelocity(const FVector& _Velocity)
{
	Velocity = _Velocity;
}

void UPlatform::MoveStart()
{
	MoveStarted = true;
}
