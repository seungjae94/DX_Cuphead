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
	Hp = UCupheadMath::Max(Hp, 0);
	HpWidget->ChangeAnimation("ui_hp" + std::to_string(Hp));
	StateManager.ChangeState(GStateName::Hit);
}

void APlayer::AddSuperMeter(float _Value)
{
	SuperMeter += _Value;

	if (SuperMeter >= 5.0f)
	{
		SuperMeter = 5.0f;
	}
	
	RefreshSuperMeterUI();
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
	UIInit();

	InputOn();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FireTime -= _DeltaTime;
	SpriteDirUpdate(_DeltaTime);
	StateManager.Update(_DeltaTime);
	ChildRenderersUpdate(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void APlayer::SpriteDirUpdate(float _DeltaTime)
{
	EEngineDir PrevDirection = Direction;
	RefreshDirection();
	Renderer->SetDir(Direction);
}

void APlayer::ChildRenderersUpdate(float _DeltaTime)
{
	// 총알 스폰 이펙트 이동
	if (nullptr != HandBulletSpawnEffect && false == HandBulletSpawnEffect->IsDestroy())
	{
		HandBulletSpawnEffect->AddActorLocation(Velocity * _DeltaTime);
	}
}

void APlayer::UIInit()
{
	HpWidget = CreateWidget<UImage>(GetWorld(), "Hp");

	HpWidget->AddToViewPort(0);
	HpWidget->SetSprite("ui_hp3.png");
	HpWidget->SetAutoSize(1.0f, true);
	HpWidget->CreateAnimation("ui_hp3", "ui_hp3.png", 0.0f, false);
	HpWidget->CreateAnimation("ui_hp2", "ui_hp2.png", 0.0f, false);
	HpWidget->CreateAnimation("ui_hp1", "ui_hp1", 1 / 24.0f, true);
	HpWidget->CreateAnimation("ui_hp0", "ui_hp0.png", 0.0f, false);

	FVector LeftBotPivotedPos = -GEngine->EngineWindow.GetWindowScale().Half2D() + HpWidget->GetWorldScale().Half2D();
	HpWidget->SetPosition(LeftBotPivotedPos + FVector{ 25.0f, 20.0f });

	for (int i = 0; i < 5; ++i)
	{
		UImage* CardWidget = CreateWidget<UImage>(GetWorld(), "CardWidget");

		FVector LeftBotPivotedPos = -GEngine->EngineWindow.GetWindowScale().Half2D() + HpWidget->GetWorldScale().Half2D();
		CardWidget->SetPosition(LeftBotPivotedPos + FVector{ 80.0f + i * 20.0f, 18.0f });
		CardWidget->AddToViewPort(0);
		CardWidget->SetSprite("ui_card.png");
		CardWidget->SetAutoSize(0.0f, true);
		CardWidgets.push_back(CardWidget);
	}

	RefreshSuperMeterUI();
}

void APlayer::RefreshSuperMeterUI()
{
	int SuperMeterInt = std::lround(SuperMeter);

	for (int i = 0; i < SuperMeterInt; ++i)
	{
		CardWidgets[i]->SetAutoSize(1.0f, true);
	}
	for (int i = SuperMeterInt; i < 5; ++i)
	{
		CardWidgets[i]->SetAutoSize(0.0f, true);
	}
}

void APlayer::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("Player OnGround : {}\n", OnGroundValue == true ? "true" : "false");
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player Position : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player Velocity : {}\n", Velocity.ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player CurState : {}\n", CurStateName);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

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

bool APlayer::IsLeftCollisionOccur()
{
	if (true == CheckPixelCollision(GetActorLocation() + LeftColliderLocalPosition))
	{
		return true;
	}

	// TODO: 충돌체 체크

	return false;
}

bool APlayer::IsRightCollisionOccur()
{
	if (true == CheckPixelCollision(GetActorLocation() + RightColliderLocalPosition))
	{
		return true;
	}

	// TODO: 충돌체 체크

	return false;
}

bool APlayer::IsGroundCollisionOccur()
{
	if (true == CheckPixelCollision(GetActorLocation() + BotColliderLocalPosition))
	{
		return true;
	}

	// TODO: 충돌체 체크

	return false;
}

void APlayer::MoveUpToGround()
{
	while (true == IsGroundCollisionOccur())
	{
		AddActorLocation(FVector::Up);
	}
	AddActorLocation(FVector::Down);
}

bool APlayer::CheckPixelCollision(const FVector& _Point)
{
	std::shared_ptr<UEngineTexture> MapTex = UEngineTexture::FindRes(ColMapName);

	if (nullptr == MapTex)
	{
		return false;
	}

	FVector MapTexScale = MapTex->GetScale();

	FVector MapTexLeftTop = -MapTexScale.Half2D();
	MapTexLeftTop.Y = -MapTexLeftTop.Y;
	FVector TestPixel = _Point - MapTexLeftTop;
	TestPixel.Y = -TestPixel.Y;
	Color8Bit ColMapColor = MapTex->GetColor(TestPixel, Color8Bit::Black);
	return ColMapColor == Color8Bit::Black;
}