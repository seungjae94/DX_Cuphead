#include "PreCompile.h"
#include "CupheadCore.h"
#include "TestGameMode.h"
#include "TitleGameMode.h"
#include "OverworldGameMode.h"
#include "BossFarmGameMode.h"
#include "BossDragonGameMode.h"
#include "CupheadDebugWindow.h"
#include <EngineCore/EngineTexture.h>

std::shared_ptr<UCupheadDebugWindow> DebugWindow;

UCupheadCore::UCupheadCore()
{
}

UCupheadCore::~UCupheadCore()
{
}

void UCupheadCore::Initialize()
{
	CreateDebugWindows();
	CreateMaterials();
	LoadResources();
	CreateLevels();
	GEngine->ChangeLevel(GLevelName::BossFarmLevel);
}

void UCupheadCore::CreateDebugWindows()
{
	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UCupheadDebugWindow>("CupheadDebugWindow");
}

void UCupheadCore::CreateMaterials()
{
	{
		std::shared_ptr<UEngineMaterial> Box = UEngineMaterial::Create("Box");
		Box->SetVertexShader("ColorShader.fx");
		Box->SetPixelShader("ColorShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("Noise");
		Mat->SetVertexShader("ImageShader.fx");
		Mat->SetPixelShader("ImageShader.fx");
		Mat->SetBlend("Overlay");
	}
}

void UCupheadCore::LoadResources()
{
	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("TitleLevel");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
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
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
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
		CurDir.Move("Player");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Dirs = CurDir.GetAllDirectory();
		for (size_t i = 0; i < Dirs.size(); i++)
		{
			UEngineSprite::LoadFolder(Dirs[i].GetFullPath());
		}

		UEngineSprite::CreateCutting(GImageName::PlayerIdle, 5, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerJump, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerParry, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerDash, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerSit, 5, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerHit, 6, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerRun, 16, 1);

		UEngineSprite::CreateCutting(GImageName::BulletSpawn, 4, 1);
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("BossFarmLevel");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Dirs = CurDir.GetAllDirectory();
		for (size_t i = 0; i < Dirs.size(); i++)
		{
			UEngineSprite::LoadFolder(Dirs[i].GetFullPath());
		}

		UEngineSprite::CreateCutting("potato_intro.png", 11, 1);
		UEngineSprite::CreateCutting("potato_idle.png", 4, 1);
		UEngineSprite::CreateCutting("potato_faint.png", 9, 1);
		UEngineSprite::CreateCutting("potato_ground_intro.png", 16, 1);
		UEngineSprite::CreateCutting("potato_attack.png", 20, 1);
		UEngineSprite::CreateCutting("potato_attack_dust.png", 14, 1);
		UEngineSprite::CreateCutting("potato_attack_ball.png", 8, 1);
		UEngineSprite::CreateCutting("potato_attack_ball_destroy.png", 7, 1);
		UEngineSprite::CreateCutting("potato_attack_snake.png", 4, 1);
		UEngineSprite::CreateCutting("potato_attack_snake_destroy.png", 5, 1);

		UEngineSprite::CreateCutting("onion_intro.png", 24, 1);
		UEngineSprite::CreateCutting("onion_idle.png", 14, 1);
		UEngineSprite::CreateCutting("onion_faint.png", 15, 1);
		UEngineSprite::CreateCutting("onion_ground_intro.png", 16, 1);
		UEngineSprite::CreateCutting("onion_cry_intro.png", 6, 1);
		UEngineSprite::CreateCutting("onion_cry_start.png", 11, 1);
		UEngineSprite::CreateCutting("onion_cry_loop.png", 5, 1);
		UEngineSprite::CreateCutting("onion_cry_wait.png", 8, 1);
		UEngineSprite::CreateCutting("onion_tear_start.png", 5, 1);
		UEngineSprite::CreateCutting("onion_tear_loop.png", 4, 1);
		UEngineSprite::CreateCutting("onion_tear_end.png", 7, 1);
		UEngineSprite::CreateCutting("onion_attack.png", 3, 1);
		UEngineSprite::CreateCutting("onion_attack_pink.png", 3, 1);
		UEngineSprite::CreateCutting("onion_attack_destroy.png", 7, 1);
		UEngineSprite::CreateCutting("onion_attack_pink_destroy.png", 6, 1);

		UEngineSprite::CreateCutting("carrot_idle.png", 22, 1);
		UEngineSprite::CreateCutting("carrot_idle_to_beam.png", 9, 1);
		UEngineSprite::CreateCutting("carrot_ground_intro.png", 16, 1);
		UEngineSprite::CreateCutting("carrot_beam_body.png", 4, 1);
		UEngineSprite::CreateCutting("carrot_beam_eye.png", 4, 1);
		UEngineSprite::CreateCutting("carrot_faint.png", 21, 1);
		UEngineSprite::CreateCutting("carrot_proj.png", 6, 1);
		UEngineSprite::CreateCutting("carrot_beam_proj.png", 12, 1);
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("BossDragonLevel");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Dirs = CurDir.GetAllDirectory();
		for (size_t i = 0; i < Dirs.size(); i++)
		{
			UEngineSprite::LoadFolder(Dirs[i].GetFullPath());
		}

		UEngineSprite::CreateCutting("dragon1_idle.png", 8, 2);
		UEngineSprite::CreateCutting("dragon1_tail.png", 12, 1);
		UEngineSprite::CreateCutting("dragon1_attack.png", 7, 1);
		UEngineSprite::CreateCutting("dragon1_attack_start.png", 8, 2);
		UEngineSprite::CreateCutting("dragon1_attack_end.png", 8, 1);
		UEngineSprite::CreateCutting("dragon1_attack_proj.png", 8, 1);
		UEngineSprite::CreateCutting("dragon1_attack_smoke.png", 7, 5);
		UEngineSprite::CreateCutting("dragon1_beam_eye.png", 11, 1);
		UEngineSprite::CreateCutting("dragon1_beam.png", 8, 2);
		UEngineSprite::CreateCutting("dragon1_beam_start.png", 8, 1);
		UEngineSprite::CreateCutting("dragon1_beam_end.png", 8, 1);
		UEngineSprite::CreateCutting("dragon1_beam_proj.png", 8, 1);
		UEngineSprite::CreateCutting("dragon1_beam_proj_pink.png", 8, 1);

		UEngineSprite::CreateCutting("dragon1_cloud_idle.png", 3, 1);
		UEngineSprite::CreateCutting("dragon1_cloud_down_idle.png", 3, 1);
		UEngineSprite::CreateCutting("dragon1_cloud_down.png", 3, 1);
		UEngineSprite::CreateCutting("dragon1_cloud_up.png", 5, 1);
	}

	{
		UEngineDirectory CurDir;
		CurDir.MoveToSearchChild("ContentsResources");
		CurDir.Move("Common");
		std::vector<UEngineFile> Files = CurDir.GetAllFile({ ".png" }, false);
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
	GEngine->CreateLevel<ATestGameMode>(GLevelName::TestLevel);
	GEngine->CreateLevel<ATitleGameMode>(GLevelName::TitleLevel);
	GEngine->CreateLevel<AOverworldGameMode>(GLevelName::OverworldLevel);
	GEngine->CreateLevel<ABossFarmGameMode>(GLevelName::BossFarmLevel);
	GEngine->CreateLevel<ABossDragonGameMode>(GLevelName::BossDragonLevel);
}

