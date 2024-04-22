#include "PreCompile.h"
#include "Platform.h"

APlatform::APlatform()
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

APlatform::~APlatform()
{
}

void APlatform::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(1.0f, true);
}

void APlatform::Tick(float _DeltaTime)
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

		float PosX = GetActorLocation().X;

		if (PosX < -700.0f || PosX > 700.0f)
		{
			Destroy();
		}
	}
}

void APlatform::CreateAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Interval, bool _Loop)
{
	Renderer->CreateAnimation(_AnimName, _SpriteName, _Interval, _Loop);
}

void APlatform::ChangeAnimation(std::string_view _AnimName)
{
	Renderer->ChangeAnimation(_AnimName);
}

void APlatform::SetCollisionPosition(const FVector& _Position)
{
	Collision->SetPosition(_Position);
}

void APlatform::SetCollisionScale(const FVector& _Scale)
{
	Collision->SetScale(_Scale);
}

void APlatform::SetRenderingOrder(ERenderingOrder _Order)
{
	Renderer->SetOrder(_Order);
}

void APlatform::SetOnStepEnter(std::function<void(std::shared_ptr<UCollision>)> _OnStepEnter)
{
	OnStepEnter = _OnStepEnter;
}

void APlatform::SetOnStepStay(std::function<void(std::shared_ptr<UCollision>)> _OnStepStay)
{
	OnStepStay = _OnStepStay;
}

void APlatform::SetOnStepExit(std::function<void(std::shared_ptr<UCollision>)> _OnStepExit)
{
	OnStepExit = _OnStepExit;
}

void APlatform::SetFrameCallback(std::string_view _AnimName, int _Index, std::function<void()> _Callback)
{
	Renderer->SetFrameCallback(_AnimName, _Index, _Callback);
}

void APlatform::SetVelocity(const FVector& _Velocity)
{
	Velocity = _Velocity;
}

FVector APlatform::GetVelocity() const
{
	return Velocity;
}

void APlatform::MoveStart()
{
	MoveStarted = true;
}
