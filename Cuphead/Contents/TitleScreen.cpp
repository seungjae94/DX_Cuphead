#include "PreCompile.h"
#include "TitleScreen.h"

ATitleScreen::ATitleScreen() 
{
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");
	Characters = CreateDefaultSubObject<USpriteRenderer>("Characters");
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });

	Background->SetOrder(ERenderingOrder::Back);
	Background->SetSprite(GImageName::TitleScreenBack);
	Background->SetAutoSize(1.0f, true);
	Background->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });

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
