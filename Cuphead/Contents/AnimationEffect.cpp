#include "PreCompile.h"
#include "AnimationEffect.h"

AAnimationEffect::AAnimationEffect()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	SetRoot(Root);
	Renderer->SetupAttachment(Root);
}

AAnimationEffect::~AAnimationEffect()
{
}

void AAnimationEffect::Init(ERenderingOrder _Order, FCreateAnimationParameter _Parameter, bool _AutoDestroy)
{
	Renderer->SetSprite(_Parameter.ImageName);
	Renderer->SetOrder(_Order);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->CreateAnimation(_Parameter.AnimName, _Parameter.ImageName, _Parameter.Interval, false, -1, -1);
	AutoDestroy = _AutoDestroy;

	Renderer->ChangeAnimation(_Parameter.AnimName);
}

void AAnimationEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == AutoDestroy && true == Renderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}
