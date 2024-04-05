#include "PreCompile.h"
#include "TitleScreen.h"

ATitleScreen::ATitleScreen() 
{
	Background = CreateDefaultSubObject<USpriteRenderer>("Background");
	Characters = CreateDefaultSubObject<USpriteRenderer>("Characters");

	Background->SetSprite("title_screen_background.png");
	Background->SetSamplering(ETextureSampling::POINT);
	Characters->CreateAnimation("Dance", "title_screen_characters", 0.0425f);
	Characters->SetSprite("title_screen_characters");
	Characters->SetSamplering(ETextureSampling::POINT);
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });
	Background->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Characters->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Background->Transform.SetPosition({ 1280.0f, 720.0f, 1.0f });
	Characters->Transform.SetScale({ 1280.0f, 720.0f, 1.0f });
	Characters->ChangeAnimation("Dance");
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

