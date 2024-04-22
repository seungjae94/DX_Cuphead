#include "PreCompile.h"
#include "FireMob.h"

AFireMob::AFireMob()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

AFireMob::~AFireMob()
{
}

void AFireMob::SetPlayer(AActor* _Player)
{
	Player = _Player;
}

void AFireMob::StateChange(std::string_view _StateName)
{
	StateManager.ChangeState(_StateName);
}

void AFireMob::BeginPlay()
{
	Super::BeginPlay();

	RendererInit();
	StateInit();

	Collision->SetPosition({0.0f, -40.0f, 0.0f});
	Collision->SetScale({ 50.0f, 50.0f, 1.0f });
}

void AFireMob::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);

	if (GetActorLocation().X > 1500.0f)
	{
		Destroy();
	}
}

void AFireMob::RendererInit()
{
	Renderer->CreateAnimation("firemob_jump", "firemob_jump.png", 1 / 24.0f, false);
	Renderer->CreateAnimation("firemob_jump_ready_start", "firemob_jump_ready_start.png", 1 / 24.0f, false);
	Renderer->CreateAnimation("firemob_jump_ready", "firemob_jump_ready.png", 1 / 24.0f, false);
	Renderer->CreateAnimation("firemob_run", "firemob_run.png", 1 / 24.0f, true);
	Renderer->CreateAnimation("firemob_air", "firemob_air.png", 1 / 24.0f, true);

	Renderer->SetFrameCallback("firemob_jump_ready_start", 4, [this]() {
		Renderer->ChangeAnimation("firemob_jump_ready");
		});

	Renderer->SetFrameCallback("firemob_jump_ready", 4, [this]() {
		StateManager.ChangeState("Air");
		});

	Renderer->SetFrameCallback("firemob_jump", 3, [this]() {
		Renderer->ChangeAnimation("firemob_air");
		});

	Renderer->SetOrder(ERenderingOrder::Back7);
	Renderer->SetAutoSize(1.0f, true);
}

void AFireMob::StateInit()
{
	StateManager.CreateState("Run");
	StateManager.CreateState("Jump");
	StateManager.CreateState("Air");

	StateManager.SetFunction("Run",
		std::bind(&AFireMob::RunStart, this),
		std::bind(&AFireMob::Run, this, std::placeholders::_1),
		std::bind(&AFireMob::RunEnd, this)
	);

	StateManager.SetFunction("Jump",
		std::bind(&AFireMob::JumpStart, this),
		std::bind(&AFireMob::Jump, this, std::placeholders::_1),
		std::bind(&AFireMob::JumpEnd, this)
	);

	StateManager.SetFunction("Air",
		std::bind(&AFireMob::AirStart, this),
		std::bind(&AFireMob::Air, this, std::placeholders::_1),
		std::bind(&AFireMob::AirEnd, this)
	);

	StateManager.ChangeState("Run");
}

void AFireMob::RunStart()
{
	Renderer->ChangeAnimation("firemob_run");
}

void AFireMob::Run(float _DeltaTime)
{
	AddActorLocation(FVector::Right * 300.0f * _DeltaTime);
}

void AFireMob::RunEnd()
{
}

void AFireMob::JumpStart()
{
	Renderer->ChangeAnimation("firemob_jump_ready_start");
}

void AFireMob::Jump(float _DeltaTime)
{
}

void AFireMob::JumpEnd()
{
}

void AFireMob::AirStart()
{
	Renderer->ChangeAnimation("firemob_jump");
	Renderer->SetOrder(ERenderingOrder::Back4);

	FVector Direction = Player->GetActorLocation() - GetActorLocation();

	if (Direction.X < 0.0f)
	{
		Renderer->SetDir(EEngineDir::Left);
		Velocity = {-300.0f, 1000.0f, 0.0f};
	}
	else
	{
		Velocity = { 300.0f, 1000.0f, 0.0f };
	}

}

void AFireMob::Air(float _DeltaTime)
{
	Velocity += FVector::Down * 1200.0f * _DeltaTime;

	AddActorLocation(Velocity * _DeltaTime);

	float PosY = GetActorLocation().Y;
	if (PosY < -1000.0f)
	{
		Destroy();
	}
}

void AFireMob::AirEnd()
{
}
