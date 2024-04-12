#pragma once
#include "Constant.h"

class UConverter
{
public:
	static FVector ConvDirectionToFVector(EDirection _Direction);
	static FVector ConvEngineDirToFVector(EEngineDir _Direction);
private:
	UConverter();
	~UConverter();
};

