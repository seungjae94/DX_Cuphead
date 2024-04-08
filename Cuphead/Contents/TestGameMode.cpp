#include "PreCompile.h"
#include "TestGameMode.h"
#include "TestPlayer.h"

ATestGameMode::ATestGameMode() 
{
}

ATestGameMode::~ATestGameMode() 
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<ATestPlayer>("TP");
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

