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
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("Resources");
		CurDir.Move("TitleLevel");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Dirs = CurDir.GetAllDirectory();
		for (size_t i = 0; i < Dirs.size(); i++)
		{
			UEngineSprite::LoadFolder(Dirs[i].GetFullPath());
		}
	}
}

void UMyCore::CreateLevels()
{
	GEngine->CreateLevel<ATestGameMode>("TestLevel");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
}

