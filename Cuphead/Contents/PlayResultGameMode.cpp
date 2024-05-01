#include "PreCompile.h"
#include "PlayResultGameMode.h"
#include "PlayResultManager.h"

APlayResultGameMode::APlayResultGameMode()
{
}

APlayResultGameMode::~APlayResultGameMode()
{
}

void APlayResultGameMode::Refresh(
	float _PlaySeconds, int _RemainHp, int _ParryCount, int _ExUsageCount, int _Difficulty /*= 2*/)
{
	int Seconds = static_cast<int>(_PlaySeconds);
	int SecondPart = Seconds % 60;
	int MinutePart = Seconds / 60;
	std::string MinutePartStr = std::to_string(MinutePart);
	MinutePartStr.insert(MinutePartStr.begin(), 2 - MinutePartStr.length(), '0');
	std::string SecondPartStr = std::to_string(SecondPart);
	Manager->ResultMinute->SetText(MinutePartStr);
	Manager->ResultSecond->SetText(SecondPartStr);

	Manager->ResultHpBonus->SetText(std::to_string(_RemainHp));
	Manager->ResultParry->SetText(std::to_string(_ParryCount));
	Manager->ResultSuperMeter->SetText(std::to_string(_ExUsageCount));
	
	if (2 == _Difficulty)
	{
		Manager->ResultSkillLevelStar0->SetSprite("result_board_full_star.png");
		Manager->ResultSkillLevelStar1->SetSprite("result_board_full_star.png");
	}
}

std::string APlayResultGameMode::GetPrevLevelName() const
{
	return PrevLevelName;
}

void APlayResultGameMode::BeginPlay()
{
	Super::BeginPlay();

	Manager = GetWorld()->SpawnActor<APlayResultManager>("Manager").get();
}

void APlayResultGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	WaitTimer = WaitTime;

	if (nullptr == _PrevLevel)
	{
		return;
	}

	PrevLevelName = _PrevLevel->GetName();
}

void APlayResultGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	WaitTimer -= _DeltaTime;

	if (WaitTimer > 0.0f)
	{
		return;
	}

	if (true == UEngineInput::IsDown('Z'))
	{
		WaitTimer = 3600.0f;
		ChangeLevelWithFadeEffect(GLevelName::OverworldLevel);
	}
}
