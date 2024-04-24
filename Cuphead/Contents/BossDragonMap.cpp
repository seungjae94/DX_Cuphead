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
}
