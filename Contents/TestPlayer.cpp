#include "PreCompile.h"
#include "TestPlayer.h"
#include <EngineBase/EngineMath.h>

ATestPlayer::ATestPlayer()
{
	Renderer = CreateDefaultSubObject<URenderer>("Renderer");
	Renderer->SetMesh("Rect");
	Renderer->SetMaterial("2DImage");
}

ATestPlayer::~ATestPlayer()
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1280.0f, 720.0f, 1.0f));
	Renderer->Resources->SettingTexture("Image", "title_screen_background.png", "POINT");
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * Speed * _DeltaTime);
	}
	if (true == UEngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * Speed * _DeltaTime);
	}
	if (true == UEngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * Speed * _DeltaTime);
	}
	if (true == UEngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * Speed * _DeltaTime);
	}

	if (true == UEngineInput::IsPress('1'))
	{
		Color.R -= _DeltaTime;
	}
	if (true == UEngineInput::IsPress('2'))
	{
		Color.R += _DeltaTime;
	}
}

