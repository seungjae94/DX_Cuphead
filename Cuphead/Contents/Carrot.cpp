#include "PreCompile.h"
#include "Carrot.h"

ACarrot::ACarrot()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	CarrotRenderer = CreateDefaultSubObject<USpriteRenderer>("Carrot");
	Collision = CreateDefaultSubObject<UCollision>("Collision");
	CollisionRenderer = CreateDefaultSubObject<USpriteRenderer>("CollisionRenderer");

	GroundRenderer->SetupAttachment(Root);
	CarrotRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);
	CollisionRenderer->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ACarrot::~ACarrot()
{
}

void ACarrot::BeginPlay()
{
	Super::BeginPlay();

	SetHp(475);

	RendererInit();
	StateInit();

	SetActorLocation({ 0.0f, 0.0f });
	CarrotRenderer->SetPosition({ 0.0f, -50.0f });
	GroundRenderer->SetPosition({ 0.0f, -80.0f });
	Collision->SetPosition(CarrotRenderer->GetLocalPosition() + FVector(0.0f, 200.0f, 0.0f));
	Collision->SetScale({ 300.0f, 400.0f });

	CollisionRenderer->SetPosition(Collision->GetLocalPosition());
	CollisionRenderer->SetScale(Collision->GetLocalScale());
}

void ACarrot::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ACarrot::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Carrot Hp : {}\n", Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Carrot State : {}\n", StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ACarrot::RendererInit()
{
	CarrotRenderer->CreateAnimation("carrot_intro", "carrot_intro.png", 1 / 12.0f, false);
	CarrotRenderer->CreateAnimation("carrot_idle", "carrot_idle.png", 1 / 12.0f, true);
	CarrotRenderer->CreateAnimation("carrot_idle_to_beam", "carrot_idle_to_beam.png", 1 / 12.0f, false);
	CarrotRenderer->CreateAnimation("carrot_beam_body", "carrot_beam_body.png", 1 / 12.0f, true);
	CarrotRenderer->CreateAnimation("carrot_beam_eye", "carrot_beam_eye.png", 1 / 12.0f, true);
	CarrotRenderer->CreateAnimation("carrot_faint", "carrot_faint.png", 1 / 12.0f, true);
	GroundRenderer->CreateAnimation("ground_intro", "carrot_ground_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundRenderer->CreateAnimation("ground_idle", "carrot_ground_idle.png", 1 / 12.0f, false);

	GroundRenderer->SetFrameCallback("ground_intro", 20, [this]() {
		CarrotRenderer->ChangeAnimation("potato_intro");
		});

	GroundRenderer->SetFrameCallback("ground_intro", 27, [this]() {
		GroundRenderer->ChangeAnimation("ground_idle");
		});

	CarrotRenderer->SetOrder(ERenderingOrder::Back5);
	GroundRenderer->SetOrder(ERenderingOrder::Back6);

	CarrotRenderer->SetPivot(EPivot::BOT);
	GroundRenderer->SetPivot(EPivot::BOT);

	CarrotRenderer->SetAutoSize(1.0f, true);
	GroundRenderer->SetAutoSize(1.0f, true);

	CollisionRenderer->SetSprite("debug_rect.png");
	CollisionRenderer->SetOrder(ERenderingOrder::Collider);
	CollisionRenderer->SetActive(false);
}

void ACarrot::StateInit()
{
}

void ACarrot::IdleStart()
{
}

void ACarrot::Idle(float _DeltaTime)
{
}

void ACarrot::IdleEnd()
{
}

void ACarrot::AttackStart()
{
}

void ACarrot::Attack(float _DeltaTime)
{
}

void ACarrot::AttackEnd()
{
}

void ACarrot::AttackWaitStart()
{
}

void ACarrot::AttackWait(float _DeltaTime)
{
}

void ACarrot::AttackWaitEnd()
{
}

void ACarrot::FaintStart()
{
}

void ACarrot::Faint(float _DeltaTime)
{
}

void ACarrot::FaintEnd()
{
}

void ACarrot::FinishStart()
{
}

void ACarrot::Finish(float _DeltaTime)
{
}

void ACarrot::FinishEnd()
{
}

void ACarrot::PlayGroundIntroAnimation()
{
	GroundRenderer->ChangeAnimation("ground_intro");
}

void ACarrot::PlayCarrotIntroAnimation()
{
	CarrotRenderer->ChangeAnimation("carrot_intro");
}

void ACarrot::PlayGroundIdleAnimation()
{
	GroundRenderer->ChangeAnimation("ground_idle");
}

void ACarrot::PlayCarrotIdleAnimation()
{
	CarrotRenderer->ChangeAnimation("carrot_idle");
}

void ACarrot::SetCarrotFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	CarrotRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
}

void ACarrot::StateChangeToAttack()
{
	StateManager.ChangeState("Attack");
}

bool ACarrot::IsFinished()
{
	return "Finish" == StateManager.GetCurStateName();
}

void ACarrot::Damage(int _Damage)
{
	if ("Faint" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	CarrotRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.5f });
	DelayCallBack(0.2f, [this]() {
		CarrotRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("Faint");
	}
}
