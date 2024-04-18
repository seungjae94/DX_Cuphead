#include "PreCompile.h"
#include "CupheadDebugWindow.h"

UCupheadDebugWindow::UCupheadDebugWindow()
{
}

UCupheadDebugWindow::~UCupheadDebugWindow()
{
}

void UCupheadDebugWindow::RegisterCallback(std::function<void()> _Callback)
{
	Callbacks.push_back(_Callback);
}

void UCupheadDebugWindow::Init()
{
	Super::Init();
}

void UCupheadDebugWindow::Tick(ULevel* _Level, float _Delta)
{
	Super::Tick(_Level, _Delta);
}

void UCupheadDebugWindow::OnGui(ULevel* _Level, float _Delta)
{
	if (true == ImGui::Button("Title Level"))
	{
		GEngine->ChangeLevel(GLevelName::TitleLevel);
	}

	if (true == ImGui::Button("Overworld Level"))
	{
		GEngine->ChangeLevel(GLevelName::OverworldLevel);
	}

	if (true == ImGui::Button("Boss Farm Level"))
	{
		GEngine->ChangeLevel(GLevelName::BossFarmLevel);
	}

	for (auto Callback : Callbacks)
	{
		Callback();
	}
}
