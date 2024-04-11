#include "PreCompile.h"
#include "Player.h"

void APlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::PlayerLeftIdle, GImageName::PlayerLeftIdle, 1/12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightIdle, GImageName::PlayerRightIdle, 1/12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftJump, GImageName::PlayerLeftJump, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightJump, GImageName::PlayerRightJump, 1 / 24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftDash, GImageName::PlayerLeftDash, 1 / 24.0f, false, 0, 6);
	Renderer->CreateAnimation(GAnimName::PlayerRightDash, GImageName::PlayerRightDash, 1 / 24.0f, false, 0, 6);
	Renderer->CreateAnimation(GAnimName::PlayerLeftShoot, GImageName::PlayerLeftShoot, 1/12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightShoot, GImageName::PlayerRightShoot, 1/12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRun, GImageName::PlayerLeftRun, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRun, GImageName::PlayerRightRun, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftRunShoot, GImageName::PlayerLeftRunShoot, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightRunShoot, GImageName::PlayerRightRunShoot, 1/24.0f);
	Renderer->CreateAnimation(GAnimName::PlayerLeftSit, GImageName::PlayerLeftSit, 1/12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerRightSit, GImageName::PlayerRightSit, 1/12.0f);
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
