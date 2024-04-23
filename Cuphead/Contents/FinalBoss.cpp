#include "PreCompile.h"
#include "FinalBoss.h"

AFinalBoss::AFinalBoss()
{
}

AFinalBoss::~AFinalBoss()
{
}

void AFinalBoss::ResumeFaint()
{
	FaintActive = true;
}

void AFinalBoss::FaintStart()
{
	Super::FaintStart();
	FaintActive = false;
}