#include "PreCompile.h"
#include "OverworldPlayer.h"

void AOverworldPlayer::StateInit()
{
	StateManager.CreateState(GStateName::Idle);
	StateManager.CreateState(GStateName::Walk);

	StateManager.SetStartFunction(GStateName::Idle, std::bind(&AOverworldPlayer::IdleStart, this));
	StateManager.SetUpdateFunction(GStateName::Idle, std::bind(&AOverworldPlayer::Idle, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Idle, std::bind(&AOverworldPlayer::IdleEnd, this));

	StateManager.SetStartFunction(GStateName::Walk, std::bind(&AOverworldPlayer::WalkStart, this));
	StateManager.SetUpdateFunction(GStateName::Walk, std::bind(&AOverworldPlayer::Walk, this, std::placeholders::_1));
	StateManager.SetEndFunction(GStateName::Walk, std::bind(&AOverworldPlayer::WalkEnd, this));

	StateManager.ChangeState(GStateName::Idle);
}

void AOverworldPlayer::IdleStart()
{
	std::string AnimName = TransDirectionToAnimName(Direction, true);
	Renderer->ChangeAnimation(AnimName);
	RefreshFlip();
}

void AOverworldPlayer::Idle(float _DeltaTime)
{
	if (true == IsDown(VK_LEFT)
		|| true == IsDown(VK_RIGHT)
		|| true == IsDown(VK_UP)
		|| true == IsDown(VK_DOWN))
	{
		StateManager.ChangeState(GStateName::Walk);
	}
}

void AOverworldPlayer::IdleEnd()
{
}

void AOverworldPlayer::WalkStart()
{

}

void AOverworldPlayer::Walk(float _DeltaTime)
{
	if (false == IsPressArrowKey())
	{
		StateManager.ChangeState(GStateName::Idle);
		return;
	}

	// ���� ����
	RefreshDirection();
	DirectionVector = UConverter::ConvDirectionToFVector(Direction);
	RefreshFlip();

	// �ִϸ��̼� ����
	std::string AnimName = TransDirectionToAnimName(Direction, false);
	Renderer->ChangeAnimation(AnimName);

	// �̵� �ùķ��̼�
	FVector OriginalPos = GetActorLocation();
	AddActorLocation(DirectionVector * MoveSpeed * _DeltaTime);

	// �浹 üũ
	// - �浹�� �߻��� ��� ��ġ�� �ǵ�����.
	if (true == CheckCollision())
	{
		SetActorLocation(OriginalPos);
		return;
	}

	// ī�޶� �̵� ó��
	float CameraZ = GetWorld()->GetMainCamera()->GetActorLocation().Z;
	FVector CameraLocation = GetActorLocation();
	CameraLocation.Z = CameraZ;
	GetWorld()->GetMainCamera()->SetActorLocation(CameraLocation);
}

void AOverworldPlayer::WalkEnd()
{
}

bool AOverworldPlayer::IsPressArrowKey()
{
	return IsPress(VK_LEFT) || IsPress(VK_RIGHT) || IsPress(VK_UP) || IsPress(VK_DOWN);
}

void AOverworldPlayer::RefreshDirection()
{
	if (true == IsPress(VK_LEFT))
	{
		if (true == IsPress(VK_UP))
		{
			Direction = EDirection::LeftUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			Direction = EDirection::LeftDown;
		}
		else
		{
			Direction = EDirection::Left;
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsPress(VK_UP))
		{
			Direction = EDirection::RightUp;
		}
		else if (true == IsPress(VK_DOWN))
		{
			Direction = EDirection::RightDown;
		}
		else
		{
			Direction = EDirection::Right;
		}
	}
	else if (true == IsPress(VK_UP))
	{
		Direction = EDirection::Up;
	}
	else if (true == IsPress(VK_DOWN))
	{
		Direction = EDirection::Down;
	}
}

void AOverworldPlayer::RefreshFlip()
{
	switch (Direction)
	{
	case EDirection::Right:
	case EDirection::RightUp:
	case EDirection::RightDown:
	case EDirection::Up:
	case EDirection::Down:
		Renderer->SetDir(EEngineDir::Right);
		break;
	case EDirection::LeftUp:
	case EDirection::Left:
	case EDirection::LeftDown:
		Renderer->SetDir(EEngineDir::Left);
		break;
	}
}

bool AOverworldPlayer::CheckCollision()
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes(GImageName::OverworldIsle1Pixel);
	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector ActorPos = GetActorLocation();
	FVector MapTexLeftTopRelativePos = ActorPos - MapTexLeftTop;
	MapTexLeftTopRelativePos.Y = -MapTexLeftTopRelativePos.Y;
	Color8Bit ColMapColor = MapTex->GetColor(MapTexLeftTopRelativePos, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}
