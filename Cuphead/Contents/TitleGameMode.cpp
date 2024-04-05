#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleScreen.h"

ATitleGameMode::ATitleGameMode() 
{

}

ATitleGameMode::~ATitleGameMode() 
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });
	GetWorld()->SpawnActor<ATitleScreen>("TitleScreen");
}

