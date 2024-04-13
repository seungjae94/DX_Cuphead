#include "PreCompile.h"
#include "OverworldPlayer.h"
#include "Noise.h"

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

void AOverworldPlayer::SetNoise(ANoise* _Noise)
{
	Noise = _Noise;
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

	DebugMsgUpdate(_DeltaTime);
}

void AOverworldPlayer::DebugMsgUpdate(float _DeltaTime)
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

	{
		float FPS = 1 / _DeltaTime;
		std::string Msg = std::format("FPS : {}\n", std::to_string(FPS));
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

void AOverworldPlayer::BringNoise()
{
	Noise->SetActorLocation(GetActorLocation());
}
