#include "PreCompile.h"
#include "Potato.h"
#include "BossAttack.h"

APotato::APotato()
{
	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	PotatoRenderer = CreateDefaultSubObject<USpriteRenderer>("Potato");

	GroundRenderer->SetupAttachment(Root);
	PotatoRenderer->SetupAttachment(Root);
}

APotato::~APotato()
{
}

void APotato::PlayGroundIntroAnimation()
{
	GroundRenderer->ChangeAnimation("ground_intro");
}

void APotato::PlayPotatoIntroAnimation()
{
	PotatoRenderer->ChangeAnimation("potato_intro");
}

void APotato::PlayGroundIdleAnimation()
{
	GroundRenderer->ChangeAnimation("ground_idle");
}

void APotato::PlayPotatoIdleAnimation()
{
	PotatoRenderer->ChangeAnimation("potato_idle");
}

void APotato::SetPotatoFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	PotatoRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
}

void APotato::StateChangeToAttack()
{
	StateManager.ChangeState("Attack");
}

void APotato::Damage(int _Damage)
{
	if ("Faint" == StateManager.GetCurStateName() || "Finish" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	PotatoRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	PotatoRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	DelayCallBack(0.1f, [this]() {
		PotatoRenderer->SetMulColor(FVector::One);
		PotatoRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("Faint");
	}
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	SetHp(360);

	RendererInit();
	StateInit();

	SetActorLocation({ 450.0f, -250.0f });
	PotatoRenderer->SetPosition({ 0.0f, -50.0f });
	GroundRenderer->SetPosition({ 0.0f, -80.0f });
	Collision->SetPosition(PotatoRenderer->GetLocalPosition() + FVector(0.0f, 200.0f, 0.0f));
	Collision->SetScale({ 300.0f, 400.0f });
}

void APotato::RendererInit()
{
	PotatoRenderer->CreateAnimation("potato_intro", "potato_intro.png", 1 / 12.0f, false);
	PotatoRenderer->CreateAnimation("potato_idle", "potato_idle.png", 1 / 6.0f, true);
	PotatoRenderer->CreateAnimation("potato_attack", "potato_attack.png", 1 / 24.0f, false);
	PotatoRenderer->CreateAnimation("potato_faint", "potato_faint.png",
		std::vector<float>(12, 1 / 12.0f),
		{ 2, 3, 4, 5, 6, 7, 8, 6, 5, 4, 3 }, true);
	GroundRenderer->CreateAnimation("ground_intro", "potato_ground_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundRenderer->CreateAnimation("ground_idle", "potato_ground_idle.png", 1 / 12.0f, false);

	GroundRenderer->SetFrameCallback("ground_intro", 20, [this]() {
		PotatoRenderer->ChangeAnimation("potato_intro");
	});

	GroundRenderer->SetFrameCallback("ground_intro", 27, [this]() {
		GroundRenderer->ChangeAnimation("ground_idle");
	});

	PotatoRenderer->SetOrder(ERenderingOrder::Back5);
	GroundRenderer->SetOrder(ERenderingOrder::Back6);

	PotatoRenderer->SetPivot(EPivot::BOT);
	GroundRenderer->SetPivot(EPivot::BOT);

	PotatoRenderer->SetAutoSize(1.25f, true);
	GroundRenderer->SetAutoSize(1.25f, true);
}

void APotato::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("AttackWait");

	StateManager.SetFunction("Idle",
		std::bind(&APotato::IdleStart, this),
		std::bind(&APotato::Idle, this, std::placeholders::_1),
		std::bind(&APotato::IdleEnd, this)
	);

	StateManager.SetFunction("Attack",
		std::bind(&APotato::AttackStart, this),
		std::bind(&APotato::Attack, this, std::placeholders::_1),
		std::bind(&APotato::AttackEnd, this)
	);

	StateManager.SetFunction("AttackWait",
		std::bind(&APotato::AttackWaitStart, this),
		std::bind(&APotato::AttackWait, this, std::placeholders::_1),
		std::bind(&APotato::AttackWaitEnd, this)
	);

	StateManager.ChangeState("Idle");
}

void APotato::IdleStart()
{
}

void APotato::Idle(float _DeltaTime)
{
}

void APotato::IdleEnd()
{
}

void APotato::AttackStart()
{
	AttackPhase = (AttackPhase + 1) % 3;
	AttackCount = 0;
	AttackTimer = 0.0f;
}

void APotato::Attack(float _DeltaTime)
{
	AttackTimer -= _DeltaTime;

	if (AttackTimer >= 0.0f)
	{
		return;
	}

	if (MaxAttackCount == AttackCount)
	{
		StateManager.ChangeState("AttackWait");
		return;
	}

	ABossAttack* Attack = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
	Attack->SetRenderingOrder(ERenderingOrder::Bullet);
	Attack->SetActorLocation(GetActorLocation() + FVector(-30.0f, 30.0f, 0.0f));
	Attack->SetVelocity(FVector::Left * 650.0f);
	Attack->SetDestroyTime(3.0f);
	Attack->SetCollisionPosition({0.0f, 0.0f});
	Attack->SetCollisionScale({75.0f, 75.0f});

	++AttackCount;

	PotatoRenderer->AnimationReset();
	PotatoRenderer->ChangeAnimation("potato_attack");
	if (MaxAttackCount == AttackCount)
	{
		Attack->SetAnimation("potato_attack_snake", "potato_attack_snake.png", 1 / 12.0f, true);
		Attack->SetCollisionPosition({ -5.0f, -10.0f });
		Attack->SetParryable(true);
	}
	else
	{
		Attack->SetAnimation("potato_attack_ball", "potato_attack_ball.png", 1 / 12.0f, true);
	}

	AttackTimer = AttackDelays[AttackPhase];
}

void APotato::AttackEnd()
{
}


void APotato::AttackWaitStart()
{
	AttackWaitTimer = AttackWaitTime;
	PotatoRenderer->ChangeAnimation("potato_idle");
}

void APotato::AttackWait(float _DeltaTime)
{
	AttackWaitTimer -= _DeltaTime;

	if (AttackWaitTimer < 0.0f)
	{
		StateManager.ChangeState("Attack");
	}
}

void APotato::AttackWaitEnd()
{
}


void APotato::FaintStart()
{
	Super::FaintStart();
	SetFaintRange({ -100.0f, 100.0f, 0.0f, 400.0f });

	PotatoRenderer->ChangeAnimation("potato_faint");
	Collision->SetActive(false);

	ShrinkTimer = ShrinkWaitTime;
}

void APotato::Faint(float _DeltaTime)
{
	Super::Faint(_DeltaTime);

	ShrinkTimer -= _DeltaTime;

	if (ShrinkTimer < 0.0f)
	{
		PotatoRenderer->AddPosition(FVector::Down * 200.0f * _DeltaTime);
	}

	if (ShrinkTimer < -3.0f)
	{
		StateManager.ChangeState(GStateName::Finish);
	}
}

void APotato::FaintEnd()
{
	Super::FaintEnd();

	PotatoRenderer->SetActive(false);
	GroundRenderer->SetActive(false);
}
