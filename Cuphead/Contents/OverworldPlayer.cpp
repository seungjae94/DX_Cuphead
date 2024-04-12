#include "PreCompile.h"
#include "OverworldPlayer.h"

AOverworldPlayer::AOverworldPlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

AOverworldPlayer::~AOverworldPlayer()
{
}

void AOverworldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 100.0f, 0.0f, 0.0f });
	BringCamera();

	Renderer->SetSprite(GImageName::OverworldCharDownIdle);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Character);

	AnimationInit();
	StateInit();

	InputOn();
}

void AOverworldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
}


void AOverworldPlayer::BringCamera()
{
	float CameraZ = GetWorld()->GetMainCamera()->GetActorLocation().Z;
	FVector CameraLocation = GetActorLocation();
	CameraLocation.Z = CameraZ;
	GetWorld()->GetMainCamera()->SetActorLocation(CameraLocation);
}