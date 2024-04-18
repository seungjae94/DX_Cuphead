#pragma once

class UCupheadDebugWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow)
public:
	UCupheadDebugWindow();
	~UCupheadDebugWindow();

	UCupheadDebugWindow(const UCupheadDebugWindow& _Other) = delete;
	UCupheadDebugWindow(UCupheadDebugWindow&& _Other) noexcept = delete;
	UCupheadDebugWindow& operator=(const UCupheadDebugWindow& _Other) = delete;
	UCupheadDebugWindow& operator=(UCupheadDebugWindow&& _Other) noexcept = delete;

	void RegisterCallback(std::string_view _Key, std::function<void()> _Callback);

protected:
	void Init() override;
	void Tick(ULevel* _Level, float _Delta);
	void OnGui(ULevel* _Level, float _Delta);
private:
	std::map<std::string, std::function<void()>> Callbacks;
};

