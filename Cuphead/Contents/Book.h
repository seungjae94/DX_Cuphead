#pragma once

class ABook : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABook();
	~ABook();

	ABook(const ABook& _Other) = delete;
	ABook(ABook&& _Other) noexcept = delete;
	ABook& operator=(const ABook& _Other) = delete;
	ABook& operator=(ABook&& _Other) noexcept = delete;

	void Init(std::string_view _BookNamePrefix, int _MaxBookIndex);
	int GetBookIndex() const;
	void IncBookIndex();
	bool IsMaxBookIndex() const;
	bool OverMaxBookIndex() const;
	bool IsCurAnimationEnd() const;

protected:


private:
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* BookRenderer = nullptr;
	std::string BookNamePrefix;
	UEngineRandom Random;

	int MaxBookIndex = 0;
	int BookIndex = 0;
	bool AnimationEnd = false;
};

