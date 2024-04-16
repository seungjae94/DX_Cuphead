#include "PreCompile.h"
#include "Onion.h"

AOnion::AOnion()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	OnionRenderer = CreateDefaultSubObject<USpriteRenderer>("Onion");
	LeftTearRenderer = CreateDefaultSubObject<USpriteRenderer>("LeftTear");
	RightTearRenderer = CreateDefaultSubObject<USpriteRenderer>("RightTear");
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	CollisionRenderer = CreateDefaultSubObject<USpriteRenderer>("CollisionRenderer");

	GroundRenderer->SetupAttachment(Root);
	OnionRenderer->SetupAttachment(Root);
	LeftTearRenderer->SetupAttachment(Root);
	RightTearRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);
	CollisionRenderer->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AOnion::~AOnion()
{
}

void AOnion::SetCollisionActive(bool _Active)
{
	Collision->SetActive(_Active);
	CollisionRenderer->SetActive(_Active);
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

	OnionRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	DelayCallBack(0.2f, [this]() {
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

	SetActorLocation({0.0f, -335.0f});

	GroundRenderer->SetPosition({ 0.0f, -35.0f });
	LeftTearRenderer->SetPosition({-350.0f, 555.0f});
	RightTearRenderer->SetPosition({330.0f, 555.0f});

	Collision->SetPosition(OnionRenderer->GetLocalPosition() + FVector(0.0f, 250.0f, 0.0f));
	Collision->SetScale({ 600.0f, 500.0f });
	Collision->SetActive(false);

	CollisionRenderer->SetPosition(Collision->GetLocalPosition());
	CollisionRenderer->SetScale(Collision->GetLocalScale());
	CollisionRenderer->SetActive(false);
}

void AOnion::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void AOnion::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Onion Hp : {}\n", Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AOnion::RendererInit()
{
	OnionRenderer->CreateAnimation("onion_intro", "onion_intro.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_idle", "onion_idle.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_cry_intro", "onion_cry_intro.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_cry_start", "onion_cry_start.png", 1 / 12.0f, false);
	OnionRenderer->CreateAnimation("onion_cry_loop", "onion_cry_loop.png", 1 / 12.0f, true);
	
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
		CollisionRenderer->SetActive(true);
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

	CollisionRenderer->SetSprite("debug_rect.png");
	CollisionRenderer->SetOrder(ERenderingOrder::Collider);
}

void AOnion::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("AttackWait");
	StateManager.CreateState("Faint");
	StateManager.CreateState("Finish");

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

	StateManager.SetFunction("Faint",
		std::bind(&AOnion::FaintStart, this),
		std::bind(&AOnion::Faint, this, std::placeholders::_1),
		std::bind(&AOnion::FaintEnd, this)
	);

	StateManager.SetFunction("Finish",
		std::bind(&AOnion::FinishStart, this),
		std::bind(&AOnion::Finish, this, std::placeholders::_1),
		std::bind(&AOnion::FinishEnd, this)
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
}

void AOnion::Attack(float _DeltaTime)
{
}

void AOnion::AttackEnd()
{
}

void AOnion::AttackWaitStart()
{
}

void AOnion::AttackWait(float _DeltaTime)
{
}

void AOnion::AttackWaitEnd()
{
}

void AOnion::FaintStart()
{
}

void AOnion::Faint(float _DeltaTime)
{
}

void AOnion::FaintEnd()
{
}

void AOnion::FinishStart()
{
}

void AOnion::Finish(float _DeltaTime)
{
}

void AOnion::FinishEnd()
{
}
