#include "PreCompile.h"
#include "CupheadGameMode.h"

ACupheadGameMode::ACupheadGameMode()
{
}

ACupheadGameMode::~ACupheadGameMode()
{
}

void ACupheadGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	Noise = CreateWidget<UImage>(GetWorld(), "Noise");
	Noise->AddToViewPort(ERenderingOrder::Noise);
	Noise->CreateAnimation("common_noise", "common_noise", 1 / 24.0f, true);
	Noise->ChangeAnimation("common_noise");
	Noise->SetScale({ 1280.0f, 720.0f });
	Noise->SetPosition(FVector::Zero);

	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}
