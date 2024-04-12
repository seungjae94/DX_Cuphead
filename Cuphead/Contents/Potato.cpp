#include "PreCompile.h"
#include "Potato.h"

APotato::APotato()
{
	Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");
	SetRoot(Root);
}

APotato::~APotato()
{
}
