#include "PreCompile.h"
#include "OverworldPlayer.h"

AOverworldPlayer::AOverworldPlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");

	//Renderer->SetSprite();
	//Renderer->CreateAnimation();
}

AOverworldPlayer::~AOverworldPlayer()
{
}
