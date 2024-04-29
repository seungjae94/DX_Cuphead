#include "PreCompile.h"
#include "EndingGameMode.h"
#include "Book.h"

AEndingGameMode::AEndingGameMode()
{
}

AEndingGameMode::~AEndingGameMode()
{
}

void AEndingGameMode::BeginPlay()
{
	Super::BeginPlay();

	Book = GetWorld()->SpawnActor<ABook>("Book").get();
	Book->Init("ending_book_", 6);

	InputOn();
}

void AEndingGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (false == Book->IsCurAnimationEnd())
	{
		return;
	}

	if (true == IsDown('Z'))
	{
		Book->IncBookIndex();

		if (true == Book->OverMaxBookIndex())
		{
			// TODO: 게임 종료
			return;
		}
	}
}
