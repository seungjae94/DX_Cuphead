#include "PreCompile.h"
#include "Dragon1.h"

ADragon1::ADragon1()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("Body");
	Collision = CreateDefaultSubObject<UCollision>("Collision");

	BodyRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ADragon1::~ADragon1()
{
}

void ADragon1::BeginPlay()
{
	Super::BeginPlay();

	SetHp(629);

	RendererInit();
	StateInit();

	SetActorLocation({ 525.0f, -525.0f });
	BodyRenderer->SetPosition({ 0.0f, 0.0f });
	Collision->SetPosition(BodyRenderer->GetLocalPosition() + FVector(0.0f, 0.0f, 0.0f));
	Collision->SetScale({ 300.0f, 500.0f });
}

void ADragon1::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ADragon1::DebugUpdate(float _DeltaTime)
{
}

void ADragon1::RendererInit()
{
	BodyRenderer->CreateAnimation("dragon1_idle", "dragon1_idle.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_tail", "dragon1_tail.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_attack", "dragon1_attack.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_attack_start", "dragon1_attack_start.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_attack_end", "dragon1_attack_end.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_beam", "dragon1_beam.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_beam_start", "dragon1_beam_start.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_beam_end", "dragon1_beam_end.png", 1 / 24.0f, false);

	BodyRenderer->SetOrder(ERenderingOrder::Back6);
	BodyRenderer->SetPivot(EPivot::BOT);
	BodyRenderer->SetAutoSize(1.0f, true);
}

void ADragon1::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("Beam");
	StateManager.CreateState("RunAway");
	StateManager.CreateState("Finish");

	StateManager.SetFunction("Idle",
		std::bind(&ADragon1::IdleStart, this),
		std::bind(&ADragon1::Idle, this, std::placeholders::_1),
		std::bind(&ADragon1::IdleEnd, this)
	);

	StateManager.SetFunction("Attack",
		std::bind(&ADragon1::AttackStart, this),
		std::bind(&ADragon1::Attack, this, std::placeholders::_1),
		std::bind(&ADragon1::AttackEnd, this)
	);

	StateManager.SetFunction("Beam",
		std::bind(&ADragon1::BeamStart, this),
		std::bind(&ADragon1::Beam, this, std::placeholders::_1),
		std::bind(&ADragon1::BeamEnd, this)
	);

	StateManager.SetFunction("RunAway",
		std::bind(&ADragon1::RunAwayStart, this),
		std::bind(&ADragon1::RunAway, this, std::placeholders::_1),
		std::bind(&ADragon1::RunAwayEnd, this)
	);

	StateManager.SetFunction("Finish",
		std::bind(&ADragon1::FinishStart, this),
		std::bind(&ADragon1::Finish, this, std::placeholders::_1),
		std::bind(&ADragon1::FinishEnd, this)
	);

	StateManager.ChangeState("Idle");
}

void ADragon1::IdleStart()
{
	BodyRenderer->ChangeAnimation("dragon1_idle");
}

void ADragon1::Idle(float _DeltaTime)
{
}

void ADragon1::IdleEnd()
{
}

void ADragon1::AttackStart()
{
}

void ADragon1::Attack(float _DeltaTime)
{
}

void ADragon1::AttackEnd()
{
}

void ADragon1::BeamStart()
{
}

void ADragon1::Beam(float _DeltaTime)
{
}

void ADragon1::BeamEnd()
{
}

void ADragon1::RunAwayStart()
{
}

void ADragon1::RunAway(float _DeltaTime)
{
}

void ADragon1::RunAwayEnd()
{
}

void ADragon1::FinishStart()
{
}

void ADragon1::Finish(float _DeltaTime)
{
}

void ADragon1::FinishEnd()
{
}

void ADragon1::PlayIntroAnimation()
{
}

bool ADragon1::IsFinished()
{
	return "Finish" == StateManager.GetCurStateName();
}

void ADragon1::Damage(int _Damage)
{
}
