#include "PreCompile.h"
#include "Player.h"
#include "AnimationEffect.h"
#include "Platform.h"
#include "CupheadCore.h"
#include "CupheadDebugWindow.h"

int APlayer::DamageCoeff = 1;

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

	if (true == HitBox->IsActive())
	{
		StateManager.ChangeState(GStateName::Hit);
	}
	else
	{
		Velocity = JumpImpulse * 1.3f;
		StateManager.ChangeState(GStateName::Jump);
	}
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

	// ����� ���
	DebugWindow->RegisterCallback(
		"DamageCheat",
		std::bind(&APlayer::DamageCheat, this)
	);
}

void APlayer::Tick(float _DeltaTime)
{
	if (_DeltaTime > 0.1f)
	{
		_DeltaTime = 0.1f;
	}

	Super::Tick(_DeltaTime);

	PlaySeconds += _DeltaTime;
	FireTime -= _DeltaTime;
	SpriteDirUpdate(_DeltaTime);
	StateManager.Update(_DeltaTime);
	PlatformMovementUpdate(_DeltaTime);

	// �ٴ� ������ üũ
	float PosY = GetActorLocation().Y;
	if (PosY < DamageGroundY)
	{
		IsGroundHit = true;
		Damage();
	}

	ChildRenderersUpdate(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void APlayer::SpriteDirUpdate(float _DeltaTime)
{
	if (false == DirUpdateActive)
	{
		return;
	}

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
	// �Ѿ� ���� ����Ʈ �̵�
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
		std::string Msg = std::format("Player PrevState : {}\n", PrevStateName);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("Player CurState : {}\n", CurStateName);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

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

bool APlayer::IsLeftCollisionOccur()
{
	if (true == CheckPixelCollision(LeftCollision->GetWorldPosition()))
	{
		return true;
	}

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

	float PosX = GetActorLocation().X;
	if (PosX > 550.0f)
	{
		return true;
	}

	return false;
}

bool APlayer::IsGroundCollisionOccur()
{
	// �ȼ� �浹 üũ
	if (true == CheckPixelCollision(BotCollision->GetWorldPosition()))
	{
		return true;
	}

	// �浹ü üũ
	bool CollisionCheck = false;
	BotCollision->CollisionEnter(ECollisionGroup::Platform, [&CollisionCheck](std::shared_ptr<UCollision> _Other) {
		CollisionCheck = true;
	});
	BotCollision->CollisionStay(ECollisionGroup::Platform, [&CollisionCheck](std::shared_ptr<UCollision> _Other) {
		CollisionCheck = true;
	});
	return CollisionCheck;
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

	// õ�忡�� �Ʒ��� �������� ó��
	while (true == IsGroundCollisionOccur())
	{
		AddActorLocation(FVector::Down);
	}
}

bool APlayer::TestDownJump()
{
	bool TestResult = false;
	AddActorLocation(FVector::Down * DownJumpCheckScale);

	if (false == IsGroundCollisionOccur())
	{
		TestResult = true;
	}

	AddActorLocation(FVector::Up * DownJumpCheckScale);

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

void APlayer::DamageCheat()
{
	ImGui::InputInt("Damage Multiplier", &DamageCoeff, 1, 100, 0);
}

int APlayer::GetDamageCoeff() const
{
	return DamageCoeff;
}

float APlayer::GetPlaySeconds() const
{
	return PlaySeconds;
}

int APlayer::GetRemainHp() const
{
	if (Hp < 0)
	{
		return 0;
	}

	return Hp;
}

int APlayer::GetParryCount() const
{
	if (ParryCount > 3)
	{
		return 3;
	}

	return ParryCount;
}

int APlayer::GetExUsageCount() const
{
	if (ExUsageCount > 6)
	{
		return 6;
	}

	return ExUsageCount;
}
