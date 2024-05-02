#include "PreCompile.h"
#include "Dragon1.h"
#include "BossAttack.h"
#include "Player.h"
#include "AnimationEffect.h"

ADragon1::ADragon1()
{
	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("Body");
	BodyRenderer->SetupAttachment(Root);
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

	SetActorLocation({ 500.0f, -475.0f });
	BodyRenderer->SetPosition({ 0.0f, 0.0f });
	Collision->SetPosition(BodyRenderer->GetLocalPosition() + FVector(0.0f, 500.0f, 0.0f));
	Collision->SetScale({ 300.0f, 500.0f });
}

void ADragon1::RendererInit()
{
	BodyRenderer->CreateAnimation("dragon1_intro", "dragon1_intro", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_idle", "dragon1_idle.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_tail", "dragon1_tail.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_attack", "dragon1_attack.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_attack_start", "dragon1_attack_start.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_attack_end", "dragon1_attack_end.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_beam", "dragon1_beam.png", 1 / 24.0f, true);
	BodyRenderer->CreateAnimation("dragon1_beam_start", "dragon1_beam_start.png", 1 / 24.0f, false);
	BodyRenderer->CreateAnimation("dragon1_beam_end", "dragon1_beam_end.png", 1 / 24.0f, false);

	BodyRenderer->SetFrameCallback("dragon1_intro", 39, [this]() {

		});

	BodyRenderer->SetFrameCallback("dragon1_attack_start", 15, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_attack");
		SpawnAttackProj();
		});

	BodyRenderer->SetFrameCallback("dragon1_attack", 6, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_attack_end");
		});

	BodyRenderer->SetFrameCallback("dragon1_attack_end", 7, [this]() {
		if ("RunAway" == StateManager.GetCurStateName())
		{
			return;
		}

		BodyRenderer->ChangeAnimation("dragon1_idle");

		if (0 == AttackCount)
		{
			StateManager.ChangeState("Idle");
		}
		});

	BodyRenderer->SetFrameCallback("dragon1_beam_start", 7, [this]() {
		BodyRenderer->ChangeAnimation("dragon1_beam");
		SpawnBeamProj();
		});

	BodyRenderer->SetFrameCallback("dragon1_beam_end", 7, [this]() {
		if ("RunAway" == StateManager.GetCurStateName())
		{
			return;
		}

		StateManager.ChangeState("Idle");
		});

	BodyRenderer->SetOrder(ERenderingOrder::Back6);
	BodyRenderer->SetPivot(EPivot::BOT);
	BodyRenderer->SetAutoSize(1.0f, true);
}

void ADragon1::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("Beam");
	StateManager.CreateState("RunAway");

	StateManager.SetFunction("Intro",
		std::bind(&ADragon1::IntroStart, this),
		std::bind(&ADragon1::Intro, this, std::placeholders::_1),
		std::bind(&ADragon1::IntroEnd, this)
	);

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

	StateManager.ChangeState("Intro");
}

void ADragon1::IntroStart()
{
}

void ADragon1::Intro(float _DeltaTime)
{
}

void ADragon1::IntroEnd()
{
}

void ADragon1::IdleStart()
{
	AttackDecisionTimer = AttackDecisionTime;
	BodyRenderer->ChangeAnimation("dragon1_idle");
}

void ADragon1::Idle(float _DeltaTime)
{
	AttackDecisionTimer -= _DeltaTime;

	if (AttackDecisionTimer > 0.0f)
	{
		return;
	}

	int AttackType = Random.RandomInt(0, 1);

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
	UEngineSound::SoundPlay("dragon_beam_start.mp3");
	BodyRenderer->ChangeAnimation("dragon1_beam_start");
}

void ADragon1::Beam(float _DeltaTime)
{

}

void ADragon1::BeamEnd()
{
	if ("RunAway" != StateManager.GetCurStateName())
	{
		UEngineSound::SoundPlay("dragon_beam_end.mp3");
	}
}

void ADragon1::RunAwayStart()
{
}

void ADragon1::RunAway(float _DeltaTime)
{
	AddActorLocation(FVector::Right * 300.0f * _DeltaTime);

	float PosX = GetActorLocation().X;

	if (PosX > 1000.0f)
	{
		StateManager.ChangeState("Finish");
	}
}

void ADragon1::RunAwayEnd()
{
}

void ADragon1::SpawnAttackProj()
{
	ABossAttack* Attack = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
	Attack->SetRenderingOrder(ERenderingOrder::Bullet);
	Attack->SetActorLocation(GetActorLocation() + FVector(-150.0f, 675.0f, 0.0f));
	Attack->SetTrailEffect(FCreateAnimationParameter{"dragon1_attack_smoke", "dragon1_attack_smoke.png", 1 / 24.0f}, 1 / 6.0f);

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

void ADragon1::SpawnBeamProj()
{
	FVector PlayerPos = Player->GetActorLocation();

	for (int i = 0; i < 3; ++i)
	{
		DelayCallBack(1.0f + 0.2f * i, [this, PlayerPos, i]() {
			ABossAttack* Beam = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
			Beam->SetRenderingOrder(ERenderingOrder::Bullet);
			Beam->SetActorLocation(GetActorLocation() + FVector(-100.0f, 750.0f, 0.0f));

			FVector Direction = (PlayerPos - Beam->GetActorLocation()).Normalize3DReturn();
			Beam->SetVelocity(Direction * 600.0f);

			float Deg = UCupheadMath::DirectionToDeg(Direction);
			Beam->SetActorRotation({ 0.0f, 0.0f, Deg + 180.0f });

			Beam->SetDestroyTime(5.0f);
			Beam->SetCollisionPosition({ -25.0f, -25.0f });
			Beam->SetCollisionScale({ 100.0f, 100.0f });

			if (i == 2)
			{
				Beam->SetAnimation("dragon1_beam_proj_pink", "dragon1_beam_proj_pink.png", 1 / 24.0f, true);
				Beam->SetParryable(true);
				BodyRenderer->ChangeAnimation("dragon1_beam_end");
			}
			else
			{
				Beam->SetAnimation("dragon1_beam_proj", "dragon1_beam_proj.png", 1 / 24.0f, true);
			}

			UEngineSound::SoundPlay("dragon_beam_" + std::to_string(i) + ".mp3");

			});
	}
}

void ADragon1::PlayIntroAnimation()
{
	BodyRenderer->ChangeAnimation("dragon1_intro");
}

void ADragon1::ChangeAnimation(std::string_view _AnimName)
{
	BodyRenderer->ChangeAnimation(_AnimName);
}

void ADragon1::SetState(std::string_view _StateName)
{
	StateManager.ChangeState(_StateName);
}

void ADragon1::SetFrameCallback(std::string_view _AnimName, int _Frame, std::function<void()> _Callback)
{
	BodyRenderer->SetFrameCallback(_AnimName, _Frame, _Callback);
}

void ADragon1::SetLastFrameCallback(std::string_view _AnimName, std::function<void()> _Callback)
{
	BodyRenderer->SetLastFrameCallback(_AnimName, _Callback);
}

void ADragon1::Damage(int _Damage)
{
	if ("RunAway" == StateManager.GetCurStateName() || "Finish" == StateManager.GetCurStateName())
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

void ADragon1::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}
