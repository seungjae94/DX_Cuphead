#pragma once

class ANoise : public AActor
{
	GENERATED_BODY(AActor)
public:
	ANoise();
	~ANoise();

	ANoise(const ANoise& _Other) = delete;
	ANoise(ANoise&& _Other) noexcept = delete;
	ANoise& operator=(const ANoise& _Other) = delete;
	ANoise& operator=(ANoise&& _Other) noexcept = delete;

protected:


private:
	USpriteRenderer* Renderer = nullptr;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

