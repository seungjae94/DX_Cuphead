#include "PreCompile.h"
#include "Player.h"
#include "AnimationEffect.h"
#include "Platform.h"

APlayer::APlayer()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);

	HitBox = CreateDefaultSubObject<UCollision>("BodyCollision");
	HitBox->SetupAttachment(Root);
	HitBox->SetCollisionGroup(ECollisionGroup::PlayerHitBox);
	HitBox->SetCollisionType(ECollisionType::RotRect);

	BotCollision = CreateDefaultSubObject<UCollision>("BotCollision");
	BotCollision->SetupAttachment(Root);
	BotCollision->SetCollisionGroup(ECollisionGroup::PlayerPhysicsBot);
	BotCollision->SetCollisionType(ECollisionType::RotRect);

	LeftCollision = CreateDefaultSubObject<UCollision>("LeftCollision");
	LeftCollision->SetupAttachment(Root);
	LeftCollision->SetCollisionGroup(ECollisionGroup::PlayerPhysicsHor);
	LeftCollision->SetCollisionType(ECollisionType::RotRect);

	RightCollision = CreateDefaultSubObject<UCollision>("RightCollision");
	RightCollision->SetupAttachment(Root);
	RightCollision->SetCollisionGroup(ECollisionGroup::PlayerPhysicsHor);
	RightCollision->SetCollisionType(ECollisionType::RotRect);
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

	HitBox->SetScale(BodyCollisionDefaultScale);
	HitBox->SetPosition(BodyCollisionDefaultPosition);

	BotCollision->SetScale({ 3.0f, 3.0f, 1.0f });
	BotCollision->SetPosition({ 0.0f, 0.0f, 0.0f });

	LeftCollision->SetScale({ 3.0f, 3.0f, 1.0f });
	LeftCollision->SetPosition({ -30.0f, 50.0f, 0.0f });

	RightCollision->SetScale({ 3.0f, 3.0f, 1.0f });
	RightCollision->SetPosition({ 30.0f, 50.0f, 0.0f });

	AnimationInit();
	StateInit();
	UIInit();

	InputOn();
}

void APlayer::Tick(float _DeltaTime)
{
	if (_DeltaTime > 0.01f)
	{
		_DeltaTime = 0.01f;
	}

	Super::Tick(_DeltaTime);

	FireTime -= _DeltaTime;
	SpriteDirUpdate(_DeltaTime);
	StateManager.Update(_DeltaTime);
	PlatformMovementUpdate(_DeltaTime);
	ChildRenderersUpdate(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void APlayer::SpriteDirUpdate(float _DeltaTime)
{
	EEngineDir PrevDirection = Direction;
	RefreshDirection();
	Renderer->SetDir(Direction);
}

void APlayer::PlatformMovementUpdate(float _DeltaTime)
{
	BotCollision->CollisionStay(ECollisionGroup::Platform, [this, _DeltaTime](std::shared_ptr<UCollision> _PlatformCollision) {
		APlatform* Platform = dynamic_cast<APlatform*>(_PlatformCollision->GetActor());
		FVector Velocity = Platform->GetVelocity();
		AddActorLocation(Velocity * _DeltaTime);

		if (true == IsLeftCollisionOccur() || true == IsRightCollisionOccur())		
		{
			AddActorLocation(-Velocity * _DeltaTime);
		}
	});
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
	if (true == CheckPixelCollision(LeftCollision->GetWorldPosition()))
	{
		return true;
	}

	// TODO: 충돌체 체크
	float PosX = GetActorLocation().X;
	if (PosX < -550.0f)
	{
		return true;
	}

	return false;
}

bool APlayer::IsRightCollisionOccur()
{
	if (true == CheckPixelCollision(RightCollision->GetWorldPosition()))
	{
		return true;
	}

	// TODO: 충돌체 체크

	float PosX = GetActorLocation().X;
	if (PosX > 550.0f)
	{
		return true;
	}

	return false;
}

bool APlayer::IsGroundCollisionOccur()
{
	if (true == CheckPixelCollision(BotCollision->GetWorldPosition()))
	{
		return true;
	}

	// 충돌체 체크
	if (true == BotCollision->CollisionEnter(ECollisionGroup::Platform, nullptr)
		|| true == BotCollision->CollisionStay(ECollisionGroup::Platform, nullptr))
	{
		return true;
	}
	
	return false;
}

void APlayer::MoveUpToGround()
{
	int UpCount = 0;
	bool MoveUp = true;

	while (true == IsGroundCollisionOccur() && true == MoveUp)
	{
		AddActorLocation(FVector::Up);
		++UpCount;

		if (UpCount > 1000)
		{
			MoveUp = false;
		}
	}

	if (true == MoveUp)
	{
		AddActorLocation(FVector::Down);
		return;
	}

	// 천장에서 아래로 내려가는 처리
	while (true == IsGroundCollisionOccur())
	{
		AddActorLocation(FVector::Down);
	}
}

bool APlayer::TestDownJump()
{
	bool TestResult = false;
	AddActorLocation(FVector::Down * 5.0f);

	if (false == IsGroundCollisionOccur())
	{
		TestResult = true;
	}

	AddActorLocation(FVector::Up * 5.0f);

	return TestResult;
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