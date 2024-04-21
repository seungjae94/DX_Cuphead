#include "PreCompile.h"
#include "Player.h"

void APlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::PlayerIdle, GImageName::PlayerIdle, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootUp, GImageName::PlayerShootUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootHalfUp, GImageName::PlayerShootHalfUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootForward, GImageName::PlayerShootForward, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootHalfDown, GImageName::PlayerShootHalfDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootDown, GImageName::PlayerShootDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRun, GImageName::PlayerRun, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRunShootHalfUp, GImageName::PlayerRunShootHalfUp, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRunShootForward, GImageName::PlayerRunShootForward, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerJump, GImageName::PlayerJump, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerParry, GImageName::PlayerParry, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerDash, GImageName::PlayerDash, 1 / 24.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerSit, GImageName::PlayerSit, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerSitShootForward, GImageName::PlayerSitShootForward, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerHit, GImageName::PlayerHit, 1 / 12.0f, false);
}

void APlayer::ChangeAnimationIfChanged(std::string _AnimName)
{
	if (_AnimName == CurAnimName)
	{
		return;
	}

	CurAnimName = _AnimName;
	Renderer->ChangeAnimation(_AnimName);
}