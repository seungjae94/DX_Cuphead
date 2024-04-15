#include "PreCompile.h"
#include "BossAttack.h"

BossAttack::BossAttack()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
}

BossAttack::~BossAttack()
{
}
