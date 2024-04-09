#include "PreCompile.h"
#include "OverworldPlayer.h"

AOverworldPlayer::AOverworldPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

AOverworldPlayer::~AOverworldPlayer()
{
}

void AOverworldPlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, 0.0f, 0.0f });
	Renderer->SetSprite(ImageName::OverworldCharDownIdle);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderingOrder::Character);

	CreateAnimation(AnimName::OverworldCharDownIdle, ImageName::OverworldCharDownIdle, 0.067f);
	CreateAnimation(AnimName::OverworldCharDownWalk, ImageName::OverworldCharDownWalk, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightIdle, ImageName::OverworldCharRightIdle, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightWalk, ImageName::OverworldCharRightWalk, 0.067f);
	CreateAnimation(AnimName::OverworldCharUpIdle, ImageName::OverworldCharUpIdle, 0.067f);
	CreateAnimation(AnimName::OverworldCharUpWalk, ImageName::OverworldCharUpWalk, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightDownIdle, ImageName::OverworldCharRightDownIdle, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightDownWalk, ImageName::OverworldCharRightDownWalk, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightUpIdle, ImageName::OverworldCharRightUpIdle, 0.067f);
	CreateAnimation(AnimName::OverworldCharRightUpWalk, ImageName::OverworldCharRightUpWalk, 0.067f);
	ChangeAnimation(AnimName::OverworldCharDownIdle);

	InputOn();
}

void AOverworldPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == IsDown(VK_LEFT))
	{
		ChangeAnimation(AnimName::OverworldCharRightIdle);
	}

	if (true == IsDown(VK_RIGHT))
	{
		ChangeAnimation(AnimName::OverworldCharRightIdle);
	}

	if (true == IsDown(VK_UP))
	{
		ChangeAnimation(AnimName::OverworldCharUpIdle);
	}

	if (true == IsDown(VK_DOWN))
	{
		ChangeAnimation(AnimName::OverworldCharDownIdle);
	}
}

void AOverworldPlayer::CreateAnimation(std::string _AnimName, std::string _ImageName, float _Inter)
{
	ImageNameMap[_AnimName] = _ImageName;
	Renderer->CreateAnimation(_AnimName, _ImageName, 0.1f);
}

void AOverworldPlayer::ChangeAnimation(std::string _AnimName)
{
	Renderer->ChangeAnimation(_AnimName);
}
