#include "PreCompile.h"
#include "RendererUtil.h"

URendererUtil::URendererUtil()
{
}

URendererUtil::~URendererUtil()
{
}

void URendererUtil::HorFlip(USpriteRenderer* _Renderer)
{
	FVector Scale = _Renderer->Transform.GetScale();
	Scale.X = -Scale.X;
	_Renderer->Transform.SetScale(Scale);
}
