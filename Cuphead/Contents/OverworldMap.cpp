#include "PreCompile.h"
#include "OverworldMap.h"

AOverworldMap::AOverworldMap()
{
	Back = CreateDefaultSubObject<USpriteRenderer>("Back");
	Front = CreateDefaultSubObject<USpriteRenderer>("Front");
	Col = CreateDefaultSubObject<USpriteRenderer>("Col");
}

AOverworldMap::~AOverworldMap()
{
}

void AOverworldMap::ToggleColMap()
{
	Col->SetActive(!Col->IsActive());
}

void AOverworldMap::BeginPlay()
{
	Super::BeginPlay();

	Back->SetSprite(GImageName::OverworldIsle1Back);
	Back->SetOrder(ERenderingOrder::Back);
	Back->SetAutoSize(1.0f, true);

	Front->SetSprite(GImageName::OverworldIsle1Front);
	Front->SetOrder(ERenderingOrder::Front);
	Front->SetAutoSize(1.0f, true);

	Col->SetSprite(GImageName::OverworldIsle1Pixel);
	Col->SetOrder(ERenderingOrder::Collider);
	Col->SetAutoSize(1.0f, true);

	Col->SetActive(false);
}

void AOverworldMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
