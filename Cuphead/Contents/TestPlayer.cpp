#include "PreCompile.h"
#include "TestPlayer.h"
#include <EngineBase/EngineMath.h>

ATestPlayer::ATestPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetSprite("test_rect.png");
}

ATestPlayer::~ATestPlayer()
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Renderer->Transform.SetPosition(FVector::Zero);
	Renderer->Transform.SetScale({ 50.0f, 50.0f, 1.0f });
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//if (true == UEngineInput::IsPress(VK_UP))
	//{
	//	AddActorLocation(FVector::Up * Speed * _DeltaTime);
	//}
	//if (true == UEngineInput::IsPress(VK_DOWN))
	//{
	//	AddActorLocation(FVector::Down * Speed * _DeltaTime);
	//}
	//if (true == UEngineInput::IsPress(VK_LEFT))
	//{
	//	AddActorLocation(FVector::Left * Speed * _DeltaTime);
	//}
	//if (true == UEngineInput::IsPress(VK_RIGHT))
	//{
	//	AddActorLocation(FVector::Right * Speed * _DeltaTime);
	//}

	//if (true == UEngineInput::IsPress('1'))
	//{
	//	Color.R -= _DeltaTime;
	//}
	//if (true == UEngineInput::IsPress('2'))
	//{
	//	Color.R += _DeltaTime;
	//}
}

