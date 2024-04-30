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

	std::string FontName = "±¼¸²";
	float FontSize = 40.0f;

	TitleTime = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleTime->SetFont(FontName);
	TitleTime->SetColor(Color8Bit::White);
	TitleTime->SetText(std::string("TIME") + std::string(14, '.'));
	TitleTime->SetScale(FontSize);
	TitleTime->SetPosition({90.0f, 80.0f, 0.0f});
	TitleTime->AddToViewPort(2);

	ResultTime = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultTime->SetFont(FontName);
	ResultTime->SetColor(Color8Bit::Yellow);
	ResultTime->SetText("01");
	ResultTime->SetScale(FontSize);
	ResultTime->SetPosition({ 260.0f, 80.0f, 0.0f });
	ResultTime->AddToViewPort(2);

	ResultTimeSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultTimeSlash->SetFont(FontName);
	ResultTimeSlash->SetColor(Color8Bit::White);
	ResultTimeSlash->SetText(":");
	ResultTimeSlash->SetScale(FontSize);
	ResultTimeSlash->SetPosition({ 290.0f, 80.0f, 0.0f });
	ResultTimeSlash->AddToViewPort(2);

	ResultMaxTime = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxTime->SetFont(FontName);
	ResultMaxTime->SetColor(Color8Bit::Yellow);
	ResultMaxTime->SetText("09");
	ResultMaxTime->SetScale(FontSize);
	ResultMaxTime->SetPosition({ 325.0f, 80.0f, 0.0f });
	ResultMaxTime->AddToViewPort(2);

	TitleHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleHpBonus->SetFont(FontName);
	TitleHpBonus->SetColor(Color8Bit::White);
	TitleHpBonus->SetText(std::string("HP BONUS") + std::string(9, '.'));
	TitleHpBonus->SetScale(FontSize);
	TitleHpBonus->SetPosition({ 113.0f, 30.0f, 0.0f });
	TitleHpBonus->AddToViewPort(2);

	ResultHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultHpBonus->SetFont(FontName);
	ResultHpBonus->SetColor(Color8Bit::Yellow);
	ResultHpBonus->SetText(std::to_string(3));
	ResultHpBonus->SetScale(FontSize);
	ResultHpBonus->SetPosition({ 300.0f, 30.0f, 0.0f });
	ResultHpBonus->AddToViewPort(2);

	ResultHpBonusSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultHpBonusSlash->SetFont(FontName);
	ResultHpBonusSlash->SetColor(Color8Bit::White);
	ResultHpBonusSlash->SetText("/");
	ResultHpBonusSlash->SetScale(FontSize);
	ResultHpBonusSlash->SetPosition({ 318.0f, 30.0f, 0.0f });
	ResultHpBonusSlash->AddToViewPort(2);

	ResultMaxHpBonus = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxHpBonus->SetFont(FontName);
	ResultMaxHpBonus->SetColor(Color8Bit::Yellow);
	ResultMaxHpBonus->SetText(std::to_string(3));
	ResultMaxHpBonus->SetScale(FontSize);
	ResultMaxHpBonus->SetPosition({ 336.0f, 30.0f, 0.0f });
	ResultMaxHpBonus->AddToViewPort(2);

	TitleParry = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleParry->SetFont(FontName);
	TitleParry->SetColor(Color8Bit::White);
	TitleParry->SetText(std::string("PARRY") + std::string(15, '.'));
	TitleParry->SetScale(FontSize);
	TitleParry->SetPosition({ 113.0f, -20.0f, 0.0f });
	TitleParry->AddToViewPort(2);

	ResultParry = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultParry->SetFont(FontName);
	ResultParry->SetColor(Color8Bit::Yellow);
	ResultParry->SetText(std::to_string(3));
	ResultParry->SetScale(FontSize);
	ResultParry->SetPosition({ 300.0f, -20.0f, 0.0f });
	ResultParry->AddToViewPort(2);

	ResultParrySlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultParrySlash->SetFont(FontName);
	ResultParrySlash->SetColor(Color8Bit::White);
	ResultParrySlash->SetText("/");
	ResultParrySlash->SetScale(FontSize);
	ResultParrySlash->SetPosition({ 318.0f, -20.0f, 0.0f });
	ResultParrySlash->AddToViewPort(2);

	ResultMaxParry = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxParry->SetFont(FontName);
	ResultMaxParry->SetColor(Color8Bit::Yellow);
	ResultMaxParry->SetText(std::to_string(3));
	ResultMaxParry->SetScale(FontSize);
	ResultMaxParry->SetPosition({ 336.0f, -20.0f, 0.0f });
	ResultMaxParry->AddToViewPort(2);

	TitleSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleSuperMeter->SetFont(FontName);
	TitleSuperMeter->SetColor(Color8Bit::White);
	TitleSuperMeter->SetText(std::string("SUPER METER") + std::string(4, '.'));
	TitleSuperMeter->SetScale(FontSize);
	TitleSuperMeter->SetPosition({ 114.0f, -70.0f, 0.0f });
	TitleSuperMeter->AddToViewPort(2);

	ResultSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultSuperMeter->SetFont(FontName);
	ResultSuperMeter->SetColor(Color8Bit::Yellow);
	ResultSuperMeter->SetText(std::to_string(6));
	ResultSuperMeter->SetScale(FontSize);
	ResultSuperMeter->SetPosition({ 300.0f, -70.0f, 0.0f });
	ResultSuperMeter->AddToViewPort(2);

	ResultSuperMeterSlash = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultSuperMeterSlash->SetFont(FontName);
	ResultSuperMeterSlash->SetColor(Color8Bit::White);
	ResultSuperMeterSlash->SetText("/");
	ResultSuperMeterSlash->SetScale(FontSize);
	ResultSuperMeterSlash->SetPosition({ 318.0f, -70.0f, 0.0f });
	ResultSuperMeterSlash->AddToViewPort(2);

	ResultMaxSuperMeter = CreateWidget<UTextWidget>(GetWorld(), "");
	ResultMaxSuperMeter->SetFont(FontName);
	ResultMaxSuperMeter->SetColor(Color8Bit::Yellow);
	ResultMaxSuperMeter->SetText(std::to_string(6));
	ResultMaxSuperMeter->SetScale(FontSize);
	ResultMaxSuperMeter->SetPosition({ 336.0f, -70.0f, 0.0f });
	ResultMaxSuperMeter->AddToViewPort(2);

	TitleSkillLevel = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleSkillLevel->SetFont(FontName);
	TitleSkillLevel->SetColor(Color8Bit::White);
	TitleSkillLevel->SetText(std::string("SKILL LEVEL") + std::string(7, '.'));
	TitleSkillLevel->SetScale(FontSize);
	TitleSkillLevel->SetPosition({ 115.0f, -120.0f, 0.0f });
	TitleSkillLevel->AddToViewPort(2);

	ResultSkillLevelStar0 = CreateWidget<UImage>(GetWorld(), "Star0");
	ResultSkillLevelStar0->SetSprite("result_board_full_star.png");
	ResultSkillLevelStar0->SetAutoSize(1.0f, true);
	ResultSkillLevelStar0->SetPosition({ 305.0f, -125.0f, 0.0f });
	ResultSkillLevelStar0->AddToViewPort(2);

	ResultSkillLevelStar1 = CreateWidget<UImage>(GetWorld(), "Star1");
	ResultSkillLevelStar1->SetSprite("result_board_full_star.png");
	ResultSkillLevelStar1->SetAutoSize(1.0f, true);
	ResultSkillLevelStar1->SetPosition({ 335.0f, -125.0f, 0.0f });
	ResultSkillLevelStar1->AddToViewPort(2);

	TitleGrade = CreateWidget<UTextWidget>(GetWorld(), "");
	TitleGradeDots = CreateWidget<UTextWidget>(GetWorld(), "");

	//UTextWidget* ResultGrade = nullptr;
}
