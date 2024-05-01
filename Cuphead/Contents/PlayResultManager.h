#pragma once

class APlayResultGameMode;

class APlayResultManager : public AActor
{
	GENERATED_BODY(AActor)
	friend APlayResultGameMode;
public:
	APlayResultManager();
	~APlayResultManager();

	APlayResultManager(const APlayResultManager& _Other) = delete;
	APlayResultManager(APlayResultManager&& _Other) noexcept = delete;
	APlayResultManager& operator=(const APlayResultManager& _Other) = delete;
	APlayResultManager& operator=(APlayResultManager&& _Other) noexcept = delete;

protected:


private:
	void BeginPlay() override;
private:
	UImage* Background = nullptr;
	UImage* Board = nullptr;
	UImage* TitleTheResults = nullptr;
	UImage* TitleStudioMDHR = nullptr;
	UImage* CupheadImage = nullptr;
	UImage* CupheadName = nullptr;
	

	UTextWidget* TitleTime = nullptr;
	UTextWidget* TitleHpBonus = nullptr;
	UTextWidget* TitleParry = nullptr;
	UTextWidget* TitleSuperMeter = nullptr;
	UTextWidget* TitleSkillLevel = nullptr;
	UTextWidget* TitleGrade = nullptr;
	UTextWidget* TitleGradeDots = nullptr;
	
	UTextWidget* ResultMinute = nullptr;
	UTextWidget* ResultTimeColon = nullptr;
	UTextWidget* ResultSecond = nullptr;

	UTextWidget* ResultHpBonus = nullptr;
	UTextWidget* ResultHpBonusSlash = nullptr;
	UTextWidget* ResultMaxHpBonus = nullptr;

	UTextWidget* ResultParry = nullptr;
	UTextWidget* ResultParrySlash = nullptr;
	UTextWidget* ResultMaxParry = nullptr;

	UTextWidget* ResultSuperMeter = nullptr;
	UTextWidget* ResultSuperMeterSlash = nullptr;
	UTextWidget* ResultMaxSuperMeter = nullptr;

	UImage* ResultSkillLevelStar0 = nullptr;
	UImage* ResultSkillLevelStar1 = nullptr;

	UTextWidget* ResultGrade = nullptr;
};

