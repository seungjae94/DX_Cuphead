#include "PreCompile.h"
#include "OverworldGameMode.h"
#include "OverworldMap.h"
#include "OverworldPlayer.h"
#include "BossLevelEntrance.h"
#include "GameData.h"

AOverworldGameMode::AOverworldGameMode()
{
}

AOverworldGameMode::~AOverworldGameMode()
{
}

void AOverworldGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->SpawnActor<AOverworldPlayer>("Player").get();
	Map = GetWorld()->SpawnActor<AOverworldMap>("Map").get();

	UCollision* BlockCollision = nullptr;
	UCollision* ChangeLevelCollision = nullptr;

	ABossLevelEntrance* Farm = GetWorld()->SpawnActor<ABossLevelEntrance>("Farm").get();
	Farm->SetAnimation("overworld_farm", "overworld_farm.png", 1 / 12.0f);
	Farm->SetLevelName(GLevelName::BossFarmLevel);
	Farm->SetActorLocation({ -80.0f, -380.0f, 0.0f });
	Farm->SetPlayer(Player);
	Farm->SetFlagPosition({115.0f, -50.0f, 0.0f});
	BlockCollision = Farm->GetBlockCollision();
	ChangeLevelCollision = Farm->GetChangeLevelCollision();
	BlockCollision->SetScale({ 250.0f, 160.0f, 1.0f });
	BlockCollision->SetRotationDeg({ 0.0f, 0.0f, -35.0f });
	ChangeLevelCollision->SetScale({ 320.0f, 230.0f, 1.0f });
	ChangeLevelCollision->SetRotationDeg({ 0.0f, 0.0f, -35.0f });

	ABossLevelEntrance* Spire = GetWorld()->SpawnActor<ABossLevelEntrance>("Spire").get();
	Spire->SetAnimation("overworld_spire", "overworld_spire.png", 1 / 12.0f);
	Spire->SetLevelName(GLevelName::BossDragonLevel);
	Spire->SetActorLocation({ 350.0f, 550.0f, 0.0f });
	Spire->SetPlayer(Player);
	Spire->SetFlagPosition({ 90.0f, -150.0f, 0.0f });
	BlockCollision = Spire->GetBlockCollision();
	ChangeLevelCollision = Spire->GetChangeLevelCollision();
	BlockCollision->SetScale({ 120.0f, 200.0f, 1.0f });
	BlockCollision->SetPosition({0.0f, -125.0f, 0.0f});
	ChangeLevelCollision->SetScale({ 170.0f, 250.0f, 1.0f });
	ChangeLevelCollision->SetPosition({ 0.0f, -125.0f, 0.0f });

	InputOn();
}

void AOverworldGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AOverworldGameMode::LevelStart(ULevel* _PrevLevel)
{
	BgmPlayer = UEngineSound::SoundPlay("overworld_bgm.mp3");
	BgmPlayer.Loop(-1);

	if (nullptr == _PrevLevel)
	{
		return;
	}

	std::string PrevLevelName = _PrevLevel->GetName();

	if (PrevLevelName == GLevelName::PlayResultLevel)
	{
		++UGameData::ClearBossCount;
	}

	if (UGameData::BossCount <= UGameData::ClearBossCount)
	{
		// 엔딩 처리
		GEngine->ChangeLevel(GLevelName::EndingLevel);
	}
}

void AOverworldGameMode::LevelEnd(ULevel* _NextLevel)
{
	BgmPlayer.Off();
}
