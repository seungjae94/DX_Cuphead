#include "PreCompile.h"
#include "Dragon1.h"
#include "BossAttack.h"

ADragon1::ADragon1()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("Body");
	Collision = CreateDefaultSubObject<UCollision>("Collision");

	BodyRenderer->SetupAttachment(Root);
	Collision->SetupAttachment(Root);

	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::RotRect);
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
	Collision->SetPosition(BodyRenderer->GetLocalPosition() + FVector(0.0f, 500.0f, 0.0f));
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
	{
		std::string Msg = std::format("Dragon1 Hp : {}\n", Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Dragon1 State : {}\n", StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
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

	BodyRenderer->SetFrameCallback("dragon1_attack_start", 15, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_attack");
		SpawnAttackProj();
		});

	BodyRenderer->SetFrameCallback("dragon1_attack", 6, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_attack_end");
		});

	BodyRenderer->SetFrameCallback("dragon1_attack_end", 7, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_idle");

		if (0 == AttackCount)
		{
			StateManager.ChangeState("Idle");
		}
		});

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
	StateManager.CreateState("Faint");
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

	AttackDecisionTimer = AttackDecisionTime;
}

void ADragon1::Idle(float _DeltaTime)
{
	AttackDecisionTimer -= _DeltaTime;

	if (AttackDecisionTimer > 0.0f)
	{
		return;
	}

	//int AttackType = Random.RandomInt(0, 1);
	int AttackType = Random.RandomInt(0, 0); // 임시로 빔을 쏘지 않도록 처리

	if (0 == AttackType)
	{
		StateManager.ChangeState("Attack");
	}
	else
	{
		StateManager.ChangeState("Beam");
	}
}

void ADragon1::IdleEnd()
{
}

void ADragon1::AttackStart()
{
	AttackCount = MaxAttackCount;
	AttackTimer = 0.0f;
}

void ADragon1::Attack(float _DeltaTime)
{
	AttackTimer -= _DeltaTime;

	if (AttackTimer > 0.0f)
	{
		return;
	}

	BodyRenderer->ChangeAnimation("dragon1_attack_start");

	--AttackCount;
	AttackTimer = AttackInterval;
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

void ADragon1::SpawnAttackProj()
{
	ABossAttack* Attack = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
	Attack->SetRenderingOrder(ERenderingOrder::Bullet);
	Attack->SetActorLocation(GetActorLocation() + FVector(-150.0f, 675.0f, 0.0f));

	std::function<FVector()> VelocityGenerator = [this, Attack]() {
		float Height = 300.0f;
		float WidthCoeff = 3.0f * UEngineMath::PI / 1280.0f;
		float AttackX = Attack->GetActorLocation().X;
		float Derivative = Height * WidthCoeff * std::cos(WidthCoeff * (AttackX - 315.0f));
		float Angle = std::atan(Derivative);
		Angle *= UEngineMath::RToD;
		Angle += 180.0f;

		Attack->SetActorRotation({ 0.0f, 0.0f, Angle + 180.0f });

		FVector Velocity = FVector::VectorRotationZToDeg(FVector::Right, Angle);

		float AbsAttackY = std::abs(Attack->GetActorLocation().Y);
		float MinSpeed = 200.0f;
		float MaxSpeed = 600.0f;
		float Speed = (360.0f - AbsAttackY) / 360.0f * (MaxSpeed - MinSpeed) + MinSpeed;
		Velocity *= Speed;
		return Velocity;
	};

	Attack->SetVelocityGenerator(VelocityGenerator);
	Attack->SetDestroyTime(5.0f);
	Attack->SetCollisionPosition({ -25.0f, -25.0f });
	Attack->SetCollisionScale({ 100.0f, 100.0f });
	Attack->SetAnimation("dragon1_attack_proj", "dragon1_attack_proj.png", 1 / 24.0f, true);
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
	if ("RunAway" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	BodyRenderer->SetPlusColor({ 1.0f, 1.0f, 1.0f, 0.0f });
	BodyRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.75f });

	DelayCallBack(0.1f, [this]() {
		BodyRenderer->SetMulColor(FVector::One);
		BodyRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("RunAway");
	}
}
