#include "PreCompile.h"
#include "Player.h"

void APlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::PlayerIntro, GImageName::PlayerIntro, 1 / 12.0f);
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
	Renderer->CreateAnimation(GAnimName::PlayerSitting, GImageName::PlayerSitting, 1 / 24.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerStanding, GImageName::PlayerSitting, 1 / 24.0f, false, 6, 0);
	Renderer->CreateAnimation(GAnimName::PlayerSitShootForward, GImageName::PlayerSitShootForward, 1 / 12.0f);
	Renderer->CreateAnimation(GAnimName::PlayerHit, GImageName::PlayerHit, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerAirExUp, GImageName::PlayerAirExUp, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerAirExHalfUp, GImageName::PlayerAirExHalfUp, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerAirExForward, GImageName::PlayerAirExForward, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerAirExHalfDown, GImageName::PlayerAirExHalfDown, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerAirExDown, GImageName::PlayerAirExDown, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerGroundExUp, GImageName::PlayerGroundExUp, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerGroundExHalfUp, GImageName::PlayerGroundExHalfUp, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerGroundExForward, GImageName::PlayerGroundExForward, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerGroundExHalfDown, GImageName::PlayerGroundExHalfDown, 1 / 12.0f, false);
	Renderer->CreateAnimation(GAnimName::PlayerGroundExDown, GImageName::PlayerGroundExDown, 1 / 12.0f, false);

	Renderer->SetFrameCallback(GAnimName::PlayerSitting, 6, [this]() {
		IsSitting = false;
	});

	Renderer->SetFrameCallback(GAnimName::PlayerStanding, 6, [this]() {
		IsStanding = false;
		ChangeState(GStateName::Idle);
	});
}