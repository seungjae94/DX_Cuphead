#pragma once
#include <EngineCore/EngineCore.h>

class UMyCore : public UserCore
{
public:
	// constructor destructor
	UMyCore();
	~UMyCore();

	// delete Function
	UMyCore(const UMyCore& _Other) = delete;
	UMyCore(UMyCore&& _Other) noexcept = delete;
	UMyCore& operator=(const UMyCore& _Other) = delete;
	UMyCore& operator=(UMyCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;
private:

};

