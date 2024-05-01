#include "PreCompile.h"
#include "CupheadCore.h"
#include "TestGameMode.h"
#include "TitleGameMode.h"
#include "IntroGameMode.h"
#include "OverworldGameMode.h"
#include "BossFarmGameMode.h"
#include "BossDragonGameMode.h"
#include "PlayResultGameMode.h"
#include "EndingGameMode.h"
#include "CupheadDebugWindow.h"
#include "DebugFontEnumerator.h"
#include <Windows.h>

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
	LoadFonts();
	LoadResources();
	LoadShaders();
	CreateMaterials();
	CreateLevels();
	GEngine->ChangeLevel(GLevelName::TitleLevel);
}

void UCupheadCore::CreateDebugWindows()
{
	DebugWindow = UEngineEditorGUI::CreateEditorWindow<UCupheadDebugWindow>("CupheadDebugWindow");
}

void UCupheadCore::LoadFonts()
{
	UEngineFont::Load("굴림");

	UEngineDirectory CurDir;
	CurDir.MoveToSearchChild("ContentsResources");
	CurDir.Move("Font");
	std::vector<UEngineFile> AllFontFiles = CurDir.GetAllFile({".ttf", ".otf"}, false);

	for (UEngineFile& File : AllFontFiles)
	{
		AddFontResourceEx(File.GetFullPath().c_str(), FR_NOT_ENUM, 0);
	}

#ifdef _DEBUG
	std::list<std::string> AllFontList = UDebugFontEnumerator::GetAllFontList();
	
	for (std::string& FontName : AllFontList)
	{
		//UEngineDebug::OutPutDebugText(FontName);
	}
#endif
}

void UCupheadCore::LoadResources()
{
	std::vector<std::string> AllImageFullNames;
	std::vector<std::string> AllSoundFullNames;
	std::vector<std::string> AllFolderFullNames;

	UEngineDirectory CurDir;
	CurDir.MoveToSearchChild("ContentsResources");
	std::vector<std::string> FirstFolderNames;
	std::vector<UEngineDirectory> FirstFolders = CurDir.GetAllDirectory(false);

	for (UEngineDirectory& FirstFolder : FirstFolders)
	{
		RegisterResourceNames(AllImageFullNames, AllSoundFullNames, AllFolderFullNames, FirstFolder.GetFolderName());
	}
	
	// 일단 메인 쓰레드로 사운드 로딩
	for (std::string_view SoundFileName : AllSoundFullNames)
	{
		UEngineSound::Load(SoundFileName);
	}


	{
		LoadingCount = static_cast<int>(AllImageFullNames.size() + AllFolderFullNames.size());

		for (std::string_view FileName : AllImageFullNames)
		{
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoad(FileName);
					--LoadingCount;
				});
		}

		for (std::string_view FolderName : AllFolderFullNames)
		{
			GEngine->JobWorker.Work([=]()
				{
					UEngineSprite::ThreadSafeLoadFolder(FolderName);
					--LoadingCount;
				});
		}

		while (LoadingCount > 0)
		{
		}
	}

	{
		// 오버월드 커팅
		UEngineSprite::CreateCutting("overworld_farm.png", 3, 1);
		UEngineSprite::CreateCutting("overworld_spire.png", 3, 1);
		UEngineSprite::CreateCutting("overworld_flag.png", 12, 1);


		// 보스맵 플레이어 커팅
		UEngineSprite::CreateCutting(GImageName::PlayerIntro, 28, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerIdle, 5, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerJump, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerParry, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerDash, 8, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerSit, 5, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerSitting, 7, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerHit, 6, 1);
		UEngineSprite::CreateCutting(GImageName::PlayerRun, 16, 1);
		UEngineSprite::CreateCutting(GImageName::BulletSpawn, 4, 1);
		UEngineSprite::CreateCutting(GImageName::BulletDestroy, 6, 1);

		// 농장맵 커팅
		UEngineSprite::CreateCutting("ground_front_intro.png", 16, 1);
		UEngineSprite::CreateCutting("ground_back_intro.png", 16, 1);

		UEngineSprite::CreateCutting("potato_intro.png", 11, 1);
		UEngineSprite::CreateCutting("potato_idle.png", 4, 1);
		UEngineSprite::CreateCutting("potato_faint.png", 9, 1);
		UEngineSprite::CreateCutting("potato_attack.png", 20, 1);
		UEngineSprite::CreateCutting("potato_attack_dust.png", 14, 1);
		UEngineSprite::CreateCutting("potato_attack_ball.png", 8, 1);
		UEngineSprite::CreateCutting("potato_attack_ball_destroy.png", 7, 1);
		UEngineSprite::CreateCutting("potato_attack_snake.png", 4, 1);
		UEngineSprite::CreateCutting("potato_attack_snake_destroy.png", 5, 1);

		UEngineSprite::CreateCutting("onion_intro.png", 24, 1);
		UEngineSprite::CreateCutting("onion_idle.png", 14, 1);
		UEngineSprite::CreateCutting("onion_faint.png", 15, 1);
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
		UEngineSprite::CreateCutting("carrot_beam_body.png", 4, 1);
		UEngineSprite::CreateCutting("carrot_beam_eye.png", 4, 1);
		UEngineSprite::CreateCutting("carrot_faint.png", 21, 1);
		UEngineSprite::CreateCutting("carrot_proj.png", 6, 1);
		UEngineSprite::CreateCutting("carrot_proj_destroy.png", 10, 1);
		UEngineSprite::CreateCutting("carrot_beam_proj.png", 12, 1);

		// 용맵 커팅
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

		UEngineSprite::CreateCutting("dragon2_idle.png", 14, 1);
		UEngineSprite::CreateCutting("dragon2_smoke.png", 21, 1);

		UEngineSprite::CreateCutting("firemob_jump.png", 4, 1);
		UEngineSprite::CreateCutting("firemob_jump_ready.png", 5, 1);
		UEngineSprite::CreateCutting("firemob_jump_ready_start.png", 5, 1);
		UEngineSprite::CreateCutting("firemob_run.png", 8, 2);
		UEngineSprite::CreateCutting("firemob_air.png", 8, 1);
	}
}

void UCupheadCore::RegisterResourceNames(std::vector<std::string>& _AllImageFullNames, std::vector<std::string>& _AllSoundFullNames, std::vector<std::string>& _AllFolderFullNames, std::string_view _FolderName)
{
	UEngineDirectory CurDir;
	CurDir.MoveToSearchChild("ContentsResources");
	CurDir.Move(_FolderName);

	// 이미지 로딩
	std::vector<UEngineFile> ImageFiles = CurDir.GetAllFile({ ".png" }, false);
	for (UEngineFile& File : ImageFiles)
	{
		_AllImageFullNames.push_back(File.GetFullPath());
	}

	std::vector<UEngineDirectory> Dirs = CurDir.GetAllDirectory();
	for (size_t i = 0; i < Dirs.size(); i++)
	{
		_AllFolderFullNames.push_back(Dirs[i].GetFullPath());
	}

	std::vector<UEngineFile> SoundFiles = CurDir.GetAllFile({ ".mp3" }, true);
	for (UEngineFile& File : SoundFiles)
	{
		_AllSoundFullNames.push_back(File.GetFullPath());
	}
}

void UCupheadCore::LoadShaders()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsShader");
	UEngineShader::AutoCompile(Dir);
}

void UCupheadCore::CreateMaterials()
{
	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DCropImage");
		Mat->SetVertexShader("CropImageShader.fx");
		Mat->SetPixelShader("CropImageShader.fx");
	}
}

void UCupheadCore::CreateLevels()
{
	GEngine->CreateLevel<ATestGameMode>(GLevelName::TestLevel);
	GEngine->CreateLevel<ATitleGameMode>(GLevelName::TitleLevel);
	GEngine->CreateLevel<AIntroGameMode>(GLevelName::IntroLevel);
	GEngine->CreateLevel<AOverworldGameMode>(GLevelName::OverworldLevel);
	GEngine->CreateLevel<ABossFarmGameMode>(GLevelName::BossFarmLevel);
	GEngine->CreateLevel<ABossDragonGameMode>(GLevelName::BossDragonLevel);
	GEngine->CreateLevel<APlayResultGameMode>(GLevelName::PlayResultLevel);
	GEngine->CreateLevel<AEndingGameMode>(GLevelName::EndingLevel);
}


