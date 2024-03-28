#include "PreCompile.h"
#include "MyCore.h"
#include "TestGameMode.h"

UMyCore::UMyCore() 
{
}

UMyCore::~UMyCore() 
{
}

void UMyCore::Initialize()
{
	GEngine->CreateLevel<ATestGameMode>("TestLevel");
	GEngine->ChangeLevel("TestLevel");
}

