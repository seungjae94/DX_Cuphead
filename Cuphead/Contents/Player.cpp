#include "PreCompile.h"
#include "Player.h"
#include "AnimationEffect.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Player);
	Collision->SetCollisionType(ECollisionType::RotRect);
}

APlayer::~APlayer()
{
}

void APlayer::SetColMapName(std::string_view _ColMapName)
{
	ColMapName = _ColMapName;
}

void APlayer::Damage()
{
	--Hp;
	StateManager.ChangeState(GStateName::Hit);
}

void APlayer::AddSuperMeter(float _Value)
{
	SuperMeter += _Value;

	if (SuperMeter >= 5.0f)
	{
		SuperMeter = 5.0f;
	}
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

	HpWidget = CreateWidget<UImage>(GetWorld(), "Hp");
	HpWidget->SetScale({ 79.0f, 33.0f });

	FVector LeftBotPivotedPos = -GEngine->EngineWindow.GetWindowScale().Half2D() + HpWidget->GetWorldScale().Half2D();
	HpWidget->SetPosition(LeftBotPivotedPos + FVector{ 25.0f, 20.0f });
	HpWidget->AddToViewPort();
	HpWidget->SetSprite("ui_hp3.png");

	for (int i = 0; i < 5; ++i)
	{
		UImage* CardWidget = CreateWidget<UImage>(GetWorld(), "CardWidget");

		FVector LeftBotPivotedPos = -GEngine->EngineWindow.GetWindowScale().Half2D() + HpWidget->GetWorldScale().Half2D();
		CardWidget->SetPosition(LeftBotPivotedPos + FVector{ 80.0f + i * 20.0f, 18.0f });
		CardWidget->AddToViewPort();
		CardWidget->SetSprite("ui_card.png");
		CardWidgets.push_back(CardWidget);
	}

	InputOn();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FireTime -= _DeltaTime;
	StateManager.Update(_DeltaTime);
	SpriteDirUpdate(_DeltaTime);
	PhysicsUpdate(_DeltaTime);
	UIUpdate(_DeltaTime);
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
	// 이동 시뮬레이션
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
		NextPos = TargetPos;
	}

	// 총알 스폰 이펙트 이동
	if (nullptr != HandBulletSpawnEffect && false == HandBulletSpawnEffect->IsDestroy())
	{
		HandBulletSpawnEffect->AddActorLocation(NextPos - PrevPos);
	}

	// 바닥 충돌 체크
	if (true == CheckCollision(ColBotPoint))
	{
		OnGroundValue = true;
	}
	else
	{
		OnGroundValue = false;
	}
}

void APlayer::UIUpdate(float _DeltaTime)
{
	// HP UI 업데이트
	if (3 == Hp)
	{
		HpWidget->SetSprite("ui_hp3.png");
	}
	else if (2 == Hp)
	{
		HpWidget->SetSprite("ui_hp2.png");
	}
	else if (0 == Hp)
	{
		HpWidget->SetSprite("ui_dead.png");
	}
	else if (1 == Hp)
	{
		HpWidgetFrameTime -= _DeltaTime;

		if (HpWidgetFrameTime < 0.0f)
		{
			HpWidgetWarn0 = !HpWidgetWarn0;

			if (true == HpWidgetWarn0)
			{
				HpWidget->SetSprite("ui_hp1_0.png");
			}
			else 
			{
				HpWidget->SetSprite("ui_hp1_1.png");
			}

			HpWidgetFrameTime = HpWidgetFrameInterval;
		}
	}

	// 슈퍼미터 UI 업데이트
	int SuperMeterInt = std::lround(SuperMeter);

	if (SuperMeterInt > 5)
	{
		SuperMeterInt = 5;
	}

	for (int i = 0; i < SuperMeterInt; ++i)
	{
		CardWidgets[i]->SetScale({20.0f, 30.0f});
	}
	for (int i = SuperMeterInt; i < 5; ++i)
	{
		CardWidgets[i]->SetScale(FVector::Zero);
	}
}

void APlayer::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Player OnGround : {}\n", OnGroundValue == true ? "true" : "false");
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
	// 대시 동작 중에는 방향을 전환하지 않는다.
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
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes(ColMapName);

	if (nullptr == MapTex)
	{
		return false;
	}

	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector ColTestPoint = GetActorLocation() + _ColPoint;
	FVector TestPixel = ColTestPoint - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}