#include "PreCompile.h"
#include "TitleScreen.h"

ATitleScreen::ATitleScreen() 
{
	Background = CreateDefaultSubObject<URenderer>("Background");
	Characters = CreateDefaultSubObject<URenderer>("Characters");

	Background->SetMesh("Rect");
	Background->SetMaterial("2DImage");

	Characters->SetMesh("Rect");
	Characters->SetMaterial("2DImage");
}

ATitleScreen::~ATitleScreen() 
{
	
}

void ATitleScreen::BeginPlay()
{
	Super::BeginPlay();

	Background->Transform;
	SetActorScale3D({ 1280.0f, 720.0f, 1.0f });
	Background->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Characters->Transform.SetPosition({ 0.0f, 0.0f, 0.0f });
	Characters->Transform.SetScale({ 1280.0f, 720.0f, 1.0f });
	Background->Resources->SettingTexture("Image", "title_screen_background.png", "POINT");
	Characters->Resources->SettingTexture("Image", "cuphead_title_screen_0001.png", "POINT");
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

