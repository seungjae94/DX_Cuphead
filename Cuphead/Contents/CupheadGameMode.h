#pragma once

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

protected:
	void BeginPlay() override;

private:
};
