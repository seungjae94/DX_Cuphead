#include "PreCompile.h"
#include "TitleScreen.h"
#include "Constant.h"

ATitleScreen::ATitleScreen() 
{
	Characters = CreateDefaultSubObject<USpriteRenderer>("Characters");
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");

	Background->SetSprite(ImageName::TitleScreenBack);
	Background->SetAutoSize(1.0f, true);
	Characters->SetSprite(ImageName::TitleScreenCharacters);
	Characters->SetAutoSize(1.0f, true);
	Characters->CreateAnimation(AnimName::TitleDance, ImageName::TitleScreenCharacters, 0.04f);
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });

	Background->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Characters->ChangeAnimation(AnimName::TitleDance);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector Scale = Characters->Transform.GetScale();
	Characters->Transform.SetPosition({ 0.0f, -361.0f + Scale.ihY(), 0.0f});
}

