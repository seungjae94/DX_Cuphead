#pragma once
#include <EngineCore/EngineCore.h>

class UCupheadDebugWindow;

extern std::shared_ptr<UCupheadDebugWindow> DebugWindow;

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
	void LoadFonts();
	void LoadResources();
	void RegisterResourceNames(std::vector<std::string>& _AllFileFullNames, std::vector<std::string>& _AllFolderFullNames, std::string_view _FolderName);
	void LoadShaders();
	void CreateMaterials();
	void CreateLevels();

	std::atomic_int LoadingCount = 0;
};

