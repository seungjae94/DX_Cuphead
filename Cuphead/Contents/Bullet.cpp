#include "PreCompile.h"
#include "Bullet.h"

ABullet::ABullet()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ABullet::~ABullet()
{
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite();
	Renderer->SetAutoSize(1.0f, true);

	Renderer->CreateAnimation(GAnimName::BulletSpawn, GImageName::BulletSpawn, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletLeft, GImageName::BulletLeft, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletRight, GImageName::BulletRight, 0.1f);
	Renderer->CreateAnimation(GAnimName::BulletDestroy, GImageName::BulletDestroy, 0.1f);
}

void ABullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
