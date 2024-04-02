#pragma once
#include <EnginePlatform/EngineResources.h>

// ���� :
class UEngineConstantBuffer : public UEngineResources<UEngineConstantBuffer>
{
public:
	// constrcuter destructer
	UEngineConstantBuffer();
	~UEngineConstantBuffer();

	// delete Function
	UEngineConstantBuffer(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer(UEngineConstantBuffer&& _Other) noexcept = delete;
	UEngineConstantBuffer& operator=(const UEngineConstantBuffer& _Other) = delete;
	UEngineConstantBuffer& operator=(UEngineConstantBuffer&& _Other) noexcept = delete;

protected:

private:

};

