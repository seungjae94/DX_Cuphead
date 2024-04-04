#pragma once
#include <EnginePlatform/EngineResources.h>

// Ό³Έν :
class UEngineSampler : public UEngineResources<UEngineSampler>
{
public:
	// constrcuter destructer
	UEngineSampler();
	~UEngineSampler();

	// delete Function
	UEngineSampler(const UEngineSampler& _Other) = delete;
	UEngineSampler(UEngineSampler&& _Other) noexcept = delete;
	UEngineSampler& operator=(const UEngineSampler& _Other) = delete;
	UEngineSampler& operator=(UEngineSampler&& _Other) noexcept = delete;

protected:

private:

};

