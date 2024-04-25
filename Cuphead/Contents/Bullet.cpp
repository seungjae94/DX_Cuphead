#include "PreCompile.h"
#include "Bullet.h"
#include "Boss.h"
#include "Player.h"

ABullet::ABullet()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Bullet);
	Collision->SetCollisionType(ECollisionType::RotRect);
	Collision->SetScale({ 100.0f, 50.0f, 1.0f });
}

ABullet::~ABullet()
{
}

void ABullet::AnimationInit(FCreateAnimationParameter _MoveAnimParam, FCreateAnimationParameter _DestroyAnimParam)
{
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Bullet);

	Renderer->CreateAnimation(_MoveAnimParam.AnimName, _MoveAnimParam.ImageName, _MoveAnimParam.Interval);
	Renderer->CreateAnimation(_DestroyAnimParam.AnimName, _DestroyAnimParam.ImageName, _DestroyAnimParam.Interval, false);

	MoveAnimName = _MoveAnimParam.AnimName;
	DestroyAnimName = _DestroyAnimParam.AnimName;

	Renderer->SetLastFrameCallback(_DestroyAnimParam.AnimName, [this]() {
		Destroy();
		});
}

void ABullet::SetDamage(int _Damage)
{
	Damage = _Damage;
}

void ABullet::SetDirection(EDirection _Direction)
{
	Direction = _Direction;
	StateManager.ChangeState(GStateName::Move);
}

void ABullet::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	DelayCallBack(1.0f, [this]() {
		Destroy();
		});

	StateInit();
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
}

void ABullet::StateInit()
{
	StateManager.CreateState(GStateName::Move);
	StateManager.CreateState(GStateName::Destroy);

	std::function<void()> MoveStartFunc = [this]() {
		RefreshRotation();
		Renderer->ChangeAnimation(MoveAnimName);
		};
	std::function<void(float)> MoveUpdateFunc = std::bind(&ABullet::Move, this, std::placeholders::_1);
	std::function<void()> MoveEndFunc = []() {};
	StateManager.SetFunction(GStateName::Move, MoveStartFunc, MoveUpdateFunc, MoveEndFunc);

	StateManager.SetFunction(GStateName::Destroy, [this]() {
			Renderer->ChangeAnimation(DestroyAnimName);
		},
		[](float _DeltaTime) {},
		[]() {}
	);
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

	Collision->CollisionEnter(ECollisionGroup::Monster, [this](std::shared_ptr<UCollision> _Collision)
		{
			// 상태, 애니메이션 변경
			ABoss* Enemy = dynamic_cast<ABoss*>(_Collision->GetActor());

			if (nullptr == Enemy)
			{
				return;
			}

			Enemy->Damage(Damage * Player->GetDamageCoeff());
			Player->AddSuperMeter(1 / 40.0f);

			StateManager.ChangeState(GStateName::Destroy);
		});
}
