#pragma once
#include "CupheadGameMode.h"

class ABook;

class AEndingGameMode : public ACupheadGameMode
{
	GENERATED_BODY(ACupheadGameMode)
public:
	AEndingGameMode();
	~AEndingGameMode();

	AEndingGameMode(const AEndingGameMode& _Other) = delete;
	AEndingGameMode(AEndingGameMode&& _Other) noexcept = delete;
	AEndingGameMode& operator=(const AEndingGameMode& _Other) = delete;
	AEndingGameMode& operator=(AEndingGameMode&& _Other) noexcept = delete;

protected:


private:
	ABook* Book = nullptr;
	UTextWidget* ThankYouForPlayingText = nullptr;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

