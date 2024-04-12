#include "PreCompile.h"
#include "TitleScreen.h"

ATitleScreen::ATitleScreen() 
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Background = CreateDefaultSubObject<USpriteRenderer>("Background");
	Background->SetupAttachment(Root);

	Characters = CreateDefaultSubObject<USpriteRenderer>("Characters");
	Characters->SetupAttachment(Root);
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	Background->SetOrder(ERenderingOrder::Back0);
	Background->SetSprite(GImageName::TitleScreenBack);
	Background->SetAutoSize(1.0f, true);

	Characters->SetOrder(ERenderingOrder::Front);
	Characters->SetSprite(GImageName::TitleScreenCharacters);
	Characters->SetAutoSize(1.0f, true);
	Characters->CreateAnimation(GAnimName::TitleDance, GImageName::TitleScreenCharacters, 0.04f);
	Characters->ChangeAnimation(GAnimName::TitleDance);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector Scale = Characters->Transform.GetScale();
	Characters->Transform.SetPosition({ 0.0f, -361.0f + Scale.ihY(), 0.0f});
}

