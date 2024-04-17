#include "PreCompile.h"
#include "CarrotBeam.h"

ACarrotBeam::ACarrotBeam()
{
}

ACarrotBeam::~ACarrotBeam()
{
}

void ACarrotBeam::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Collision->AddScale(FVector{ 70.0f, 70.0f } * _DeltaTime);
}
