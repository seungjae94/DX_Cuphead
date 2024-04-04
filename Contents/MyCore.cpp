#include "PreCompile.h"
#include "MyCore.h"
#include "TestGameMode.h"
#include "TitleGameMode.h"
#include <EngineCore/EngineTexture.h>

UMyCore::UMyCore() 
{
}

UMyCore::~UMyCore() 
{
}

void UMyCore::Initialize()
{
	LoadResources();
	CreateLevels();
	GEngine->ChangeLevel("TitleLevel");
}

void UMyCore::LoadResources()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineTexture::Load(File.GetFullPath());
		}
	}
}

void UMyCore::CreateLevels()
{
	GEngine->CreateLevel<ATestGameMode>("TestLevel");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
}

