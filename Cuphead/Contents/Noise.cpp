#include "PreCompile.h"
#include "Noise.h"

ANoise::ANoise()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	
	Renderer->SetSprite(ImageName::Noise);
	Renderer->CreateAnimation(AnimName::Noise, ImageName::Noise, 0.05f);
}

ANoise::~ANoise()
{
}

void ANoise::BeginPlay()
{
	Super::BeginPlay();

	Renderer->Transform.SetPosition(FVector::Zero);
	Renderer->Transform.SetScale({1280.0f, 720.0f, 1.0f});
	Renderer->ChangeAnimation(AnimName::Noise);
}

void ANoise::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
