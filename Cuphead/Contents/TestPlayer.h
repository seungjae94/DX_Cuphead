#pragma once
#include <EngineCore/Actor.h>

class ATestPlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ATestPlayer();
	~ATestPlayer();

	// delete Function
	ATestPlayer(const ATestPlayer& _Other) = delete;
	ATestPlayer(ATestPlayer&& _Other) noexcept = delete;
	ATestPlayer& operator=(const ATestPlayer& _Other) = delete;
	ATestPlayer& operator=(ATestPlayer&& _Other) noexcept = delete;

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;

private:
	float4 Color;
	const float Speed = 200.0f;
};

