#include "PreCompile.h"
#include "Onion.h"
#include "BossAttack.h"

AOnion::AOnion()
{
	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	OnionRenderer = CreateDefaultSubObject<USpriteRenderer>("Onion");
	LeftTearRenderer = CreateDefaultSubObject<USpriteRenderer>("LeftTear");
	RightTearRenderer = CreateDefaultSubObject<USpriteRenderer>("RightTear");

	GroundRenderer->SetupAttachment(Root);
	OnionRenderer->SetupAttachment(Root);
	LeftTearRenderer->SetupAttachment(Root);
	RightTearRenderer->SetupAttachment(Root);
}

AOnion::~AOnion()
{
}

void AOnion::PlayGroundIntroAnimation()
{
	GroundRenderer->ChangeAnimation("ground_intro");
}

void AOnion::PlayOnionIntroAnimation()
{
	OnionRenderer->ChangeAnimation("onion_intro");
}

void AOnion::PlayGroundIdleAnimation()
{
	GroundRenderer->ChangeAnimation("ground_idle");
}

void AOnion::PlayOnionIdleAnimation()
{
	OnionRenderer->ChangeAnimation("onion_idle");
}

void AOnion::SetOnionFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	OnionRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
}

void AOnion::Damage(int _Damage)
{
	if ("Faint" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	OnionRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	OnionRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	DelayCallBack(0.1f, [this]() {
		OnionRenderer->SetMulColor(FVector::One);
		OnionRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("Faint");
	}
}

void AOnion::StateChangeToAttack()
{
	StateManager.ChangeState("Attack");
}

void AOnion::BeginPlay()
{
	Super::BeginPlay();

	SetHp(400);

	RendererInit();
	StateInit();

	SetActorLocation({ 0.0f, -335.0f });

	GroundRenderer->SetPosition({ 0.0f, -35.0f });
	LeftTearRenderer->SetPosition({ -350.0f, 555.0f });
	RightTearRenderer->SetPosition({ 330.0f, 555.0f });

	Collision->SetPosition(OnionRenderer->GetLocalPosition() + FVector(0.0f, 250.0f, 0.0f));
	Collision->SetScale({ 480.0f, 480.0f });
	Collision->SetActive(false);
}

void AOnion::RendererInit()
{
	OnionRenderer->CreateAnimation("onion_intro", "onion_intro.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_idle", "onion_idle.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_faint", "onion_faint.png", 1 / 24.0f, true);
	OnionRenderer->CreateAnimation("onion_cry_intro", "onion_cry_intro.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_cry_start", "onion_cry_start.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_cry_loop", "onion_cry_loop.png", 1 / 12.0f, true);
	OnionRenderer->CreateAnimation("onion_cry_wait", "onion_cry_wait.png", 1 / 12.0f, true);

	GroundRenderer->CreateAnimation("ground_intro", "onion_ground_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundRenderer->CreateAnimation("ground_idle", "onion_ground_idle.png", 1 / 12.0f, false);

	LeftTearRenderer->CreateAnimation("onion_tear_start", "onion_tear_start.png", 1 / 12.0f, false);
	LeftTearRenderer->CreateAnimation("onion_tear_loop", "onion_tear_loop.png", 1 / 12.0f, true);
	LeftTearRenderer->CreateAnimation("onion_tear_end", "onion_tear_end.png", 1 / 12.0f, false);

	RightTearRenderer->CreateAnimation("onion_tear_start", "onion_tear_start.png", 1 / 12.0f, false);
	RightTearRenderer->CreateAnimation("onion_tear_loop", "onion_tear_loop.png", 1 / 12.0f, true);
	RightTearRenderer->CreateAnimation("onion_tear_end", "onion_tear_end.png", 1 / 12.0f, false);

	GroundRenderer->SetFrameCallback("ground_intro", 20, [this]() {
		OnionRenderer->ChangeAnimation("onion_intro");
		Collision->SetActive(true);
		});

	GroundRenderer->SetFrameCallback("ground_intro", 27, [this]() {
		GroundRenderer->ChangeAnimation("ground_idle");
		});

	OnionRenderer->SetFrameCallback("onion_intro", 23, [this]() {
		OnionRenderer->ChangeAnimation("onion_cry_intro");
		});

	OnionRenderer->SetFrameCallback("onion_cry_start", 10, [this]() {
		OnionRenderer->ChangeAnimation("onion_cry_loop");
		});

	LeftTearRenderer->SetFrameCallback("onion_tear_start", 4, [this]() {
		LeftTearRenderer->ChangeAnimation("onion_tear_loop");
		});

	RightTearRenderer->SetFrameCallback("onion_tear_start", 4, [this]() {
		RightTearRenderer->ChangeAnimation("onion_tear_loop");
		});

	OnionRenderer->SetOrder(ERenderingOrder::Back5);
	GroundRenderer->SetOrder(ERenderingOrder::Back6);
	LeftTearRenderer->SetOrder(ERenderingOrder::Back6);
	RightTearRenderer->SetOrder(ERenderingOrder::Back6);

	OnionRenderer->SetPivot(EPivot::BOT);
	GroundRenderer->SetPivot(EPivot::BOT);

	OnionRenderer->SetAutoSize(1.0f, true);
	GroundRenderer->SetAutoSize(1.25f, true);
	LeftTearRenderer->SetAutoSize(0.95f, true);
	RightTearRenderer->SetAutoSize(0.95f, true);

	LeftTearRenderer->SetDir(EEngineDir::Left);
}

void AOnion::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("AttackWait");

	StateManager.SetFunction("Idle",
		std::bind(&AOnion::IdleStart, this),
		std::bind(&AOnion::Idle, this, std::placeholders::_1),
		std::bind(&AOnion::IdleEnd, this)
	);

	StateManager.SetFunction("Attack",
		std::bind(&AOnion::AttackStart, this),
		std::bind(&AOnion::Attack, this, std::placeholders::_1),
		std::bind(&AOnion::AttackEnd, this)
	);

	StateManager.SetFunction("AttackWait",
		std::bind(&AOnion::AttackWaitStart, this),
		std::bind(&AOnion::AttackWait, this, std::placeholders::_1),
		std::bind(&AOnion::AttackWaitEnd, this)
	);

	StateManager.ChangeState("Idle");
}

void AOnion::IdleStart()
{
}

void AOnion::Idle(float _DeltaTime)
{
}

void AOnion::IdleEnd()
{
}

void AOnion::AttackStart()
{
	OnionRenderer->ChangeAnimation("onion_cry_start");
	LeftTearRenderer->ChangeAnimation("onion_tear_start");
	RightTearRenderer->ChangeAnimation("onion_tear_start");

	AttackTotalTimer = AttackTotalTime;
	AttackTimer = AttackInterval;
}

void AOnion::Attack(float _DeltaTime)
{
	AttackTotalTimer -= _DeltaTime;
	AttackTimer -= _DeltaTime;

	if (AttackTotalTimer < 0.0f)
	{
		StateManager.ChangeState("AttackWait");
		return;
	}

	if (AttackTimer >= 0.0f)
	{
		return;
	}

	ABossAttack* Attack = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
	Attack->SetRenderingOrder(ERenderingOrder::Bullet);

	float RandomX = 0.0f;
	while (RandomX > -300.0f && RandomX < 300.0f)
	{
		RandomX = Random.RandomFloat(-640.0f, 640.0f);
	}

	int RandomValue = Random.RandomInt(0, 9);

	Attack->SetActorLocation({ RandomX, 300.0f, 0.0f });
	Attack->SetVelocity(FVector::Down * 650.0f);
	Attack->SetCollisionPosition({ 0.0f, 0.0f });
	Attack->SetCollisionScale({30.0f, 50.0f});
	Attack->SetDestroyTime(3.0f);

	if (0 == RandomValue)
	{
		Attack->SetAnimation("onion_attack_pink", "onion_attack_pink.png", 1 / 12.0f, true);
		Attack->SetParryable(true);
	}
	else
	{
		Attack->SetAnimation("onion_attack", "onion_attack.png", 1 / 12.0f, true);
	}

	AttackTimer = AttackInterval;
}

void AOnion::AttackEnd()
{
}

void AOnion::AttackWaitStart()
{
	AttackWaitTimer = AttackWaitTime;
	OnionRenderer->ChangeAnimation("onion_cry_wait");
	LeftTearRenderer->ChangeAnimation("onion_tear_end");
	RightTearRenderer->ChangeAnimation("onion_tear_end");
}

void AOnion::AttackWait(float _DeltaTime)
{
	AttackWaitTimer -= _DeltaTime;

	if (AttackWaitTimer < 0.0f)
	{
		StateManager.ChangeState("Attack");
	}
}

void AOnion::AttackWaitEnd()
{
}

void AOnion::FaintStart()
{
	Super::FaintStart();
	SetFaintRange({ -100.0f, 100.0f, 0.0f, 400.0f });

	OnionRenderer->ChangeAnimation("onion_faint");
	LeftTearRenderer->SetActive(false);
	RightTearRenderer->SetActive(false);

	Collision->SetActive(false);

	ShrinkTimer = ShrinkWaitTime;
}

void AOnion::Faint(float _DeltaTime)
{
	Super::Faint(_DeltaTime);

	ShrinkTimer -= _DeltaTime;

	if (ShrinkTimer < 0.0f)
	{
		OnionRenderer->AddPosition(FVector::Down * 200.0f * _DeltaTime);
	}

	if (ShrinkTimer < -3.0f)
	{
		StateManager.ChangeState(GStateName::Finish);
	}
}

void AOnion::FaintEnd()
{
	Super::FaintEnd();

	OnionRenderer->SetActive(false);
	GroundRenderer->SetActive(false);
}