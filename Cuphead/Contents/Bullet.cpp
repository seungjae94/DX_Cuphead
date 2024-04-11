#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ABullet::~ABullet()
{
}

void ABullet::SetDirection(EDirection _Direction)
{
	Direction = _Direction;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	AnimationInit();
	StateInit();

	StateManager.ChangeState(GStateName::Spawn);
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
}

void ABullet::AnimationInit()
{
	Renderer->SetSprite(GImageName::BulletSpawn);
	Renderer->SetAutoSize(1.0f, true);

	Renderer->CreateAnimation(GAnimName::BulletSpawn, GImageName::BulletSpawn, 0.1f, false);
	Renderer->CreateAnimation(GAnimName::BulletMove, GImageName::BulletMove, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletDestroy, GImageName::BulletDestroy, 0.1f, false);

	Renderer->SetFrameCallback(GAnimName::BulletSpawn, 4, [=]() {
		StateManager.ChangeState(GStateName::Move);
	});
}

void ABullet::StateInit()
{
	StateManager.CreateState(GStateName::Spawn);
	StateManager.CreateState(GStateName::Move);
	StateManager.CreateState(GStateName::Destroy);

	std::function<void()> SpawnStartFunc = [=]() {
		Renderer->ChangeAnimation(GAnimName::BulletSpawn);
	};
	std::function<void(float)> SpawnUpdateFunc = [](float _DeltaTime) {};
	std::function<void()> SpawnEndFunc = []() {};
	StateManager.SetFunction(GStateName::Spawn, SpawnStartFunc, SpawnUpdateFunc, SpawnEndFunc);

	std::function<void()> MoveStartFunc = [=]() {
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
