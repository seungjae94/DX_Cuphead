#include "PreCompile.h"
#include "OverworldMap.h"

AOverworldMap::AOverworldMap()
{
	Back = CreateDefaultSubObject<USpriteRenderer>("Back");
	Front = CreateDefaultSubObject<USpriteRenderer>("Front");
}

AOverworldMap::~AOverworldMap()
{
}

void AOverworldMap::BeginPlay()
{
	Super::BeginPlay();

	Back->SetSprite(ImageName::OverworldIsle1Back);
	Back->SetOrder(ERenderingOrder::Back);
	Back->SetAutoSize(1.0f, true);

	Front->SetSprite(ImageName::OverworldIsle1Front);
	Front->SetOrder(ERenderingOrder::Front);
	Front->SetAutoSize(1.0f, true);
}

void AOverworldMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
