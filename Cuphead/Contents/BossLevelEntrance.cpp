#include "PreCompile.h"
#include "BossLevelEntrance.h"
#include "CupheadGameMode.h"
#include "OverworldPlayer.h"
#include "PlayResultGameMode.h"

ABossLevelEntrance::ABossLevelEntrance()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	Renderer->SetOrder(ERenderingOrder::Entrance);

	FlagRenderer = CreateDefaultSubObject<USpriteRenderer>("FlagRenderer");
	FlagRenderer->SetupAttachment(Root);
	FlagRenderer->SetOrder(ERenderingOrder::Flag);

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

	LevelExplainUI = CreateWidget<UImage>(GetWorld(), "LevelExplainUI");
	LevelExplainUI->AddToViewPort(0);

	if (GLevelName::BossFarmLevel == LevelName)
	{
		LevelExplainUI->SetSprite("overworld_farm_ui.png");
	}
	else if (GLevelName::BossDragonLevel == LevelName)
	{
		LevelExplainUI->SetSprite("overworld_dragon_ui.png");
	}

	LevelExplainUI->SetAutoSize(1.0f, true);
	LevelExplainUI->SetActive(false);
}

void ABossLevelEntrance::SetFlagPosition(const FVector& _Position)
{
	FlagRenderer->SetPosition(_Position);
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

void ABossLevelEntrance::SetPlayer(AOverworldPlayer* _Player)
{
	Player = _Player;
}

void ABossLevelEntrance::BeginPlay()
{
	Super::BeginPlay();

	FlagRenderer->SetAutoSize(1.0f, true);
	FlagRenderer->CreateAnimation("overworld_flag", "overworld_flag.png", 1 / 12.0f, true);
	FlagRenderer->ChangeAnimation("overworld_flag");
	FlagRenderer->SetActive(false);
}

void ABossLevelEntrance::LevelStart(ULevel* _PrevLevel)
{
	LevelExplainUI->SetActive(false);
	Player->SetInputActive(true);

	if (nullptr == _PrevLevel)
	{
		return;
	}

	APlayResultGameMode* PRGameMode = dynamic_cast<APlayResultGameMode*>(_PrevLevel->GetGameMode().get());

	if (nullptr == PRGameMode)
	{
		return;
	}

	std::string PrevLevelName = PRGameMode->GetPrevLevelName();

	if (false == CheckLevelMatch(PrevLevelName))
	{
		return;
	}

	Player->SetZButtonActive(false);
	ChangeLevelCollision->SetActive(false);

	// 깃발 꽂기
	FlagRenderer->SetActive(true);
		
	// TODO: 플레이어 상태 변경
}

void ABossLevelEntrance::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChangeLevelCollision->CollisionEnter(ECollisionGroup::PlayerHitBox, [this](std::shared_ptr<UCollision> _Other) {
		Player->SetZButtonActive(true);
	});

	ChangeLevelCollision->CollisionStay(ECollisionGroup::PlayerHitBox, std::bind(&ABossLevelEntrance::OnCollisionStay, this, std::placeholders::_1));

	ChangeLevelCollision->CollisionExit(ECollisionGroup::PlayerHitBox, [this](std::shared_ptr<UCollision> _Other) {
		Player->SetZButtonActive(false);
		LevelExplainUI->SetActive(false);
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

bool ABossLevelEntrance::CheckLevelMatch(std::string_view _LevelName)
{
	return LevelName == _LevelName;
}

void ABossLevelEntrance::OnCollisionStay(std::shared_ptr<UCollision> _PlayerCollision)
{
	// UI가 떠있는 경우
	if (true == LevelExplainUI->IsActive())
	{
		if (true == UEngineInput::IsDown('Z'))
		{
			ACupheadGameMode* CurGameMode = dynamic_pointer_cast<ACupheadGameMode>(GetWorld()->GetGameMode()).get();
			CurGameMode->ChangeLevelWithFadeEffect(LevelName);
			UEngineSound::SoundPlay("overworld_change_level.mp3");
			return;
		}
		
		if (true == UEngineInput::IsDown(VK_ESCAPE))
		{
			UEngineSound::SoundPlay("overworld_ui_close.mp3");
			LevelExplainUI->SetActive(false);
			Player->SetInputActive(true);
			return;
		}

		return;
	}

	// UI를 띄워야 하는 경우
	if (true == UEngineInput::IsDown('Z'))
	{
		UEngineSound::SoundPlay("overworld_ui_open.mp3");
		LevelExplainUI->SetActive(true);
		Player->SetInputActive(false);
	}
}
