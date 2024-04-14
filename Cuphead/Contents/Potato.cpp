#include "PreCompile.h"
#include "Potato.h"

APotato::APotato()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	GroundRenderer = CreateDefaultSubObject<USpriteRenderer>("Ground");
	PotatoRenderer = CreateDefaultSubObject<USpriteRenderer>("Potato");

	GroundRenderer->SetupAttachment(Root);
	PotatoRenderer->SetupAttachment(Root);
}

APotato::~APotato()
{
}

void APotato::PlayGroundIntroAnimation()
{
	GroundRenderer->ChangeAnimation("ground_intro");
}

void APotato::PlayPotatoIntroAnimation()
{
	PotatoRenderer->ChangeAnimation("potato_intro");
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	PotatoRenderer->CreateAnimation("potato_intro", "potato_intro.png", 1 / 12.0f, false);
	GroundRenderer->CreateAnimation("ground_intro", "potato_ground_intro.png",
		std::vector<float>(28, 1 / 18.0f),
		{ 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, false);

	PotatoRenderer->SetOrder(ERenderingOrder::Back5);
	GroundRenderer->SetOrder(ERenderingOrder::Back6);

	PotatoRenderer->SetPivot(EPivot::BOT);
	GroundRenderer->SetPivot(EPivot::BOT);

	PotatoRenderer->SetAutoSize(1.0f, true);
	GroundRenderer->SetAutoSize(1.0f, true);

	PotatoRenderer->SetPosition({ 450.0f, -300.0f });
	GroundRenderer->SetPosition({ 450.0f, -350.0f });
}
