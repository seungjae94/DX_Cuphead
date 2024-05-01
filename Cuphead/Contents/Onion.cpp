#include "PreCompile.h"
#include "Onion.h"
#include "BossAttack.h"

AOnion::AOnion()
{
	GroundFrontRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundFront");
	GroundBackRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundBack");
	OnionRenderer = CreateDefaultSubObject<UCropSpriteRenderer>("Onion");
	LeftTearRenderer = CreateDefaultSubObject<USpriteRenderer>("LeftTear");
	RightTearRenderer = CreateDefaultSubObject<USpriteRenderer>("RightTear");

	GroundFrontRenderer->SetupAttachment(Root);
	GroundBackRenderer->SetupAttachment(Root);
	OnionRenderer->SetupAttachment(Root);
	LeftTearRenderer->SetupAttachment(Root);
	RightTearRenderer->SetupAttachment(Root);
}

AOnion::~AOnion()
{
}

void AOnion::PlayGroundIntroAnimation()
{
	GroundFrontRenderer->ChangeAnimation("ground_front_intro");
	GroundBackRenderer->ChangeAnimation("ground_back_intro");
}

void AOnion::PlayOnionIntroAnimation()
{
	OnionRenderer->ChangeAnimation("onion_intro");
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
	if ("Faint" == StateManager.GetCurStateName() || "Finish" == StateManager.GetCurStateName())
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

	CryingSoundPlayer = UEngineSound::SoundPlay("onion_crying.mp3");
	CryingSoundPlayer.Loop(-1);
	CryingSoundPlayer.Off();

	RendererInit();
	StateInit();

	SetActorLocation({ 0.0f, -315.0f });

	GroundFrontRenderer->SetPosition({ 0.0f, -55.0f });
	GroundBackRenderer->SetPosition({ 0.0f, -25.0f });
	GroundBackRenderer->SetAutoSize(0.0f, true);

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

	GroundFrontRenderer->CreateAnimation("ground_front_intro", "ground_front_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundFrontRenderer->CreateAnimation("ground_front_idle", "ground_front_idle.png", 1 / 12.0f, false);
	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 20, [this]() {
		OnionRenderer->ChangeAnimation("onion_intro");
		Collision->SetActive(true);
		});

	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 27, [this]() {
		GroundFrontRenderer->ChangeAnimation("ground_front_idle");
		});

	GroundBackRenderer->CreateAnimation("ground_back_intro", "ground_back_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundBackRenderer->CreateAnimation("ground_back_idle", "ground_back_idle.png", 1 / 12.0f, false);

	GroundBackRenderer->SetFrameCallback("ground_back_intro", 20, [this]() {
		GroundBackRenderer->SetAutoSize(1.5f, true);
		});

	GroundBackRenderer->SetFrameCallback("ground_back_intro", 27, [this]() {
		GroundBackRenderer->ChangeAnimation("ground_back_idle");
		});

	LeftTearRenderer->CreateAnimation("onion_tear_start", "onion_tear_start.png", 1 / 12.0f, false);
	LeftTearRenderer->CreateAnimation("onion_tear_loop", "onion_tear_loop.png", 1 / 12.0f, true);
	LeftTearRenderer->CreateAnimation("onion_tear_end", "onion_tear_end.png", 1 / 12.0f, false);

	RightTearRenderer->CreateAnimation("onion_tear_start", "onion_tear_start.png", 1 / 12.0f, false);
	RightTearRenderer->CreateAnimation("onion_tear_loop", "onion_tear_loop.png", 1 / 12.0f, true);
	RightTearRenderer->CreateAnimation("onion_tear_end", "onion_tear_end.png", 1 / 12.0f, false);

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

	OnionRenderer->SetOrder(ERenderingOrder::Back6);
	GroundFrontRenderer->SetOrder(ERenderingOrder::Back7);
	GroundBackRenderer->SetOrder(ERenderingOrder::Back5);
	LeftTearRenderer->SetOrder(ERenderingOrder::Back7);
	RightTearRenderer->SetOrder(ERenderingOrder::Back7);

	OnionRenderer->SetPivot(EPivot::BOT);
	GroundFrontRenderer->SetPivot(EPivot::BOT);
	GroundBackRenderer->SetPivot(EPivot::BOT);

	OnionRenderer->SetAutoSize(1.0f, true);
	GroundFrontRenderer->SetAutoSize(1.5f, true);
	GroundBackRenderer->SetAutoSize(1.5f, true);
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
	UEngineSound::SoundPlay("onion_rise.mp3");
}

void AOnion::Idle(float _DeltaTime)
{
}

void AOnion::IdleEnd()
{
}

void AOnion::AttackStart()
{
	CryingSoundPlayer.Replay();
	CryingSoundPlayer.On();

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
	CryingSoundPlayer.Off();
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

	OnionRenderer->SetAutoSize(0.9f, true);
	OnionRenderer->AddPosition(FVector::Down * 10.0f);
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
		if (ShrinkTimer > -1.0f)
		{
			OnionRenderer->AddPosition(FVector::Up * 40.0f * _DeltaTime);
		}

		OnionRenderer->Crop({ 0.0f, 0.0f }, { 1.0f, 1.0f + ShrinkTimer / 3.0f });
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
	GroundFrontRenderer->SetActive(false);
	GroundBackRenderer->SetActive(false);
}