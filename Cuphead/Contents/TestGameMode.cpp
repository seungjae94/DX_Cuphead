#include "PreCompile.h"
#include "TestGameMode.h"

ATestGameMode::ATestGameMode() 
{
}

ATestGameMode::~ATestGameMode() 
{
}

void ATestGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<ACamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
}

void ATestGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

