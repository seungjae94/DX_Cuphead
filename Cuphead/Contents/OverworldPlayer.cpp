#include "PreCompile.h"
#include "OverworldPlayer.h"
#include "Constant.h"

AOverworldPlayer::AOverworldPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	Renderer->SetSprite(ImageName::OverworldCharDownIdle);
	Renderer->CreateAnimation(AnimName::DownIdle, ImageName::OverworldCharDownIdle, 0.1f);
	Renderer->CreateAnimation(AnimName::DownWalk, ImageName::OverworldCharDownWalk, 0.1f);
	Renderer->CreateAnimation(AnimName::RightIdle, ImageName::OverworldCharRightIdle, 0.1f);
	Renderer->CreateAnimation(AnimName::RightWalk, ImageName::OverworldCharRightWalk, 0.1f);
	Renderer->CreateAnimation(AnimName::UpIdle, ImageName::OverworldCharUpIdle, 0.1f);
	Renderer->CreateAnimation(AnimName::UpWalk, ImageName::OverworldCharUpWalk, 0.1f);
	Renderer->CreateAnimation(AnimName::RightDownIdle, ImageName::OverworldCharRightDownIdle, 0.1f);
	Renderer->CreateAnimation(AnimName::RightDownWalk, ImageName::OverworldCharRightDownWalk, 0.1f);
	Renderer->CreateAnimation(AnimName::RightUpIdle, ImageName::OverworldCharRightUpIdle, 0.1f);
	Renderer->CreateAnimation(AnimName::RightUpWalk, ImageName::OverworldCharRightUpWalk, 0.1f);

	InputOn();
	InitImageScaleMap();
}

AOverworldPlayer::~AOverworldPlayer()
{
}

void AOverworldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, 0.0f, 0.0f });

	ChangeAnimation(AnimName::DownIdle);
}

void AOverworldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_LEFT))
	{
		ChangeAnimation(AnimName::RightIdle);

		FVector Scale = Renderer->Transform.GetScale();
		Scale.X = -Scale.X;
		Renderer->Transform.SetScale(Scale);
	}

	if (true == IsDown(VK_RIGHT))
	{
		ChangeAnimation(AnimName::RightIdle);
	}

	if (true == IsDown(VK_UP))
	{
		ChangeAnimation(AnimName::UpIdle);
	}

	if (true == IsDown(VK_DOWN))
	{
		ChangeAnimation(AnimName::DownIdle);
	}
}

void AOverworldPlayer::InitImageScaleMap()
{
	ImageScaleMap[AnimName::DownIdle] = { 52.0f, 97.0f, 1.0f };
	ImageScaleMap[AnimName::DownWalk] = { 67.0f, 100.0f, 1.0f };
	ImageScaleMap[AnimName::RightDownIdle] = { 60.0f, 100.0f, 1.0f };
	ImageScaleMap[AnimName::RightDownWalk] = { 66.0f, 100.0f, 1.0f };
	ImageScaleMap[AnimName::RightIdle] = { 60.0f, 86.0f, 1.0f };
	ImageScaleMap[AnimName::RightWalk] = { 66.0f, 90.0f, 1.0f };
	ImageScaleMap[AnimName::UpIdle] = { 52.0f, 78.0f, 1.0f };
	ImageScaleMap[AnimName::UpWalk] = { 68.0f, 99.0f, 1.0f };
	ImageScaleMap[AnimName::RightUpIdle] = { 60.0f, 80.0f, 1.0f };
	ImageScaleMap[AnimName::RightUpWalk] = { 70.0f, 96.0f, 1.0f };
}

void AOverworldPlayer::ChangeAnimation(std::string _AnimName)
{
	Renderer->Transform.SetScale(ImageScaleMap[_AnimName]);
	Renderer->ChangeAnimation(_AnimName);
}
