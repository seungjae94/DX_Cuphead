#include "PreCompile.h"
#include "Boss.h"

ABoss::ABoss()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(ECollisionGroup::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ABoss::~ABoss()
{
}

void ABoss::SetHp(int _Hp)
{
	Hp = _Hp;
}

bool ABoss::IsFinished() const
{
	return "Finish" == StateManager.GetCurStateName();
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	StateManager.CreateState("Finish");
	StateManager.SetFunction("Finish",
		std::bind(&ABoss::FinishStart, this),
		std::bind(&ABoss::Finish, this, std::placeholders::_1),
		std::bind(&ABoss::FinishEnd, this)
	);
}

void ABoss::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	StateManager.Update(_DeltaTime);
	DebugUpdate(_DeltaTime);
}

void ABoss::DebugUpdate(float _DeltaTime)
{
	{
		std::string Msg = std::format("{} Hp : {}\n", GetName(), Hp);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("{} State : {}\n", GetName(), StateManager.GetCurStateName());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}
