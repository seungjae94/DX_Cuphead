#include "PreCompile.h"
#include "BossFarmMap.h"

ABossFarmMap::ABossFarmMap()
{
	Back0 = CreateDefaultSubObject<USpriteRenderer>("Back0");
	Back1 = CreateDefaultSubObject<USpriteRenderer>("Back1");
	Back2 = CreateDefaultSubObject<USpriteRenderer>("Back2");
	Back3 = CreateDefaultSubObject<USpriteRenderer>("Back3");
	Front = CreateDefaultSubObject<USpriteRenderer>("Front");
	Col = CreateDefaultSubObject<USpriteRenderer>("Col");
}

ABossFarmMap::~ABossFarmMap()
{
}

void ABossFarmMap::ToggleColMap()
{
	Col->SetActive(!Col->IsActive());
}

void ABossFarmMap::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector::Zero);

	Back0->SetSprite("boss_farm_map_back0.png");
	Back1->SetSprite("boss_farm_map_back1.png");
	Back2->SetSprite("boss_farm_map_back2.png");
	Back3->SetSprite("boss_farm_map_back3.png");
	Front->SetSprite("boss_farm_map_front.png");
	Col->SetSprite("boss_farm_map_col.png");

	Back0->SetOrder(ERenderingOrder::Back0);
	Back1->SetOrder(ERenderingOrder::Back1);
	Back2->SetOrder(ERenderingOrder::Back2);
	Back3->SetOrder(ERenderingOrder::Back3);
	Front->SetOrder(ERenderingOrder::Front);
	Col->SetOrder(ERenderingOrder::Collider);

	Back0->SetAutoSize(1.0f, true);
	Back1->SetAutoSize(1.0f, true);
	Back2->SetAutoSize(1.0f, true);
	Back3->SetAutoSize(1.0f, true);
	Front->SetAutoSize(1.0f, true);
	Col->SetAutoSize(1.0f, true);

	Col->SetActive(false);
}

void ABossFarmMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
