#include "PreCompile.h"
#include "OverworldPlayer.h"

void AOverworldPlayer::AnimationInit()
{
	Renderer->CreateAnimation(GAnimName::OverworldCharDownIdle, GImageName::OverworldCharDownIdle, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharDownWalk, GImageName::OverworldCharDownWalk, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightIdle, GImageName::OverworldCharRightIdle, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightWalk, GImageName::OverworldCharRightWalk, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharUpIdle, GImageName::OverworldCharUpIdle, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharUpWalk, GImageName::OverworldCharUpWalk, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightDownIdle, GImageName::OverworldCharRightDownIdle, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightDownWalk, GImageName::OverworldCharRightDownWalk, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightUpIdle, GImageName::OverworldCharRightUpIdle, 0.067f);
	Renderer->CreateAnimation(GAnimName::OverworldCharRightUpWalk, GImageName::OverworldCharRightUpWalk, 0.067f);
	Renderer->ChangeAnimation(GAnimName::OverworldCharDownIdle);
}

std::string AOverworldPlayer::TransDirectionToAnimName(EDirection _Direction, bool _IsIdle)
{
	if (true == _IsIdle)
	{
		switch (_Direction)
		{
		case EDirection::Right:
		case EDirection::Left:
			return GAnimName::OverworldCharRightIdle;
		case EDirection::RightUp:
		case EDirection::LeftUp:
			return GAnimName::OverworldCharRightUpIdle;
		case EDirection::Up:
			return GAnimName::OverworldCharUpIdle;
		case EDirection::LeftDown:
		case EDirection::RightDown:
			return GAnimName::OverworldCharRightDownIdle;
		case EDirection::Down:
			return GAnimName::OverworldCharDownIdle;
		}
	}

	switch (_Direction)
	{
	case EDirection::Right:
	case EDirection::Left:
		return GAnimName::OverworldCharRightWalk;
	case EDirection::RightUp:
	case EDirection::LeftUp:
		return GAnimName::OverworldCharRightUpWalk;
	case EDirection::Up:
		return GAnimName::OverworldCharUpWalk;
	case EDirection::LeftDown:
	case EDirection::RightDown:
		return GAnimName::OverworldCharRightDownWalk;
	case EDirection::Down:
		return GAnimName::OverworldCharDownWalk;
	}

	MsgBoxAssert(std::to_string(static_cast<int>(_Direction)) + "은 존재하지 않는 방향입니다.");
	return "ERROR";
}