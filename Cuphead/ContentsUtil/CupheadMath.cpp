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

FVector UCupheadMath::DegToDirection(float _Deg)
{
	return RadToDirection(_Deg * UEngineMath::DToR);
}

FVector UCupheadMath::RadToDirection(float _Rad)
{
	float X = std::cos(_Rad);
	float Y = std::sin(_Rad);
	return { X, Y, 0.0f };
}

float UCupheadMath::DirectionToDeg(const FVector& _Direction)
{
	return DirectionToRad(_Direction) * UEngineMath::RToD;
}

float UCupheadMath::DirectionToRad(const FVector& _Direction)
{
	if (_Direction.X == 0.0f)
	{
		if (_Direction.Y > 0.0f)
		{
			return PI / 2.0f;
		}

		return 3.0f * PI / 2.0f;
	}

	// Angle in [-PI/2, PI/2]
	float Angle = std::atan(_Direction.Y / _Direction.X);

	if (_Direction.X < 0.0f)
	{
		Angle += PI;
	}

	float ResultAngle = Angle + 2.0f * PI;

	if (ResultAngle >= 2.0f * PI)
	{
		ResultAngle -= 2.0f * PI;
	}

	return ResultAngle;
}

float UCupheadMath::SubtractDeg(float _First, float _Second)
{
	float Result = _First - _Second;

	if (Result >= 180.0f)
	{
		return Result - 360.0f;
	}

	if (Result < -180.0f)
	{
		return Result + 360.0f;
	}

	return Result;
}
