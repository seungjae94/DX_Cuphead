#include "PreCompile.h"
#include "CupheadGameMode.h"

ACupheadGameMode::ACupheadGameMode()
{
}

ACupheadGameMode::~ACupheadGameMode()
{
}

void ACupheadGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<ACamera> Camera = GetWorld()->GetMainCamera();
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
	FadeIn->CreateAnimation("none", "none.png", 1 / 24.0f, false);
	FadeIn->SetScale({ 1280.0f, 720.0f });
	FadeIn->SetPosition(FVector::Zero);
	FadeIn->SetActive(false);

	FadeOut = CreateWidget<UImage>(GetWorld(), "FadeOut");
	FadeOut->AddToViewPort(ERenderingOrder::Fade);
	FadeOut->CreateAnimation("fade_out", "fade_out", 1 / 24.0f, false);
	FadeOut->CreateAnimation("none", "none.png", 1 / 24.0f, false);
	FadeOut->SetScale({ 1280.0f, 720.0f });
	FadeOut->SetPosition(FVector::Zero);
	FadeOut->SetActive(false);

	GetWorld()->GetLastTarget()->AddEffect<UBlurEffect>();
}

void ACupheadGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (EFadeInState::None != IsFadeInChecker)
	{
		if (EFadeInState::First == IsFadeInChecker)
		{
			IsFadeInChecker = EFadeInState::Fading;
		}
		else if (true == FadeIn->IsCurAnimationEnd())
		{
			IsFadeInChecker = EFadeInState::None;
			FadeIn->SetActive(false);
		}
	}

	if (EFadeOutState::None != IsFadeOutChecker)
	{
		if (EFadeOutState::First == IsFadeOutChecker)
		{
			IsFadeOutChecker = EFadeOutState::Fading;
		}
		else if (true == FadeOut->IsCurAnimationEnd())
		{
			GEngine->ChangeLevel(NextLevelName);
			NextLevelName = "";
			IsChanging = false;
		}
	}
}

void ACupheadGameMode::ChangeLevelWithFadeEffect(std::string_view _NextLevelName)
{
	if (true == IsChanging)
	{
		return;
	}

	NextLevelName = _NextLevelName;
	FadeOutStart();
	IsChanging = true;
}

void ACupheadGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);


}

void ACupheadGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	if (EFadeOutState::Fading == IsFadeOutChecker)
	{
		IsFadeOutChecker = EFadeOutState::None;

		FadeOut->SetActive(false);

		ACupheadGameMode* NextGameMode = dynamic_pointer_cast<ACupheadGameMode>(_NextLevel->GetGameMode()).get();
		NextGameMode->FadeInStart();
	}
}

bool ACupheadGameMode::IsFadeIn() const
{
	return IsFadeInChecker != EFadeInState::None;
}

bool ACupheadGameMode::IsFadeOut() const
{
	return IsFadeOutChecker != EFadeOutState::None;
}

void ACupheadGameMode::FadeInStart()
{
	IsFadeInChecker = EFadeInState::First;
	FadeIn->SetActive(true);
	FadeOut->SetActive(false);
	FadeIn->ChangeAnimation("none");
	FadeIn->ChangeAnimation("fade_in");
}

void ACupheadGameMode::FadeOutStart()
{
	IsFadeOutChecker = EFadeOutState::First;
	FadeOut->SetActive(true);
	FadeIn->SetActive(false);
	FadeOut->ChangeAnimation("none");
	FadeOut->ChangeAnimation("fade_out");
}
