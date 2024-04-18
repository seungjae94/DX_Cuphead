#pragma once
#include <EngineCore/EngineCore.h>

class UCupheadDebugWindow;

class UCupheadCore : public UserCore
{
public:
	// constructor destructor
	UCupheadCore();
	~UCupheadCore();

	// delete Function
	UCupheadCore(const UCupheadCore& _Other) = delete;
	UCupheadCore(UCupheadCore&& _Other) noexcept = delete;
	UCupheadCore& operator=(const UCupheadCore& _Other) = delete;
	UCupheadCore& operator=(UCupheadCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;
private:
	void CreateDebugWindows();
	void CreateMaterials();
	void LoadResources();
	void CreateLevels();

	std::shared_ptr<UCupheadDebugWindow> DebugWindow = nullptr;
};

