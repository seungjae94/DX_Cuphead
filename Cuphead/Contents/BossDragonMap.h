#pragma once

class ABossDragonMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABossDragonMap();
	~ABossDragonMap();

	ABossDragonMap(const ABossDragonMap& _Other) = delete;
	ABossDragonMap(ABossDragonMap&& _Other) noexcept = delete;
	ABossDragonMap& operator=(const ABossDragonMap& _Other) = delete;
	ABossDragonMap& operator=(ABossDragonMap&& _Other) noexcept = delete;

protected:


private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// ÄÄÆ÷³ÍÆ®
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Background0 = nullptr;
	USpriteRenderer* Background1 = nullptr;

private:
	FVector MapScale;
	const float BackgroundSpeed = 200.0f;
private:
	bool ShowColMap = false;
};

