#include "PreCompile.h"
#include "CupheadGameMode.h"

ACupheadGameMode::ACupheadGameMode()
{
}

ACupheadGameMode::~ACupheadGameMode()
{
}

void ACupheadGameMode::ChangeLevelWithFadeEffect(std::string_view _NextLevelName)
{
	NextLevelName = _NextLevelName;
	FadeOutStart();
}

void ACupheadGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	Noise = CreateWidget<UImage>(GetWorld(), "Noise");
	Noise->AddToViewPort(ERenderingOrder::Noise);
	Noise->CreateAnimation("common_noise", "common_noise", 1 / 24.0f, true);
	Noise->ChangeAnimation("common_noise");
	Noise->SetScale({ 1280.0f, 720.0f });
	Noise->SetPosition(FVector::Zero);

	FadeIn = CreateWidget<UImage>(GetWorld(), "FadeIn");
	FadeIn->AddToViewPort(ERenderingOrder::Fade);
	FadeIn->CreateAnimation("fade_in", "fade_in", 1 / 24.0f, false);
	FadeIn->SetScale({ 1280.0f, 720.0f });
	FadeIn->SetPosition(FVector::Zero);
	FadeIn->SetActive(false);

	FadeOut = CreateWidget<UImage>(GetWorld(), "FadeOut");
	FadeOut->AddToViewPort(ERenderingOrder::Fade);
	FadeOut->CreateAnimation("fade_out", "fade_out", 1 / 24.0f, false);
	FadeOut->SetScale({ 1280.0f, 720.0f });
	FadeOut->SetPosition(FVector::Zero);
	FadeOut->SetActive(false);

	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void ACupheadGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsFadeIn)
	{
		if (true == FadeIn->IsCurAnimationEnd())
		{
			IsFadeIn = false;
			FadeIn->SetActive(false);
		}
	}

	if (true == IsFadeOut)
	{
		if (true == FadeOut->IsCurAnimationEnd())
		{
			FadeOut->SetActive(false);
			GEngine->ChangeLevel(NextLevelName);
			NextLevelName = "";
		}
	}
}

void ACupheadGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);


}

void ACupheadGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	if (true == IsFadeOut)
	{
		IsFadeOut = false;
		
		ACupheadGameMode* NextGameMode = dynamic_pointer_cast<ACupheadGameMode>(_NextLevel->GetGameMode()).get();
		NextGameMode->FadeInStart();
	}
}

void ACupheadGameMode::FadeInStart()
{
	IsFadeIn = true;
	FadeIn->SetActive(true);
	FadeIn->ChangeAnimation("fade_in");
}

void ACupheadGameMode::FadeOutStart()
{
	IsFadeOut = true;
	FadeOut->SetActive(true);
	FadeOut->ChangeAnimation("fade_out");
}
