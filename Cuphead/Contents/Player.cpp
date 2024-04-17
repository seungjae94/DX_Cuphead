#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Player);
	Collision->SetCollisionType(ECollisionType::Rect);
}

APlayer::~APlayer()
{
}

void APlayer::Damage()
{
	--Hp;
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation({ 0.0f, -185.0f, 0.0f });

	Renderer->SetSprite(GImageName::PlayerIdle);
	Renderer->SetOrder(ERenderingOrder::Character);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetPivot(EPivot::BOT);

	Collision->SetScale(CollisionDefaultScale);
	Collision->SetPosition(CollisionDefaultPosition);

	AnimationInit();
	StateInit();
	StateManager.ChangeState(GStateName::Idle);

	InputOn();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FireTime -= _DeltaTime;
	StateManager.Update(_DeltaTime);
	SpriteDirUpdate(_DeltaTime);
	PhysicsUpdate(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void APlayer::SpriteDirUpdate(float _DeltaTime)
{
	EEngineDir PrevDirection = Direction;
	RefreshDirection();
	Renderer->SetDir(Direction);
}

void APlayer::PhysicsUpdate(float _DeltaTime)
{
	// �̵� �ùķ��̼�
	if (true == ApplyGravity)
	{
		Velocity += Gravity * _DeltaTime;
	}

	if (true == OnGroundValue && Velocity.Y < 0.0f)
	{
		Velocity.Y = 0.0f;
	}

	FVector PrevPos = GetActorLocation();
	AddActorLocation(Velocity * _DeltaTime);
	FVector NextPos = GetActorLocation();

	if (true == CheckCollision(ColLeftPoint) || true == CheckCollision(ColRightPoint))
	{
		FVector TargetPos = NextPos;
		TargetPos.X = PrevPos.X;
		SetActorLocation(TargetPos);
	}

	// �ٴ� �浹 üũ
	if (true == CheckCollision(ColBotPoint))
	{
		OnGroundValue = true;
	}
	else
	{
		OnGroundValue = false;
	}
}

void APlayer::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Player Hp : {}\n", std::to_string(Hp));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	//{
	//	std::string Msg = std::format("Player Position : {}\n", GetActorLocation().ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("Player Renderer Scale : {}\n", Renderer->GetWorldScale().ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("Player Velocity : {}\n", Velocity.ToString());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	{
		std::string Msg = std::format("Player OnGround : {}\n", OnGroundValue == true ? "true" : "false");
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	//{
	//	std::string Msg = std::format("Player CurState : {}\n", CurStateName);
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("Player PrevState : {}\n", PrevStateName);
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}

	//{
	//	std::string Msg = std::format("Player IsFire : {}\n", IsFire == true ? "true" : "false");
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}
}

bool APlayer::IsPressArrowKey()
{
	return IsPress(VK_LEFT) || IsPress(VK_RIGHT);
}

bool APlayer::IsDirectionLeft() const
{
	return Direction == EEngineDir::Left;
}

void APlayer::RefreshDirection()
{
	// ��� ���� �߿��� ������ ��ȯ���� �ʴ´�.
	if (GStateName::Dash == CurStateName)
	{
		return;
	}

	if (true == IsPress(VK_RIGHT))
	{
		Direction = EEngineDir::Right;
	}
	else if (true == IsPress(VK_LEFT))
	{
		Direction = EEngineDir::Left;
	}
}

bool APlayer::CheckCollision(const FVector& _ColPoint)
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes("boss_farm_map_col.png");
	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector ColTestPoint = GetActorLocation() + _ColPoint;
	FVector TestPixel = ColTestPoint - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}