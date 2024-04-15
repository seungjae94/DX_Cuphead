#include "PreCompile.h"
#include "Bullet.h"
#include "Enemy.h"

ABullet::ABullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Bullet);
	Collision->SetCollisionType(ECollisionType::Rect);
	Collision->SetScale({ 100.0f, 50.0f, 1.0f });

	CollisionRenderer = CreateDefaultSubObject<USpriteRenderer>("CollisionRenderer");
	CollisionRenderer->SetupAttachment(Root);
	CollisionRenderer->SetPosition(Collision->GetLocalPosition());
	CollisionRenderer->SetScale(Collision->GetLocalScale());
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

	DelayCallBack(1.0f, [this]() {
		Destroy();
	});

	AnimationInit();
	StateInit();
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugMsgUpdate(_DeltaTime);
}

void ABullet::DebugMsgUpdate(float _DeltaTime)
{
}

void ABullet::AnimationInit()
{
	Renderer->SetSprite(GImageName::BulletMove);
	Renderer->SetAutoSize(0.9f, true);
	Renderer->SetOrder(ERenderingOrder::Bullet);

	Renderer->CreateAnimation(GAnimName::BulletMove, GImageName::BulletMove, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletDestroy, GImageName::BulletDestroy, 0.1f, false);

	CollisionRenderer->SetSprite("debug_rect.png");
	CollisionRenderer->SetOrder(ERenderingOrder::Collider);
	CollisionRenderer->SetActive(false);
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

	Collision->CollisionEnter(ECollisionGroup::Monster, [=](std::shared_ptr<UCollision> _Collision)
	{
		// 상태, 애니메이션 변경
		AEnemy* Enemy = dynamic_cast<AEnemy*>(_Collision->GetActor());

		if (nullptr == Enemy)
		{
			return;
		}

		Enemy->Damage(Damage);
	});
}
