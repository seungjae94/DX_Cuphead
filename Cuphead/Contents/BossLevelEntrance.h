#pragma once

class AOverworldPlayer;

class ABossLevelEntrance : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABossLevelEntrance();
	~ABossLevelEntrance();

	ABossLevelEntrance(const ABossLevelEntrance& _Other) = delete;
	ABossLevelEntrance(ABossLevelEntrance&& _Other) noexcept = delete;
	ABossLevelEntrance& operator=(const ABossLevelEntrance& _Other) = delete;
	ABossLevelEntrance& operator=(ABossLevelEntrance&& _Other) noexcept = delete;

	void SetLevelName(std::string_view _LevelName);
	void SetAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Inter);

	UCollision* GetBlockCollision();
	UCollision* GetChangeLevelCollision();
	void SetPlayer(AOverworldPlayer* _Player);

protected:

private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugUpdate(float _DeltaTime);

	AOverworldPlayer* Player = nullptr;
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* BlockCollision = nullptr;
	UCollision* ChangeLevelCollision = nullptr;
	std::string LevelName;
};
