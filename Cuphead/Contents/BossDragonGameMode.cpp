#include "PreCompile.h"
#include "BossDragonGameMode.h"
#include "BossDragonMap.h"
#include "Dragon1.h"
#include "Dragon2.h"
#include "Dragon3.h"
#include "Player.h"

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
	/*Dragon1->SetFrameCallback("potato_intro", 9, [this]() {
		StateManager.ChangeState("PotatoBattle");
	});*/

}

void ABossDragonGameMode::Intro(float _DeltaTime)
{
}

void ABossDragonGameMode::IntroEnd()
{
}

void ABossDragonGameMode::Phase1Start()
{
}

void ABossDragonGameMode::Phase1(float _DeltaTime)
{
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
