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
	Board->SetPosition({150.0f, -75.0f, 0.0f});
	Board->AddToViewPort(1);

	TitleTheResults = CreateWidget<UImage>(GetWorld(), "TitleTheResults");
	TitleTheResults->SetSprite("the_result_text");
	TitleTheResults->CreateAnimation("the_result_text", "the_result_text", 1 / 18.0f, true);
	TitleTheResults->ChangeAnimation("the_result_text");
	TitleTheResults->SetAutoSize(1.0f, true);
	TitleTheResults->SetPosition({ 0.0f, 280.0f, 0.0f });
	TitleTheResults->AddToViewPort(1);
		
	TitleStudioMDHR = CreateWidget<UImage>(GetWorld(), "TitleStudioMDHR");
	TitleStudioMDHR->SetSprite("result_mdhr_title.png");
	TitleStudioMDHR->SetAutoSize(1.0f, true);
	TitleStudioMDHR->SetPosition({ 0.0f, 200.0f, 0.0f });
	TitleStudioMDHR->AddToViewPort(1);

	CupheadImage = CreateWidget<UImage>(GetWorld(), "CupheadImage");
	CupheadImage->SetSprite("result_cuphead_idle");
	CupheadImage->CreateAnimation("result_cuphead_idle", "result_cuphead_idle", std::vector<float>(12, 1 / 18.0f), {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1}, true);
	CupheadImage->ChangeAnimation("result_cuphead_idle");
	CupheadImage->SetAutoSize(1.0f, true);
	CupheadImage->SetPosition({ -300.0f, -50.0f, 0.0f });
	CupheadImage->AddToViewPort(1);

	CupheadName = CreateWidget<UImage>(GetWorld(), "CupheadName");
	CupheadName->SetSprite("result_cuphead_text.png");
	CupheadName->SetAutoSize(1.0f, true);
	CupheadName->SetPosition({ -300.0f, -300.0f, 0.0f });
	CupheadName->AddToViewPort(1);

	TitleTime = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleTime->SetFont("±¼¸²");
	TitleTime->SetColor(Color8Bit::White);
	TitleTime->SetText("TIME");
	TitleTime->SetScale(50.0f);
	TitleTime->AddToViewPort(2);

	TitleHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleParry = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleSkillLevel = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleGrade = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleGradeDots = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultTime = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultTimeSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxTime = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultHpBonusSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultParry = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultParrySlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxParry = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultSuperMeterSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");

	//UImage* ResultSkillLevelStar0 = nullptr;
	//UImage* ResultSkillLevelStar1 = nullptr;

	//UTextWidget* ResultGrade = nullptr;
}
