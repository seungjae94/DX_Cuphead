#include "PreCompile.h"
#include "Noise.h"

ANoise::ANoise()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

ANoise::~ANoise()
{
}

void ANoise::BeginPlay()
{
	Super::BeginPlay();

	//Renderer->SetMaterial("Noise");
	Renderer->SetSprite(GImageName::Noise);
	Renderer->SetOrder(ERenderingOrder::Noise);
	Renderer->SetScale(GConstant::WindowScale);
	Renderer->CreateAnimation(GAnimName::Noise, GImageName::Noise, 0.05f);
	Renderer->ChangeAnimation(GAnimName::Noise);
}

void ANoise::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//SetActorLocation(GetWorld()->GetMainCamera()->GetActorLocation());
}
