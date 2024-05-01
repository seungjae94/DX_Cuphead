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
			// TODO: ���� ����
			return;
		}
		return;
	}

	if (nullptr == ThankYouForPlayingText && true == Book->IsMaxBookIndex())
	{
		ThankYouForPlayingText = CreateWidget<UTextWidget>(GetWorld(), "LastText");
		ThankYouForPlayingText->SetFont("����");
		ThankYouForPlayingText->SetScale(80.0f);
		ThankYouForPlayingText->SetColor(Color8Bit::Yellow);
		ThankYouForPlayingText->SetPosition({ 0.0f, 100.0f });
		ThankYouForPlayingText->SetText("�÷��� ���ּż� �����մϴ�!");
		ThankYouForPlayingText->AddToViewPort(0);
	}
}
