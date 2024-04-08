#include "PreCompile.h"
#include "BossDragonMap.h"
#include "Constant.h"

ABossDragonMap::ABossDragonMap()
{
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");
	Background->SetSprite(ImageName::BossDragonMapBackground);
}

ABossDragonMap::~ABossDragonMap()
{
}

void ABossDragonMap::BeginPlay()
{
	Super::BeginPlay();

	Background->Transform.SetScale({ 1280.0f, 720.0f, 0.0f });
}

void ABossDragonMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
