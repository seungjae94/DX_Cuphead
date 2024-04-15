#include "PreCompile.h"
#include "Potato.h"
#include "BossAttack.h"

APotato::APotato()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	PotatoRenderer = CreateDefaultSubObject<USpriteRenderer>("Potato");
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	CollisionRenderer = CreateDefaultSubObject<USpriteRenderer>("CollisionRenderer");

	GroundRenderer->SetupAttachment(Root);
	PotatoRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);
	CollisionRenderer->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
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

void APotato::TransToAttackState()
{
	StateManager.ChangeState("Attack");
}

bool APotato::IsFinished()
{
	return "FINISH" == StateManager.GetCurStateName();;
}

void APotato::Damage(int _Damage)
{
	Hp -= _Damage;

	PotatoRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	DelayCallBack(0.3f, [this]() {
		PotatoRenderer->SetPlusColor(FVector::Zero);
	});
}

void APotato::SetGroundFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	GroundRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
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
	Collision->SetScale({300.0f, 400.0f});

	CollisionRenderer->SetPosition(Collision->GetLocalPosition());
	CollisionRenderer->SetScale(Collision->GetLocalScale());
}

void APotato::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugMsgUpdate(_DeltaTime);
}

void APotato::DebugMsgUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Potato Hp : {}\n", Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Potato State : {}\n", StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Potato AttackWaitTimer : {}\n", AttackWaitTimer);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Potato AttackTimer : {}\n", AttackTimer);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void APotato::RendererInit()
{
	PotatoRenderer->CreateAnimation("potato_intro", "potato_intro.png", 1 / 12.0f, false);
	PotatoRenderer->CreateAnimation("potato_idle", "potato_idle.png", 1 / 6.0f, true);
	PotatoRenderer->CreateAnimation("potato_attack", "potato_attack.png", 1 / 24.0f, false);
	GroundRenderer->CreateAnimation("ground_intro", "potato_ground_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundRenderer->CreateAnimation("ground_idle", "potato_ground_idle.png", 1 / 12.0f, false);

	GroundRenderer->SetFrameCallback("ground_intro", 20, [this]() {
		PotatoRenderer->ChangeAnimation("potato_intro");
		});

	PotatoRenderer->SetOrder(ERenderingOrder::Back5);
	GroundRenderer->SetOrder(ERenderingOrder::Back6);

	PotatoRenderer->SetPivot(EPivot::BOT);
	GroundRenderer->SetPivot(EPivot::BOT);

	PotatoRenderer->SetAutoSize(1.0f, true);
	GroundRenderer->SetAutoSize(1.0f, true);

	CollisionRenderer->SetSprite("debug_rect.png");
	CollisionRenderer->SetOrder(ERenderingOrder::Collider);
	CollisionRenderer->SetAlpha(0.5f);
}

void APotato::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("AttackWait");
	StateManager.CreateState("Faint");
	StateManager.CreateState("Finish");

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

	StateManager.SetFunction("Faint",
		std::bind(&APotato::FaintStart, this),
		std::bind(&APotato::Faint, this, std::placeholders::_1),
		std::bind(&APotato::FaintEnd, this)
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

	++AttackCount;

	PotatoRenderer->ChangeAnimation("potato_attack");
	if (MaxAttackCount == AttackCount)
	{
		Attack->SetAnimation("potato_attack_snake", "potato_attack_snake.png", 1 / 12.0f, true);
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
}

void APotato::Faint(float _DeltaTime)
{
}

void APotato::FaintEnd()
{
}
