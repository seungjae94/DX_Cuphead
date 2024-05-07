#include "PreCompile.h"
#include "Boss.h"
#include "Player.h"

FVector ABoss::HitPlusColor = { 0.25f, 0.25f, 0.25f, 0.0f };

ABoss::ABoss()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ABoss::~ABoss()
{
}

void ABoss::SetHp(int _Hp)
{
	Hp = _Hp;
}

bool ABoss::IsFinished() const
{
	return "Finish" == StateManager.GetCurStateName();
}

void ABoss::BodyDamageOff()
{
	HasBodyDamage = false;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	StateManager.CreateState("Finish");
	StateManager.SetFunction("Finish",
		std::bind(&ABoss::FinishStart, this),
		std::bind(&ABoss::Finish, this, std::placeholders::_1),
		std::bind(&ABoss::FinishEnd, this)
	);
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
	BodyDamageCheck();
}

void ABoss::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("{} Hp : {}\n", GetName(), Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("{} State : {}\n", GetName(), StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ABoss::BodyDamageCheck()
{
	if (false == HasBodyDamage)
	{
		return;
	}

	Collision->CollisionStay(ECollisionGroup::PlayerHitBox,
		[this](std::shared_ptr<UCollision> _PlayerCollision) {
			APlayer* Player = dynamic_cast<APlayer*>(_PlayerCollision->GetActor());

			if (nullptr == Player)
			{
				return;
			}

			Player->Damage();
		});
}
