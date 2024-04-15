#include "PreCompile.h"
#include "BossAttack.h"

ABossAttack::ABossAttack()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

ABossAttack::~ABossAttack()
{
}

void ABossAttack::SetOrder(ERenderingOrder _Order)
{
	Renderer->SetOrder(_Order);
}

void ABossAttack::SetSprite(std::string_view _ImageName)
{
	Renderer->SetSprite(_ImageName);
}

void ABossAttack::SetAnimation(std::string_view _AnimName, std::string_view _ImageName, float _Inter, bool _Loop)
{
	Renderer->SetSprite(_ImageName);
	Renderer->SetAutoSize(1.0f, true);

	Renderer->CreateAnimation(_AnimName, _ImageName, _Inter, _Loop);
	Renderer->ChangeAnimation(_AnimName);
}

void ABossAttack::SetVelocity(const FVector& _Velocity, bool _RotateImage, const FVector& _RotationDeg)
{
	Velocity = _Velocity;

	if (true == _RotateImage)
	{
		Renderer->SetRotationDeg(_RotationDeg);
	}
}

void ABossAttack::BeginPlay()
{
	Super::BeginPlay();
}

void ABossAttack::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (EChaseType::None == ChaseType)
	{
		AddActorLocation(Velocity * _DeltaTime);
	}
}
