#include "PreCompile.h"
#include "BossLevelEntrance.h"
#include "CupheadGameMode.h"

ABossLevelEntrance::ABossLevelEntrance()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(ERenderingOrder::Entrance);

	BlockCollision = CreateDefaultSubObject<UCollision>("BlockCollision");
	BlockCollision->SetupAttachment(Root);
	BlockCollision->SetCollisionGroup(ECollisionGroup::BossLevelEntranceBlock);
	BlockCollision->SetCollisionType(ECollisionType::RotRect);

	ChangeLevelCollision = CreateDefaultSubObject<UCollision>("ChangeLevelCollision");
	ChangeLevelCollision->SetupAttachment(Root);
	ChangeLevelCollision->SetCollisionGroup(ECollisionGroup::BossLevelEntranceChangeLevel);
	ChangeLevelCollision->SetCollisionType(ECollisionType::RotRect);
}

ABossLevelEntrance::~ABossLevelEntrance()
{
}

void ABossLevelEntrance::SetLevelName(std::string_view _LevelName)
{
	LevelName = _LevelName;
}

void ABossLevelEntrance::SetAnimation(std::string_view _AnimName, std::string_view _SpriteName, float _Inter)
{
	Renderer->CreateAnimation(_AnimName, _SpriteName, _Inter, true);
	Renderer->SetAutoSize(1.0f, true);
	Renderer->ChangeAnimation(_AnimName);
}

UCollision* ABossLevelEntrance::GetBlockCollision()
{
	return BlockCollision;
}

UCollision* ABossLevelEntrance::GetChangeLevelCollision()
{
	return ChangeLevelCollision;
}

void ABossLevelEntrance::BeginPlay()
{
	Super::BeginPlay();
}

void ABossLevelEntrance::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BlockCollision->CollisionEnter(ECollisionGroup::PlayerHitBox, [this](std::shared_ptr<UCollision> _Other) {
		// TODO: UI�� ǥ���ϵ��� ����
		//ACupheadGameMode* CurGameMode = dynamic_pointer_cast<ACupheadGameMode>(GetWorld()->GetGameMode()).get();
		//CurGameMode->ChangeLevelWithFadeEffect(LevelName);
	});

	DebugUpdate(_DeltaTime);
}

void ABossLevelEntrance::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("{} Position: {}", GetName(), GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("{} Scale: {}", GetName(), GetActorScale3D().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("{} Collision Scale: {}", GetName(), BlockCollision->GetWorldScale().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
