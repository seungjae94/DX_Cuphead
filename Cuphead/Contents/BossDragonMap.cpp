#include "PreCompile.h"
#include "BossDragonMap.h"
#include "CupheadCore.h"
#include "CupheadDebugWindow.h"

ABossDragonMap::ABossDragonMap()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Background0 = CreateDefaultSubObject<USpriteRenderer>("Background0");
	Background0->SetupAttachment(Root);

	Background1 = CreateDefaultSubObject<USpriteRenderer>("Background1");
	Background1->SetupAttachment(Root);

	Col = CreateDefaultSubObject<USpriteRenderer>("Col");
	Col->SetupAttachment(Root);
}

ABossDragonMap::~ABossDragonMap()
{
}

void ABossDragonMap::BeginPlay()
{
	Super::BeginPlay();

	MapScale = { 1280.0f, 720.0f };

	Background0->SetSprite(GImageName::BossDragonMapBackground);
	Background0->SetOrder(ERenderingOrder::Back0);
	Background0->Transform.SetScale(MapScale);

	Background1->SetSprite(GImageName::BossDragonMapBackground);
	Background1->SetOrder(ERenderingOrder::Back0);
	Background1->Transform.SetScale(MapScale);

	Background0->SetPosition({ -MapScale.X + 1.0f, 0.0f, 0.0f });
	Background1->SetPosition({ 0.0f, 0.0f, 0.0f });

	Col->SetSprite("boss_farm_map_col.png");
	Col->SetOrder(ERenderingOrder::Collider);
	Col->SetAutoSize(1.0f, true);
	Col->SetActive(false);

	//DebugWindow->RegisterCallback(
	//	std::bind(&ABossDragonMap::ShowPixelColMapCheckBox, this)
	//);
}

void ABossDragonMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Background0->Transform.AddPosition(FVector::Right * BackgroundSpeed * _DeltaTime);
	Background1->Transform.AddPosition(FVector::Right * BackgroundSpeed * _DeltaTime);

	int PosX = Background1->Transform.GetPosition().iX();
	int WindowX = GEngine->EngineWindow.GetWindowScale().iX();
	if (PosX >= WindowX)
	{
		Background0->Transform.SetPosition({ -MapScale.X + 1.0f, 0.0f, 0.0f });
		Background1->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	}

	DebugWindow->RegisterCallback(
		"BossDragonMapPixelColToggle",
		std::bind(&ABossDragonMap::ShowPixelColMapCheckBox, this)
	);
}

void ABossDragonMap::ShowPixelColMapCheckBox()
{
	bool Clicked = ImGui::Checkbox("Dragon Map Pixel Collision", &ShowColMap);
	if (true == Clicked)
	{
		ToggleColMap();
	}
}

void ABossDragonMap::ToggleColMap()
{
	Col->SetActive(!Col->IsActive());
}