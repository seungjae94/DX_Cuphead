#include "PreCompile.h"
#include "Noise.h"

ANoise::ANoise()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ANoise::~ANoise()
{
}

void ANoise::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetMaterial("Noise");
	Renderer->SetSprite(GImageName::Noise);
	Renderer->SetOrder(ERenderingOrder::UI);
	Renderer->CreateAnimation(GAnimName::Noise, GImageName::Noise, 0.05f);

	SetActorLocation(FVector::Zero);
	SetActorScale3D({1280.0f, 720.0f, 1.0f});
	Renderer->ChangeAnimation(GAnimName::Noise);
}

void ANoise::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetActorLocation(GetWorld()->GetMainCamera()->GetActorLocation());
}
