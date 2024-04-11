#include "PreCompile.h"
#include "Player.h"

void APlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::PlayerLeftIdle, GImageName::PlayerLeftIdle, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightIdle, GImageName::PlayerRightIdle, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftJump, GImageName::PlayerLeftJump, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightJump, GImageName::PlayerRightJump, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftDash, GImageName::PlayerLeftDash, 1 / 24.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerRightDash, GImageName::PlayerRightDash, 1 / 24.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerLeftShoot, GImageName::PlayerLeftShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightShoot, GImageName::PlayerRightShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRun, GImageName::PlayerLeftRun, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRun, GImageName::PlayerRightRun, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRunShoot, GImageName::PlayerLeftRunShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRunShoot, GImageName::PlayerRightRunShoot, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftSit, GImageName::PlayerLeftSit, 0.1f);
	Renderer->CreateAnimation(GAnimName::PlayerRightSit, GImageName::PlayerRightSit, 0.1f);
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
