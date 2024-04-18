#pragma once

class ABossFarmMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ABossFarmMap();
	~ABossFarmMap();

	// delete Function
	ABossFarmMap(const ABossFarmMap& _Other) = delete;
	ABossFarmMap(ABossFarmMap&& _Other) noexcept = delete;
	ABossFarmMap& operator=(const ABossFarmMap& _Other) = delete;
	ABossFarmMap& operator=(ABossFarmMap&& _Other) noexcept = delete;

protected:

private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Back0 = nullptr;
	USpriteRenderer* Back1 = nullptr;
	USpriteRenderer* Back3 = nullptr;
	USpriteRenderer* Back4 = nullptr;
	USpriteRenderer* Front = nullptr;
	USpriteRenderer* Col = nullptr;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	bool ShowColMap = false;
	void ShowPixelColMapCheckBox();
	void ToggleColMap();
};

