#include "PreCompile.h"
#include "BossDragonMap.h"

ABossDragonMap::ABossDragonMap()
{
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");
}

ABossDragonMap::~ABossDragonMap()
{
}

void ABossDragonMap::BeginPlay()
{
	Super::BeginPlay();

	Background->SetSprite(ImageName::BossDragonMapBackground);
	Background->SetOrder(ERenderingOrder::Back);
	Background->SetAutoSize(1.0f, true);
}

void ABossDragonMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
