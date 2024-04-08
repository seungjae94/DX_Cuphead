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

	USpriteRenderer* Background = nullptr;
};

