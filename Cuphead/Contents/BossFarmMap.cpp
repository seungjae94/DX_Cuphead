#include "PreCompile.h"
#include "BossFarmMap.h"
#include "CupheadCore.h"
#include "CupheadDebugWindow.h"

ABossFarmMap::ABossFarmMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Back0 = CreateDefaultSubObject<USpriteRenderer>("Back0");
	Back0->SetupAttachment(Root);

	Back1 = CreateDefaultSubObject<USpriteRenderer>("Back1");
	Back1->SetupAttachment(Root);

	Back3 = CreateDefaultSubObject<USpriteRenderer>("Back2");
	Back3->SetupAttachment(Root);

	Back4 = CreateDefaultSubObject<USpriteRenderer>("Back3");
	Back4->SetupAttachment(Root);

	Front = CreateDefaultSubObject<USpriteRenderer>("Front");
	Front->SetupAttachment(Root);

	Col = CreateDefaultSubObject<USpriteRenderer>("Col");
	Col->SetupAttachment(Root);
}

ABossFarmMap::~ABossFarmMap()
{
}

void ABossFarmMap::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector::Zero);

	Back0->SetSprite("boss_farm_map_back0.png");
	Back1->SetSprite("boss_farm_map_back1.png");
	Back3->SetSprite("boss_farm_map_back3.png");
	Back4->SetSprite("boss_farm_map_back4.png");
	Front->SetSprite("boss_farm_map_front.png");

	Back0->SetOrder(ERenderingOrder::Back0);
	Back1->SetOrder(ERenderingOrder::Back1);
	Back3->SetOrder(ERenderingOrder::Back3);
	Back4->SetOrder(ERenderingOrder::Back4);
	Front->SetOrder(ERenderingOrder::Front);

	Back0->SetAutoSize(1.0f, true);
	Back1->SetAutoSize(1.0f, true);
	Back3->SetAutoSize(1.0f, true);
	Back4->SetAutoSize(1.0f, true);
	Front->SetAutoSize(1.0f, true);

	Col->SetSprite("boss_farm_map_col.png");
	Col->SetOrder(ERenderingOrder::Collider);
	Col->SetAutoSize(1.0f, true);
	Col->SetActive(false);

	Back0->SetPosition({ 0.0f, 1.0f, 0.0f });

	DebugWindow->RegisterCallback(
		"BossFarmMapPixelColToggle",
		std::bind(&ABossFarmMap::ShowPixelColMapCheckBox, this)
	);
}

void ABossFarmMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABossFarmMap::ShowPixelColMapCheckBox()
{
	bool Clicked = ImGui::Checkbox("Farm Map Pixel Collision", &ShowColMap);
	if (true == Clicked)
	{
		ToggleColMap();
	}
}

void ABossFarmMap::ToggleColMap()
{
	Col->SetActive(!Col->IsActive());
}