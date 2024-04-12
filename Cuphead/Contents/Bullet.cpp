#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

ABullet::~ABullet()
{
}

void ABullet::SetDirection(EDirection _Direction)
{
	Direction = _Direction;
	StateManager.ChangeState(GStateName::Move);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
}

void ABullet::AnimationInit()
{
	Renderer->SetSprite(GImageName::BulletMove);
	Renderer->SetAutoSize(0.9f, true);
	Renderer->SetOrder(ERenderingOrder::Bullet);

	Renderer->CreateAnimation(GAnimName::BulletMove, GImageName::BulletMove, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletDestroy, GImageName::BulletDestroy, 0.1f, false);
}

void ABullet::StateInit()
{
	StateManager.CreateState(GStateName::Move);
	StateManager.CreateState(GStateName::Destroy);

	std::function<void()> MoveStartFunc = [this]() {
		this->RefreshRotation();
		Renderer->ChangeAnimation(GAnimName::BulletMove);
	};
	std::function<void(float)> MoveUpdateFunc = std::bind(&ABullet::Move, this, std::placeholders::_1);
	std::function<void()> MoveEndFunc = []() {};
	StateManager.SetFunction(GStateName::Move, MoveStartFunc, MoveUpdateFunc, MoveEndFunc);
}

void ABullet::RefreshRotation()
{
	switch (Direction)
	{
	case EDirection::Right:
		break;
	case EDirection::RightUp:
		SetActorRotation({ 0.0f, 0.0f, 45.0f });
		break;
	case EDirection::Up:
		SetActorRotation({ 0.0f, 0.0f, 90.0f });
		break;
	case EDirection::LeftUp:
		SetActorRotation({ 0.0f, 0.0f, 135.0f });
		break;
	case EDirection::Left:
		SetActorRotation({ 0.0f, 0.0f, 180.0f });
		break;
	case EDirection::LeftDown:
		SetActorRotation({ 0.0f, 0.0f, 225.0f });
		break;
	case EDirection::Down:
		SetActorRotation({ 0.0f, 0.0f, 270.0f });
		break;
	case EDirection::RightDown:
		SetActorRotation({ 0.0f, 0.0f, 315.0f });
		break;
	default:
		break;
	}
}

void ABullet::Move(float _DeltaTime)
{
	FVector Displacement = UConverter::ConvDirectionToFVector(Direction) * Speed * _DeltaTime;
	AddActorLocation(Displacement);
}
