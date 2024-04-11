#include "PreCompile.h"
#include "Physics.h"

const FVector UPhysics::Gravity = { 0.0f, -980.0f, 0.0f };

UPhysics::UPhysics(AActor* _Actor)
{
	Actor = _Actor;
}
void UPhysics::SetVelocityX(float _X)
{
	Velocity.X = _X;
}

void UPhysics::AddForce(FVector _Force)
{
	// 질량은 1로 가정한다.
	Velocity += _Force;
}

void UPhysics::Update(float _DeltaTime)
{
	if (true == OnGroundValue && Velocity.Y < 0.0f)
	{
		Velocity.Y = 0.0f;
	}

	Actor->AddActorLocation(Velocity);
}

UPhysics::~UPhysics()
{
}
