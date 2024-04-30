#include "PreCompile.h"
#include "PlayResultManager.h"

APlayResultManager::APlayResultManager()
{
}

APlayResultManager::~APlayResultManager()
{
}

void APlayResultManager::BeginPlay()
{
	Super::BeginPlay();

	Background = CreateWidget<UImage>(GetWorld(), "Background");
	Background->SetSprite("result_back.png");
	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	Background->SetScale(WindowScale * 2.0f);
	Background->AddToViewPort(0);

	Board = CreateWidget<UImage>(GetWorld(), "Board");
	Board->SetSprite("result_board.png");
	Board->SetAutoSize(1.0f, true);
	Board->AddToViewPort(1);

	TitleTheResults = CreateWidget<UImage>(GetWorld(), "TitleTheResults");
	TitleTheResults->SetSprite("the_result_text");
	TitleTheResults->CreateAnimation("the_result_text", "the_result_text", 1 / 24.0f, true);
	TitleTheResults->ChangeAnimation("the_result_text");
	TitleTheResults->SetAutoSize(1.0f, true);
	TitleTheResults->AddToViewPort(1);
		
	TitleStudioMDHR = CreateWidget<UImage>(GetWorld(), "TitleStudioMDHR");
	TitleStudioMDHR->SetSprite("result_mdhr_title.png");
	TitleStudioMDHR->SetAutoSize(1.0f, true);
	TitleStudioMDHR->AddToViewPort(1);

	CupheadImage = CreateWidget<UImage>(GetWorld(), "CupheadImage");
	CupheadImage->SetSprite("result_cuphead_idle");
	CupheadImage->CreateAnimation("result_cuphead_idle", "result_cuphead_idle", 1 / 24.0f, true);
	CupheadImage->ChangeAnimation("result_cuphead_idle");
	CupheadImage->SetAutoSize(1.0f, true);
	CupheadImage->SetPosition({ -300.0f, 0.0f, 0.0f });
	CupheadImage->AddToViewPort(1);

	CupheadName = CreateWidget<UImage>(GetWorld(), "CupheadName");
	CupheadName->SetSprite("result_cuphead_text.png");
	CupheadName->SetAutoSize(1.0f, true);
	CupheadName->AddToViewPort(1);

	//UTextWidget* TitleTime = nullptr;
	//UTextWidget* TitleHpBonus = nullptr;
	//UTextWidget* TitleParry = nullptr;
	//UTextWidget* TitleSuperMeter = nullptr;
	//UTextWidget* TitleSkillLevel = nullptr;
	//UTextWidget* TitleGrade = nullptr;
	//UTextWidget* TitleGradeDots = nullptr;

	//UTextWidget* ResultTime = nullptr;
	//UTextWidget* ResultTimeSlash = nullptr;
	//UTextWidget* ResultMaxTime = nullptr;

	//UTextWidget* ResultHpBonus = nullptr;
	//UTextWidget* ResultHpBonusSlash = nullptr;
	//UTextWidget* ResultMaxHpBonus = nullptr;

	//UTextWidget* ResultParry = nullptr;
	//UTextWidget* ResultParrySlash = nullptr;
	//UTextWidget* ResultMaxParry = nullptr;

	//UTextWidget* ResultSuperMeter = nullptr;
	//UTextWidget* ResultSuperMeterSlash = nullptr;
	//UTextWidget* ResultMaxSuperMeter = nullptr;

	//UImage* ResultSkillLevelStar0 = nullptr;
	//UImage* ResultSkillLevelStar1 = nullptr;

	//UTextWidget* ResultGrade = nullptr;
}
