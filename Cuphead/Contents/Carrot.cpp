#include "PreCompile.h"
#include "Carrot.h"
#include "BossAttack.h"
#include "CarrotBeam.h"
#include "Player.h"

ACarrot::ACarrot()
{
	GroundFrontRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundFront");
	GroundBackRenderer = CreateDefaultSubObject<USpriteRenderer>("GroundBack");
	CarrotRenderer = CreateDefaultSubObject<USpriteRenderer>("Carrot");
	EyeRenderer = CreateDefaultSubObject<USpriteRenderer>("Eye");

	GroundFrontRenderer->SetupAttachment(Root);
	GroundBackRenderer->SetupAttachment(Root);
	CarrotRenderer->SetupAttachment(Root);
	EyeRenderer->SetupAttachment(Root);
}

ACarrot::~ACarrot()
{
}

void ACarrot::BeginPlay()
{
	Super::BeginPlay();

	SetHp(475);

	CarrotAttackLoopSoundPlayer = UEngineSound::SoundPlay("carrot_attack_loop.mp3");
	CarrotAttackLoopSoundPlayer.Loop(-1);
	CarrotAttackLoopSoundPlayer.Off();

	RendererInit();
	StateInit();

	SetActorLocation({ 0.0f, -270.0f });
	CarrotRenderer->SetPosition({ 0.0f, 0.0f });
	EyeRenderer->SetPosition({ -2.0f, 310.0f });
	GroundFrontRenderer->SetPosition({ 0.0f, 0.0f });
	GroundBackRenderer->SetPosition({ 0.0f, 0.0f });
	Collision->SetPosition(CarrotRenderer->GetLocalPosition() + FVector(0.0f, 400.0f, 0.0f));
	Collision->SetScale({ 250.0f, 300.0f });

	BodyDamageOff();
}

void ACarrot::RendererInit()
{
	CarrotRenderer->CreateAnimation("carrot_intro", "carrot_intro", 1 / 12.0f, false);
	CarrotRenderer->CreateAnimation("carrot_idle", "carrot_idle.png", 1 / 18.0f, true);
	CarrotRenderer->CreateAnimation("carrot_idle_to_beam", "carrot_idle_to_beam.png", 1 / 12.0f, false);
	CarrotRenderer->CreateAnimation("carrot_beam_body", "carrot_beam_body.png", 1 / 12.0f, true);
	CarrotRenderer->CreateAnimation("carrot_beam_eye", "carrot_beam_eye.png", 1 / 12.0f, true);
	CarrotRenderer->CreateAnimation("carrot_faint", "carrot_faint.png", 1 / 12.0f, true);

	EyeRenderer->CreateAnimation("carrot_beam_eye", "carrot_beam_eye.png", 1 / 12.0f, true);

	GroundFrontRenderer->CreateAnimation("ground_front_intro", "ground_front_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundFrontRenderer->CreateAnimation("ground_front_idle", "ground_front_idle.png", 1 / 12.0f, false);

	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 20, [this]() {
		CarrotRenderer->ChangeAnimation("carrot_intro");
		});

	GroundFrontRenderer->SetFrameCallback("ground_front_intro", 27, [this]() {
		GroundFrontRenderer->ChangeAnimation("ground_front_idle");
		});

	GroundBackRenderer->CreateAnimation("ground_back_intro", "ground_back_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);
	GroundBackRenderer->CreateAnimation("ground_back_idle", "ground_back_idle.png", 1 / 12.0f, false);

	GroundBackRenderer->SetFrameCallback("ground_back_intro", 27, [this]() {
		GroundBackRenderer->ChangeAnimation("ground_back_idle");
		});

	CarrotRenderer->SetFrameCallback("carrot_idle_to_beam", 8, [this]() {
		if ("Faint" == StateManager.GetCurStateName())
		{
			return;
		}

		CarrotRenderer->ChangeAnimation("carrot_beam_body");
		EyeRenderer->ChangeAnimation("carrot_beam_eye");
		EyeRenderer->SetActive(true);
		});

	CarrotRenderer->SetOrder(ERenderingOrder::Back3);
	EyeRenderer->SetOrder(ERenderingOrder::Back4);
	GroundFrontRenderer->SetOrder(ERenderingOrder::Back4);
	GroundBackRenderer->SetOrder(ERenderingOrder::Back2);

	CarrotRenderer->SetPivot(EPivot::BOT);
	EyeRenderer->SetPivot(EPivot::BOT);
	GroundFrontRenderer->SetPivot(EPivot::BOT);
	GroundBackRenderer->SetPivot(EPivot::BOT);

	CarrotRenderer->SetAutoSize(1.2f, true);
	EyeRenderer->SetAutoSize(1.2f, true);
	GroundFrontRenderer->SetAutoSize(1.2f, true);
	GroundBackRenderer->SetAutoSize(1.2f, true);

	EyeRenderer->SetActive(false);
}

void ACarrot::StateInit()
{
	StateManager.CreateState("Idle");
	StateManager.CreateState("Attack");
	StateManager.CreateState("Beam");

	StateManager.SetFunction("Idle",
		std::bind(&ACarrot::IdleStart, this),
		std::bind(&ACarrot::Idle, this, std::placeholders::_1),
		std::bind(&ACarrot::IdleEnd, this)
	);

	StateManager.SetFunction("Attack",
		std::bind(&ACarrot::AttackStart, this),
		std::bind(&ACarrot::Attack, this, std::placeholders::_1),
		std::bind(&ACarrot::AttackEnd, this)
	);

	StateManager.SetFunction("Beam",
		std::bind(&ACarrot::BeamStart, this),
		std::bind(&ACarrot::Beam, this, std::placeholders::_1),
		std::bind(&ACarrot::BeamEnd, this)
	);

	StateManager.ChangeState("Idle");
}

void ACarrot::IdleStart()
{
	UEngineSound::SoundPlay("carrot_rise.mp3");
}

void ACarrot::Idle(float _DeltaTime)
{
}

void ACarrot::IdleEnd()
{
}

void ACarrot::AttackStart()
{
	CarrotAttackLoopSoundPlayer.Replay();
	CarrotAttackLoopSoundPlayer.On();

	CarrotRenderer->ChangeAnimation("carrot_idle");
	EyeRenderer->SetActive(false);

	AttackCount = MaxAttackCount;
	AttackTimer = AttackInterval;
}

void ACarrot::Attack(float _DeltaTime)
{
	AttackTimer -= _DeltaTime;

	if (AttackTimer >= 0.0f)
	{
		return;
	}

	ABossAttack* Proj = GetWorld()->SpawnActor<ABossAttack>("Attack").get();
	Proj->SetRenderingOrder(ERenderingOrder::Bullet);

	float RandomX = Random.RandomFloat(-640.0f, 640.0f);

	Proj->SetActorLocation({ RandomX, 400.0f, 0.0f });
	Proj->SetVelocity(FVector::Down * 200.0f);
	Proj->SetAnimation("carrot_proj", "carrot_proj.png", 1 / 12.0f, true);
	Proj->SetChaseType(EChaseType::Permanent, Player);
	Proj->SetChaseTime(5.0f);
	Proj->SetDestroyTime(10.0f);

	int RandomInt = Random.RandomInt(1, 4);
	Proj->SetDestroySound("carrot_proj_explode_" + std::to_string(RandomInt) + ".mp3");
	Proj->SetDestroyable(true, "carrot_proj_destroy", "carrot_proj_destroy.png", 1 / 12.0f);
	Proj->SetCollisionPosition({ -2.0f, -10.0f });
	Proj->SetCollisionScale({ 30.0f, 70.0f });

	--AttackCount;
	AttackTimer = AttackInterval;

	if (AttackCount <= 0)
	{
		StateManager.ChangeState("Beam");
		return;
	}
}


void ACarrot::AttackEnd()
{
	CarrotAttackLoopSoundPlayer.Off();
}

void ACarrot::BeamStart()
{
	CarrotRenderer->ChangeAnimation("carrot_idle_to_beam");

	BeamCount = MaxBeamCount;
	BeamTimer = BeamInterval;
}

void ACarrot::Beam(float _DeltaTime)
{
	if (0 == BeamCount)
	{
		return;
	}

	BeamTimer -= _DeltaTime;

	if (BeamTimer >= 0.0f)
	{
		return;
	}

	FVector BeamSpawnPosition = GetActorLocation() + FVector(-3.0f, 425.0f, 0.0f);
	FVector Direction = (Player->GetActorLocation() - BeamSpawnPosition).Normalize2DReturn();
	float Theta = UCupheadMath::DirectionToDeg(Direction);

	for (int i = 0; i < 5; ++i)
	{
		DelayCallBack(0.1f * i, [this, BeamSpawnPosition, Theta, Direction]() {
			ACarrotBeam* Beam = GetWorld()->SpawnActor<ACarrotBeam>("Beam").get();
			Beam->SetRenderingOrder(ERenderingOrder::Bullet);
			Beam->SetActorLocation(BeamSpawnPosition);

			Beam->SetActorRotation({ 0.0f, 0.0f, Theta + 90.0f });
			Beam->SetVelocity(Direction * 650.0f);
			Beam->SetDestroyTime(4.0f);
			Beam->SetCollisionPosition({ 0.0f, 0.0f });
			Beam->SetCollisionScale({ 50.0f, 50.0f });
			Beam->SetAnimation("carrot_beam_proj", "carrot_beam_proj.png", 1 / 12.0f, false);

			UEngineSound::SoundPlay("carrot_beam.mp3");
			});
	}

	--BeamCount;
	BeamTimer = BeamInterval;

	if (0 == BeamCount)
	{
		DelayCallBack(1.0f, [this]() {
			StateManager.ChangeState("Attack");
			});
	}
}

void ACarrot::BeamEnd()
{
}

void ACarrot::FaintStart()
{
	Super::FaintStart();
	SetFaintRange({ -100.0f, 100.0f, 0.0f, 400.0f });

	CarrotRenderer->ChangeAnimation("carrot_faint");
	EyeRenderer->SetActive(false);
	Collision->SetActive(false);

	ShrinkTimer = ShrinkWaitTime;
}

void ACarrot::Faint(float _DeltaTime)
{
	Super::Faint(_DeltaTime);

	ShrinkTimer -= _DeltaTime;

	if (ShrinkTimer < 0.0f)
	{
		CarrotRenderer->AddPosition(FVector::Down * 200.0f * _DeltaTime);
	}

	if (ShrinkTimer < -3.0f)
	{
		StateManager.ChangeState(GStateName::Finish);
	}
}

void ACarrot::FaintEnd()
{
	Super::FaintEnd();

	CarrotRenderer->SetActive(false);
	GroundFrontRenderer->SetActive(false);
	GroundBackRenderer->SetActive(false);
}

void ACarrot::PlayGroundIntroAnimation()
{
	GroundFrontRenderer->ChangeAnimation("ground_front_intro");
	GroundBackRenderer->ChangeAnimation("ground_back_intro");
}

void ACarrot::PlayCarrotIntroAnimation()
{
	CarrotRenderer->ChangeAnimation("carrot_intro");
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

void ACarrot::Damage(int _Damage)
{
	if ("Faint" == StateManager.GetCurStateName() || "Finish" == StateManager.GetCurStateName())
	{
		return;
	}

	Hp -= _Damage;

	CarrotRenderer->SetPlusColor(HitPlusColor);
	EyeRenderer->SetPlusColor(HitPlusColor);


	DelayCallBack(0.1f, [this]() {
		CarrotRenderer->SetPlusColor(FVector::Zero);
		EyeRenderer->SetPlusColor(FVector::Zero);
		});

	if (Hp <= 0.0f)
	{
		StateManager.ChangeState("Faint");
	}
}

void ACarrot::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}
