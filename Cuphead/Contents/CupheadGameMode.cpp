#include "PreCompile.h"
#include "CupheadGameMode.h"
#include "Noise.h"

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

	Noise = GetWorld()->SpawnActor<ANoise>("Noise", INT_MAX).get();

	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}
