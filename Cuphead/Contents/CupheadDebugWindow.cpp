#include "PreCompile.h"
#include "CupheadDebugWindow.h"

UCupheadDebugWindow::UCupheadDebugWindow()
{
}

UCupheadDebugWindow::~UCupheadDebugWindow()
{
}

void UCupheadDebugWindow::RegisterCallback(std::string_view _Key, std::function<void()> _Callback)
{
	Callbacks[std::string(_Key)] = _Callback;
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
	ImGui::Text(std::format("FPS: {}", std::to_string(1.0f / _Delta)).c_str());

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

	if (true == ImGui::Button("Boss Dragon Level"))
	{
		GEngine->ChangeLevel(GLevelName::BossDragonLevel);
	}

	for (auto Pair : Callbacks)
	{
		Pair.second();
	}
}
