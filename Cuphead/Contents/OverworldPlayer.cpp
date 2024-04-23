#include "PreCompile.h"
#include "OverworldPlayer.h"

AOverworldPlayer::AOverworldPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	ZButtonRenderer = CreateDefaultSubObject<USpriteRenderer>("ZButtonRenderer");
	ZButtonRenderer->SetupAttachment(Root);
	ZButtonRenderer->SetOrder(ERenderingOrder::UI);
	ZButtonRenderer->SetActive(false);
	ZButtonRenderer->SetSprite("overworld_zbutton.png");
	ZButtonRenderer->SetAutoSize(1.0f, true);
	ZButtonRenderer->SetPosition({0.0f, 70.0f, 0.0f});

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::PlayerHitBox);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

AOverworldPlayer::~AOverworldPlayer()
{
}

void AOverworldPlayer::SetZButtonActive(bool _Value)
{
	ZButtonRenderer->SetActive(_Value);
}

void AOverworldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 100.0f, 0.0f, 0.0f });
	BringCamera();
	
	Renderer->SetSprite(GImageName::OverworldCharDownIdle);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Character);

	Collision->SetScale({ 50.0f, 80.0f, 1.0f });
	Collision->SetPosition({ 0.0f, 0.0f, 0.0f });

	AnimationInit();
	StateInit();

	InputOn();
}

void AOverworldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector PrevPos = GetActorLocation();

	StateManager.Update(_DeltaTime);

	if (true == Collision->CollisionEnter(ECollisionGroup::BossLevelEntranceBlock, nullptr))
	{
		SetActorLocation(PrevPos);
	}

	Collision->CollisionEnter(ECollisionGroup::BossLevelEntranceBlock, [this, PrevPos](std::shared_ptr<UCollision> _Other) {
		SetActorLocation(PrevPos);
	});

	// 카메라 이동 처리
	BringCamera();

	DebugUpdate(_DeltaTime);
}

void AOverworldPlayer::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Player Position : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
		std::string Msg = std::format("Camera Position : {}\n", CameraPos.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void AOverworldPlayer::BringCamera()
{
	FVector Diff = GetActorLocation() - GetWorld()->GetMainCamera()->GetActorLocation();
	float Dist = Diff.Size2D();

	if (Dist < 1.0f)
	{
		return;
	}

	float CameraZ = GetWorld()->GetMainCamera()->GetActorLocation().Z;
	FVector CameraLocation = GetActorLocation();
	CameraLocation.Z = CameraZ;


	GetWorld()->GetMainCamera()->SetActorLocation(CameraLocation);
}
