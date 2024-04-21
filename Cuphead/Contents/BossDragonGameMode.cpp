#include "PreCompile.h"
#include "BossDragonGameMode.h"
#include "BossDragonMap.h"
#include "Dragon1.h"
#include "Dragon2.h"
#include "Dragon3.h"
#include "Player.h"
#include "Platform.h"

ABossDragonGameMode::ABossDragonGameMode()
{
}

ABossDragonGameMode::~ABossDragonGameMode()
{
}

void ABossDragonGameMode::BeginPlay()
{
	Super::BeginPlay();

	Player = GetWorld()->SpawnActor<APlayer>("Player").get();

	// 디버그용 픽셀 충돌
	Player->SetColMapName("boss_farm_map_col.png");

	Map = GetWorld()->SpawnActor<ABossDragonMap>("Map").get();

	StateInit();

	InputOn();
}

void ABossDragonGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ABossDragonGameMode::DebugUpdate(float _DeltaTime)
{
	std::string Msg = std::format("Game State : {}\n", StateManager.GetCurStateName());
	UEngineDebugMsgWindow::PushMsg(Msg);
}

void ABossDragonGameMode::StateInit()
{
	StateManager.CreateState("Intro");
	StateManager.CreateState("Phase1");
	StateManager.CreateState("Phase2Intro");
	StateManager.CreateState("Phase2");
	StateManager.CreateState("Phase3Intro");
	StateManager.CreateState("Phase3");

	StateManager.SetFunction("Intro",
		std::bind(&ABossDragonGameMode::IntroStart, this),
		std::bind(&ABossDragonGameMode::Intro, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::IntroEnd, this)
	);

	StateManager.SetFunction("Phase1",
		std::bind(&ABossDragonGameMode::Phase1Start, this),
		std::bind(&ABossDragonGameMode::Phase1, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::Phase1End, this)
	);

	StateManager.SetFunction("Phase2Intro",
		std::bind(&ABossDragonGameMode::Phase2IntroStart, this),
		std::bind(&ABossDragonGameMode::Phase2Intro, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::Phase2IntroEnd, this)
	);

	StateManager.SetFunction("Phase2",
		std::bind(&ABossDragonGameMode::Phase2Start, this),
		std::bind(&ABossDragonGameMode::Phase2, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::Phase2End, this)
	);

	StateManager.SetFunction("Phase3Intro",
		std::bind(&ABossDragonGameMode::Phase3IntroStart, this),
		std::bind(&ABossDragonGameMode::Phase3Intro, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::Phase3IntroEnd, this)
	);

	StateManager.SetFunction("Phase3",
		std::bind(&ABossDragonGameMode::Phase3Start, this),
		std::bind(&ABossDragonGameMode::Phase3, this, std::placeholders::_1),
		std::bind(&ABossDragonGameMode::Phase3End, this)
	);

	StateManager.ChangeState("Intro");
}

void ABossDragonGameMode::IntroStart()
{
	Dragon1 = GetWorld()->SpawnActor<ADragon1>("Dragon1").get();
	Dragon1->SetPlayer(Player);
	Dragon1->PlayIntroAnimation();
	Dragon1->SetFrameCallback("dragon1_intro", 39, [this]() {
		Dragon1->SetActorLocation({ 525.0f, -525.0f });
		Dragon1->SetState("Idle");
		StateManager.ChangeState("Phase1");
		});

	SpawnCloud(true, { -450.0f, -225.0f, 0.0f });
	SpawnCloud(true, { -450.0f, 275.0f, 0.0f });
	SpawnCloud(true, { -250.0f, 50.0f, 0.0f });
	SpawnCloud(true, { -150.0f, -275.0f, 0.0f });
	SpawnCloud(true, { 0.0f, 225.0f, 0.0f });
	SpawnCloud(true, { 100.0f, -250.0f, 0.0f });
	SpawnCloud(true, { 200.0f, 25.0f, 0.0f });
	SpawnCloud(true, { 300.0f, 225.0f, 0.0f });
}

void ABossDragonGameMode::Intro(float _DeltaTime)
{
}

void ABossDragonGameMode::IntroEnd()
{
}

void ABossDragonGameMode::Phase1Start()
{
	CloudSpawnTimer = 0.0f;

	for (UPlatform* Cloud : Clouds)
	{
		Cloud->MoveStart();
	}
}

void ABossDragonGameMode::Phase1(float _DeltaTime)
{
	CloudSpawnTimer -= _DeltaTime;

	if (CloudSpawnTimer >= 0.0f)
	{
		return;
	}

	// 구름 발판 생성
	UPlatform* FirstCloud = SpawnCloud(false);

	DelayCallBack(1.0f, [this, FirstCloud]() {
		UPlatform* SecondCloud = SpawnCloud(false);
		float FirstCloudY = FirstCloud->GetActorLocation().Y;
		SecondCloud->SetActorLocation({ 600.0f, FirstCloudY + 150.0f, 0.0f });
		});

	CloudSpawnTimer = CloudSpawnInterval;
}

void ABossDragonGameMode::Phase1End()
{
}

void ABossDragonGameMode::Phase2IntroStart()
{
}

void ABossDragonGameMode::Phase2Intro(float _DeltaTime)
{
}

void ABossDragonGameMode::Phase2IntroEnd()
{
}

void ABossDragonGameMode::Phase2Start()
{
}

void ABossDragonGameMode::Phase2(float _DeltaTime)
{
}

void ABossDragonGameMode::Phase2End()
{
}

void ABossDragonGameMode::Phase3IntroStart()
{
}

void ABossDragonGameMode::Phase3Intro(float _DeltaTime)
{
}

void ABossDragonGameMode::Phase3IntroEnd()
{
}

void ABossDragonGameMode::Phase3Start()
{
}

void ABossDragonGameMode::Phase3(float _DeltaTime)
{
}

void ABossDragonGameMode::Phase3End()
{
}

UPlatform* ABossDragonGameMode::SpawnCloud(bool _SetLocation, const FVector& _Location)
{
	UPlatform* Cloud = GetWorld()->SpawnActor<UPlatform>("Cloud").get();

	if (false == _SetLocation)
	{
		float RandomY = Random.RandomFloat(-250.0f, 100.0f);
		Cloud->SetActorLocation({ 600.0f, RandomY, 0.0f });
		Cloud->MoveStart();
	}
	else
	{
		Cloud->SetActorLocation(_Location);
		Clouds.push_back(Cloud);
	}

	Cloud->SetVelocity(FVector::Left * 100.0f);
	Cloud->SetRenderingOrder(ERenderingOrder::Back6);
	Cloud->SetCollisionPosition(FVector::Zero);
	Cloud->SetCollisionScale({ 150.0f, 1.0f, 1.0f });

	Cloud->CreateAnimation("dragon1_cloud_idle", "dragon1_cloud_idle.png", 1 / 12.0f, true);
	Cloud->CreateAnimation("dragon1_cloud_down_idle", "dragon1_cloud_down_idle.png", 1 / 12.0f, true);
	Cloud->CreateAnimation("dragon1_cloud_down", "dragon1_cloud_down.png", 1 / 12.0f, false);
	Cloud->CreateAnimation("dragon1_cloud_up", "dragon1_cloud_up.png", 1 / 12.0f, false);
	Cloud->ChangeAnimation("dragon1_cloud_idle");

	Cloud->SetFrameCallback("dragon1_cloud_up", 4, [this, Cloud]() {
		Cloud->ChangeAnimation("dragon1_cloud_idle");
		});

	Cloud->SetFrameCallback("dragon1_cloud_down", 2, [this, Cloud]() {
		Cloud->ChangeAnimation("dragon1_cloud_down_idle");
		});

	Cloud->SetOnStepEnter([this, Cloud](std::shared_ptr<UCollision> _Collision) {
		Cloud->ChangeAnimation("dragon1_cloud_down");
		});

	Cloud->SetOnStepExit([this, Cloud](std::shared_ptr<UCollision> _Collision) {
		Cloud->ChangeAnimation("dragon1_cloud_up");
		});

	return Cloud;
}
