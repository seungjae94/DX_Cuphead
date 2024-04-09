#include "PreCompile.h"
#include "Converter.h"

FVector UConverter::ConvDirectionToFVector(EDirection _Direction)
{
	FVector Result;

	switch (_Direction)
	{
	case EDirection::Right:
		Result = FVector::Right;
		break;
	case EDirection::RightUp:
		Result = FVector::Right + FVector::Up;
		Result.Normalize2D();
		break;
	case EDirection::Up:
		Result = FVector::Up;
		break;
	case EDirection::LeftUp:
		Result = FVector::Left + FVector::Up;
		Result.Normalize2D();
		break;
	case EDirection::Left:
		Result = FVector::Left;
		break;
	case EDirection::LeftDown:
		Result = FVector::Left + FVector::Down;
		Result.Normalize2D();
		break;
	case EDirection::Down:
		Result = FVector::Down;
		break;
	case EDirection::RightDown:
		Result = FVector::Right + FVector::Down;
		Result.Normalize2D();
		break;
	}

	return Result;
}

UConverter::UConverter()
{
}

UConverter::~UConverter()
{
}
