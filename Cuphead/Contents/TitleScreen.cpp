#include "PreCompile.h"
#include "TitleScreen.h"
#include "Constant.h"

ATitleScreen::ATitleScreen() 
{
	Characters = CreateDefaultSubObject<USpriteRenderer>("Characters");
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");

	Background->SetSprite(ImageName::TitleScreenBack);
	Characters->SetSprite(ImageName::TitleScreenCharacters);
	Characters->CreateAnimation(AnimName::TitleDance, ImageName::TitleScreenCharacters, 0.0425f);
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });

	Background->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Characters->Transform.SetPosition({ 0.0f, -60.0f, 0.0f });
	Background->Transform.SetScale({ 1280.0f, 720.0f, 1.0f });
	Characters->Transform.SetScale({ 1067.0f, 600.0f, 1.0f });
	Characters->ChangeAnimation(AnimName::TitleDance);
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

