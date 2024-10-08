#pragma once

class ANoise;

enum class EFadeInState
{
	None,
	First,
	Fading
};

enum class EFadeOutState
{
	None,
	First,
	Fading
};

class ACupheadGameMode : public AGameMode
{
	GENERATED_BODY(AActor)
public:
	ACupheadGameMode();
	~ACupheadGameMode();

	ACupheadGameMode(const ACupheadGameMode& _Other) = delete;
	ACupheadGameMode(ACupheadGameMode&& _Other) noexcept = delete;
	ACupheadGameMode& operator=(const ACupheadGameMode& _Other) = delete;
	ACupheadGameMode& operator=(ACupheadGameMode&& _Other) noexcept = delete;

	void ChangeLevelWithFadeEffect(std::string_view _NextLevelName);

protected:
	UImage* Noise = nullptr;
	UImage* FadeIn = nullptr;
	UImage* FadeOut = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	bool IsFadeIn() const;
	bool IsFadeOut() const;
private:
	// 페이드 효과
	EFadeInState IsFadeInChecker = EFadeInState::None;
	EFadeOutState IsFadeOutChecker = EFadeOutState::None;
	void FadeInStart();
	void FadeOutStart();
	std::string NextLevelName;
private:
	// 레벨 변경
	bool IsChanging = false;
};

