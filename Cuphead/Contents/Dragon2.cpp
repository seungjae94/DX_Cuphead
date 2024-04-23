#include "PreCompile.h"
#include "Dragon2.h"
#include "FireMob.h"
#include "AnimationEffect.h"

ADragon2::ADragon2()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	DashRenderer = CreateDefaultSubObject<USpriteRenderer>("Dash");
	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("Body");
	TongueRenderer = CreateDefaultSubObject<USpriteRenderer>("Tongue");
	FireRenderer = CreateDefaultSubObject<USpriteRenderer>("Fire");
	Collision = CreateDefaultSubObject<UCollision>("Collision");

	DashRenderer->SetupAttachment(Root);
	BodyRenderer->SetupAttachment(Root);
	FireRenderer->SetupAttachment(Root);
	TongueRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

ADragon2::~ADragon2()
{
}

void ADragon2::BeginPlay()
{
	Super::BeginPlay();

	SetHp(510);

	RendererInit();
	StateInit();

	SetActorLocation({ -1075.0f, -350.0f });
	DashRenderer->SetPosition({ 1500.0f, 450.0f });
	BodyRenderer->SetPosition(FVector::Zero);
	TongueRenderer->SetPosition({ 184.0f, 16.0f });

	Collision->SetPosition(BodyRenderer->GetLocalPosition() + FVector(0.0f, 275.0f, 0.0f));
	Collision->SetScale({ 200.0f, 450.0f });
}

void ADragon2::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ADragon2::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Dragon2 Hp : {}\n", Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Dragon2 State : {}\n", StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Dragon2 Body Pos : {}\n", BodyRenderer->GetWorldPosition().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ADragon2::RendererInit()
{
	DashRenderer->CreateAnimation("dragon2_dash", "dragon2_dash", 1 / 24.0f, true);

	BodyRenderer->CreateAnimation("dragon2_intro", "dragon2_intro", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon2_idle", "dragon2_idle.png", 1 / 18.0f, true);
	BodyRenderer->CreateAnimation("dragon2_faint", "dragon2_faint", 1 / 24.0f, true);

	TongueRenderer->CreateAnimation("dragon2_tongue_intro", "dragon2_tongue_intro", 1 / 24.0f, false);
	TongueRenderer->CreateAnimation("dragon2_tongue_idle", "dragon2_tongue_idle", 1 / 12.0f, true);

	FireRenderer->CreateAnimation("dragon2_fire", "dragon2_fire", 1 / 24.0f, false);
	FireRenderer->CreateAnimation("dragon2_smoke", "dragon2_smoke.png", 1 / 24.0f, false);

	TongueRenderer->SetFrameCallback("dragon2_tongue_intro", 3, [this]() {
		TongueRenderer->ChangeAnimation("dragon2_tongue_idle");
		});

	DashRenderer->SetOrder(ERenderingOrder::Back2);
	DashRenderer->SetAutoSize(1.0f, true);

	BodyRenderer->SetOrder(ERenderingOrder::Back5);
	BodyRenderer->SetPivot(EPivot::BOT);
	BodyRenderer->SetAutoSize(1.0f, true);

	TongueRenderer->SetOrder(ERenderingOrder::Back6);
	TongueRenderer->SetPivot(EPivot::LEFTBOTTOM);
	TongueRenderer->SetAutoSize(1.0f, true);

	FireRenderer->SetOrder(ERenderingOrder::Back6);
	FireRenderer->SetPivot(EPivot::BOT);
	FireRenderer->SetAutoSize(1.0f, true);
}

void ADragon2::StateInit()
{
	StateManager.CreateState("Dash");
	StateManager.CreateState("Intro");
	StateManager.CreateState("Idle");
	StateManager.CreateState("Faint");
	StateManager.CreateState("Finish");

	StateManager.SetFunction("Dash",
		std::bind(&ADragon2::DashStart, this),
		std::bind(&ADragon2::Dash, this, std::placeholders::_1),
		std::bind(&ADragon2::DashEnd, this)
	);

	StateManager.SetFunction("Intro",
		std::bind(&ADragon2::IntroStart, this),
		std::bind(&ADragon2::Intro, this, std::placeholders::_1),
		std::bind(&ADragon2::IntroEnd, this)
	);

	StateManager.SetFunction("Idle",
		std::bind(&ADragon2::IdleStart, this),
		std::bind(&ADragon2::Idle, this, std::placeholders::_1),
		std::bind(&ADragon2::IdleEnd, this)
	);

	StateManager.SetFunction("Faint",
		std::bind(&ADragon2::FaintStart, this),
		std::bind(&ADragon2::Faint, this, std::placeholders::_1),
		std::bind(&ADragon2::FaintEnd, this)
	);

	StateManager.SetFunction("Finish",
		std::bind(&ADragon2::FinishStart, this),
		std::bind(&ADragon2::Finish, this, std::placeholders::_1),
		std::bind(&ADragon2::FinishEnd, this)
	);

	StateManager.ChangeState("Dash");
}

void ADragon2::DashStart()
{
	BodyRenderer->SetActive(false);
	TongueRenderer->SetActive(false);
	DashRenderer->ChangeAnimation("dragon2_dash");
}

void ADragon2::Dash(float _DeltaTime)
{
	DashRenderer->AddPosition(FVector::Left * 750.0f * _DeltaTime);

	float DashPosX = DashRenderer->GetWorldPosition().X;

	if (DashPosX < -1000.0f)
	{
		StateManager.ChangeState("Intro");
	}
}

void ADragon2::DashEnd()
{
	DashRenderer->SetActive(false);
}

void ADragon2::IntroStart()
{
	BodyRenderer->SetActive(true);
	BodyRenderer->ChangeAnimation("dragon2_intro");

	IntroMoveTimer = IntroMoveTime;
}

void ADragon2::Intro(float _DeltaTime)
{
	IntroMoveTimer -= _DeltaTime;

	if (IntroMoveTimer > 0.0f)
	{
		AddActorLocation(FVector::Right * 1000.0f * _DeltaTime);
	}
}

void ADragon2::IntroEnd()
{
}

void ADragon2::IdleStart()
{
	TongueRenderer->SetActive(true);
	TongueRenderer->ChangeAnimation("dragon2_tongue_intro");
	BodyRenderer->ChangeAnimation("dragon2_idle");

	FireTimer = FireTime;
	SpawnTimer = SpawnTime;

	JumperCounter = 0;

	FireRenderer->SetActive(false);
}

void ADragon2::Idle(float _DeltaTime)
{
	// ºÒ»Õ±â
	FireTimer -= _DeltaTime;
	if (true == FireRenderer->IsActive() && true == FireRenderer->IsCurAnimationEnd())
	{
		FireAnimation = false;
		FireRenderer->SetActive(false);
		FireRenderer->AnimationReset();
	}
	if (FireTimer < 0.0f)
	{
		FireRenderer->SetActive(true);

		int RandomInt = Random.RandomInt(0, 1);

		if (0 == RandomInt)
		{
			FireRenderer->SetPosition({ 192.0f, 253.0f });
			FireRenderer->ChangeAnimation("dragon2_fire");
		}
		else
		{
			FireRenderer->SetPosition({ 212.0f, 257.0f });
			FireRenderer->ChangeAnimation("dragon2_smoke");
		}

		FireTimer = FireTime;
	}

	// ºÒ¸÷ ¼ÒÈ¯
	SpawnTimer -= _DeltaTime;
	if (SpawnTimer < 0.0f)
	{
		AFireMob* FireMob = GetWorld()->SpawnActor<AFireMob>("FireMob").get();
		FireMob->SetActorLocation(GetActorLocation() + FVector{ 280.0f, 125.0f, 0.0f });
		FireMob->SetPlayer(this);

		--JumperCounter;
		if (0 == JumperCounter % JumperPeriod)
		{
			DelayCallBack(1.0f, [FireMob]() {
				FireMob->StateChange("Jump");
				});
		}

		SpawnTimer = SpawnTime;
	}
}

void ADragon2::IdleEnd()
{
}

void ADragon2::FaintStart()
{
	BodyRenderer->AddPosition({ -35.0f, -100.0f });
	BodyRenderer->ChangeAnimation("dragon2_faint");

	BossExplosionTimer = 0.0f;
	FaintTimer = FaintTime;

	FaintActive = false;
}

void ADragon2::Faint(float _DeltaTime)
{
	if (false == FaintActive)
	{
		return;
	}

	FaintTimer -= _DeltaTime;
	BossExplosionTimer -= _DeltaTime;

	if (FaintTimer < 0.0f)
	{
		StateManager.ChangeState("Finish");
	}

	if (BossExplosionTimer < 0.0f)
	{
		AAnimationEffect* Explosion = GetWorld()->SpawnActor<AAnimationEffect>("Explosion").get();
		Explosion->Init(ERenderingOrder::Collider, FCreateAnimationParameter{ "boss_explosion", "boss_explosion", 1 / 24.0f }, true);

		float PosX = Random.RandomFloat(-100.0f, 100.0f);
		float PosY = Random.RandomFloat(0.0f, 400.0f);
		Explosion->SetActorLocation(GetActorLocation() + FVector{PosX, PosY});

		BossExplosionTimer = BossExplosionInterval;
	}
}

void ADragon2::FaintEnd()
{
}

void ADragon2::FinishStart()
{
}

void ADragon2::Finish(float _DeltaTime)
{
}

void ADragon2::FinishEnd()
{
}

void ADragon2::Damage(int _Damage)
{
	if ("Faint" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	BodyRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	BodyRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });
	TongueRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	TongueRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	DelayCallBack(0.1f, [this]() {
		BodyRenderer->SetMulColor(FVector::One);
		BodyRenderer->SetPlusColor(FVector::Zero);
		TongueRenderer->SetMulColor(FVector::One);
		TongueRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("Faint");
	}
}

void ADragon2::ResumeFaint()
{
	FaintActive = true;
}

void ADragon2::ChangeState(std::string_view _StateName)
{
	StateManager.ChangeState(_StateName);
}

void ADragon2::SetFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	BodyRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
}

bool ADragon2::IsFaint()
{
	return "Faint" == StateManager.GetCurStateName();
}

bool ADragon2::IsFinished()
{
	return "Finish" == StateManager.GetCurStateName();
}
