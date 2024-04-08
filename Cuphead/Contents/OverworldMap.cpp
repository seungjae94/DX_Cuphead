#include "PreCompile.h"
#include "OverworldMap.h"
#include "Constant.h"

AOverworldMap::AOverworldMap()
{
	Back = CreateDefaultSubObject<USpriteRenderer>("Back");
	Front = CreateDefaultSubObject<USpriteRenderer>("Front");

	Back->SetSprite(ImageName::OverworldIsle1Back);
	Front->SetSprite(ImageName::OverworldIsle1Front);
}

AOverworldMap::~AOverworldMap()
{
}

void AOverworldMap::BeginPlay()
{
	Super::BeginPlay();

	Back->Transform.SetPosition(FVector::Zero);
	Back->Transform.SetScale({ 4000.0f, 2200.0f, 1.0f });
	Front->Transform.SetPosition(FVector::Zero);
	Front->Transform.SetScale({ 4000.0f, 2200.0f, 1.0f });
}

void AOverworldMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
