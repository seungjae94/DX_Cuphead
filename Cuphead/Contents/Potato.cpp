#include "PreCompile.h"
#include "Potato.h"
#include "BossAttack.h"

APotato::APotato()
{
	GroundFrontRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundFront");
	GroundBackRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundBack");
	PotatoRenderer = CreateDefaultSubObject<UCropSpriteRenderer>("Potato");

	GroundFrontRenderer->SetupAttachment(Root);
	GroundBackRenderer->SetupAttachment(Root);
	PotatoRenderer->SetupAttachment(Root);
}

APotato::~APotato()
{
}

void APotato::PlayGroundIntroAnimation()
{
	GroundFrontRenderer->ChangeAnimation("ground_front_intro");
	GroundBackRenderer->ChangeAnimation("ground_back_intro");
}

void APotato::PlayPotatoIntroAnimation()
{
	PotatoRenderer->ChangeAnimation("potato_intro");
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

	GroundFrontRenderer->SetPosition({ 0.0f, -80.0f });
	GroundBackRenderer->SetPosition({ 0.0f, -60.0f });
	GroundBackRenderer->SetAutoSize(0.0f, true);

	Collision->SetPosition(PotatoRenderer->GetLocalPosition() + FVector(0.0f, 200.0f, 0.0f));
	Collision->SetScale({ 300.0f, 400.0f });
}

void APotato::LevelStart(ULevel* _PrevLevel)
{
	StateManager.ChangeState("Intro");
}

void APotato::RendererInit()
{
	PotatoRenderer->CreateAnimation("potato_intro", "potato_intro.png", 1 / 12.0f, false);
	PotatoRenderer->CreateAnimation("potato_idle", "potato_idle.png", 1 / 6.0f, true);
	PotatoRenderer->CreateAnimation("potato_attack", "potato_attack.png", 1 / 24.0f, false);
	PotatoRenderer->CreateAnimation("potato_faint", "potato_faint.png",
		std::vector<float>(12, 1 / 12.0f),
		{ 2, 3, 4, 5, 6, 7, 8, 6, 5, 4, 3 }, true);

	GroundFrontRenderer->CreateAnimation("ground_front_intro", "ground_front_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundFrontRenderer->CreateAnimation("ground_front_idle", "ground_front_idle.png", 1 / 12.0f, false);

	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 20, [this]() {
		PotatoRenderer->ChangeAnimation("potato_intro");
	});

	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 27, [this]() {
		GroundFrontRenderer->ChangeAnimation("ground_front_idle");
	});

	GroundBackRenderer->CreateAnimation("ground_back_intro", "ground_back_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundBackRenderer->CreateAnimation("ground_back_idle", "ground_back_idle.png", 1 / 12.0f, false);

	GroundBackRenderer->SetFrameCallback("ground_back_intro", 20, [this]() {
		GroundBackRenderer->SetAutoSize(1.25f, true);
		});

	GroundBackRenderer->SetFrameCallback("ground_back_intro", 27, [this]() {
		GroundBackRenderer->ChangeAnimation("ground_back_idle");
		});

	PotatoRenderer->SetOrder(ERenderingOrder::Back6);
	GroundFrontRenderer->SetOrder(ERenderingOrder::Back7);
	GroundBackRenderer->SetOrder(ERenderingOrder::Back5);

	PotatoRenderer->SetPivot(EPivot::BOT);
	GroundFrontRenderer->SetPivot(EPivot::BOT);
	GroundBackRenderer->SetPivot(EPivot::BOT);

	PotatoRenderer->SetAutoSize(1.25f, true);
	GroundFrontRenderer->SetAutoSize(1.25f, true);
	GroundBackRenderer->SetAutoSize(1.25f, true);
}

void APotato::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("Attack");
	StateManager.CreateState("AttackWait");

	StateManager.SetFunction("Intro",
		std::bind(&APotato::IntroStart, this),
		std::bind(&APotato::Intro, this, std::placeholders::_1),
		std::bind(&APotato::IntroEnd, this)
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
}

void APotato::IntroStart()
{
	UEngineSound::SoundPlay("potato_rise.mp3");
}

void APotato::Intro(float _DeltaTime)
{

}

void APotato::IntroEnd()
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
		UEngineSound::SoundPlay("potato_ball.mp3");
	}
	else
	{
		Attack->SetAnimation("potato_attack_ball", "potato_attack_ball.png", 1 / 12.0f, true);
		UEngineSound::SoundPlay("potato_snake.mp3");
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

	PotatoRenderer->AddPosition(FVector::Up * 20.0f);
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
		PotatoRenderer->Crop({ 0.0f, 0.0f }, {1.0f, 1.0f + ShrinkTimer / 3.0f});
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
	GroundFrontRenderer->SetActive(false);
	GroundBackRenderer->SetActive(false);
}
