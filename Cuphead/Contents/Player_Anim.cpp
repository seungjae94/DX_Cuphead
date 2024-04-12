#include "PreCompile.h"
#include "Player.h"

void APlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::PlayerIdle, GImageName::PlayerIdle, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerAimUp, GImageName::PlayerAimUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerAimHalfUp, GImageName::PlayerAimHalfUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerAimForward, GImageName::PlayerAimForward, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerAimHalfDown, GImageName::PlayerAimHalfDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerAimDown, GImageName::PlayerAimDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootUp, GImageName::PlayerShootUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootHalfUp, GImageName::PlayerShootHalfUp, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootForward, GImageName::PlayerShootForward, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootHalfDown, GImageName::PlayerShootHalfDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerShootDown, GImageName::PlayerShootDown, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRun, GImageName::PlayerRun, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRunShootHalfUp, GImageName::PlayerRunShootHalfUp, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRunShootForward, GImageName::PlayerRunShootForward, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerJump, GImageName::PlayerJump, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerDash, GImageName::PlayerDash, 1 / 24.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerSit, GImageName::PlayerSit, 1 / 12.0f);
}

void APlayer::ChangeAnimationIf(bool _Cond, std::string_view _IfAnim, std::string_view _ElseAnim)
{
	if (true == _Cond)
	{
		Renderer->ChangeAnimation(_IfAnim);
	}
	else
	{
		Renderer->ChangeAnimation(_ElseAnim);
	}
}
