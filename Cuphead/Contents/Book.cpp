#include "PreCompile.h"
#include "Book.h"

ABook::ABook()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	BookRenderer = CreateDefaultSubObject<USpriteRenderer>("BookRenderer");
	BookRenderer->SetupAttachment(Root);
	BookRenderer->SetOrder(ERenderingOrder::Back0);
	BookRenderer->SetAutoSize(1.0f, true);
}

ABook::~ABook()
{
}

void ABook::Init(std::string_view _BookNamePrefix, int _MaxBookIndex)
{
	BookNamePrefix = _BookNamePrefix;
	MaxBookIndex = _MaxBookIndex;

	for (int i = 0; i <= MaxBookIndex; ++i)
	{
		std::string BookName = BookNamePrefix + std::to_string(i);
		BookRenderer->CreateAnimation(BookName, BookName, 1 / 24.0f, false);
		BookRenderer->SetFrameCallback(BookName, 0, [this]() {
			AnimationEnd = false;
			});
		BookRenderer->SetLastFrameCallback(BookName, [this]() {
			AnimationEnd = true;
			});
	}

	std::string StartBookName = BookNamePrefix + std::to_string(0);
	BookRenderer->ChangeAnimation(StartBookName);
}

int ABook::GetBookIndex() const
{
	return BookIndex;
}

void ABook::IncBookIndex()
{
	++BookIndex;

	if (BookIndex > MaxBookIndex)
	{
		return;
	}

	int RandomInt = Random.RandomInt(1, 3);
	UEngineSound::SoundPlay("pageturn_" + std::to_string(RandomInt) + ".mp3");
	BookRenderer->ChangeAnimation(BookNamePrefix + std::to_string(BookIndex));
}

bool ABook::IsMaxBookIndex() const
{
	return BookIndex == MaxBookIndex;
}

bool ABook::OverMaxBookIndex() const
{
	return BookIndex > MaxBookIndex;
}

bool ABook::IsCurAnimationEnd() const
{
	return AnimationEnd;
}
