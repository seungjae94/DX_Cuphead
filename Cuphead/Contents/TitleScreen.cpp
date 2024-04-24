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

	Text = CreateDefaultSubObject<USpriteRenderer>("Text");
	Text->SetupAttachment(Root);
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

	Characters->SetOrder(ERenderingOrder::Back1);
	Characters->SetSprite(GImageName::TitleScreenCharacters);
	Characters->SetAutoSize(1.0f, true);
	Characters->CreateAnimation(GAnimName::TitleDance, GImageName::TitleScreenCharacters, 0.04f);
	Characters->ChangeAnimation(GAnimName::TitleDance);

	Text->SetOrder(ERenderingOrder::Back2);
	Text->SetSprite("title_press_any_button.png");
	Text->SetAutoSize(1.0f, true);
	Text->SetPosition({0.0f, -300.0f, 0.0f});

	TextToggleTimer = TextToggleTime;
}

void ATitleScreen::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector Scale = Characters->Transform.GetScale();
	Characters->Transform.SetPosition({ 0.0f, -361.0f + Scale.ihY(), 0.0f});

	TextToggleTimer -= _DeltaTime;
	if (TextToggleTimer < 0.0f)
	{
		Text->SetActive(!Text->IsActive());

		TextToggleTimer = TextToggleTime;
	}
}

