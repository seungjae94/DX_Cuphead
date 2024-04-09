#include "PreCompile.h"
#include "Noise.h"

ANoise::ANoise()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	
	Renderer->SetSprite(GImageName::Noise);
	Renderer->CreateAnimation(GAnimName::Noise, GImageName::Noise, 0.05f);
}

ANoise::~ANoise()
{
}

void ANoise::BeginPlay()
{
	Super::BeginPlay();

	Renderer->Transform.SetPosition(FVector::Zero);
	Renderer->Transform.SetScale({1280.0f, 720.0f, 1.0f});
	Renderer->ChangeAnimation(GAnimName::Noise);
}

void ANoise::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
