#include "PreCompile.h"
#include "BossLevelEntrance.h"
#include "CupheadGameMode.h"

ABossLevelEntrance::ABossLevelEntrance()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(ERenderingOrder::Back3);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::BossLevelEntrance);
	Collision->SetCollisionType(ECollisionType::Rect);
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
	Collision->SetScale(Renderer->GetWorldScale());
}

void ABossLevelEntrance::BeginPlay()
{
	Super::BeginPlay();
}

void ABossLevelEntrance::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Collision->CollisionStay(ECollisionGroup::PlayerHitBox, [this](std::shared_ptr<UCollision> _Other) {
		// TODO: UI만 표시하도록 수정
		ACupheadGameMode* CurGameMode = dynamic_pointer_cast<ACupheadGameMode>(GetWorld()->GetGameMode()).get();
		CurGameMode->ChangeLevelWithFadeEffect(LevelName);
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
		std::string Msg = std::format("{} Collision Scale: {}", GetName(), Collision->GetWorldScale().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
