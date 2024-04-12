#pragma once

class APotato : public AActor
{
	GENERATED_BODY(AActor)
public:
	APotato();
	~APotato();

	APotato(const APotato& _Other) = delete;
	APotato(APotato&& _Other) noexcept = delete;
	APotato& operator=(const APotato& _Other) = delete;
	APotato& operator=(APotato&& _Other) noexcept = delete;

protected:


private:
	// ÄÄÆ÷³ÍÆ®
	UDefaultSceneComponent* Root = nullptr;

};

