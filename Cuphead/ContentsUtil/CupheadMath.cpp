#include "PreCompile.h"
#include "CupheadMath.h"
#include <cmath>

float UCupheadMath::PI = static_cast<float>(std::atan(1) * 4);

UCupheadMath::UCupheadMath()
{
}

UCupheadMath::~UCupheadMath()
{
}

float UCupheadMath::DirectionToDeg(const FVector& _Direction)
{
	return DirectionToRad(_Direction) * UEngineMath::RToD;
}

float UCupheadMath::DirectionToRad(const FVector& _Direction)
{
	float Angle = std::atan(_Direction.Y / _Direction.X);

	if (_Direction.X < 0)
	{
		Angle += PI;
	}

	return Angle;
}
