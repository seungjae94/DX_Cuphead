#include "PreCompile.h"
#include "CupheadCore.h"
#include "Constant.h"
#include "TestGameMode.h"
#include "TitleGameMode.h"
#include "OverworldGameMode.h"
#include <EngineCore/EngineTexture.h>

UCupheadCore::UCupheadCore()
{
}

UCupheadCore::~UCupheadCore()
{
}

void UCupheadCore::Initialize()
{
	LoadResources();
	CreateLevels();
	GEngine->ChangeLevel(LevelName::TitleLevel);
}

void UCupheadCore::LoadResources()
{
	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
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

	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("OverworldLevel");
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

	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("Common");
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

void UCupheadCore::CreateLevels()
{
	GEngine->CreateLevel<ATestGameMode>(LevelName::TestLevel);
	GEngine->CreateLevel<ATitleGameMode>(LevelName::TitleLevel);
	GEngine->CreateLevel<AOverworldGameMode>(LevelName::OverworldLevel);
}

