#pragma once
#include <EnginePlatform/EngineResources.h>
#include <map>

#include "EngineBuffer.h"
#include "EngineShader.h"
#include "EngineEnums.h"
// ���� :
class UEngineStructuredBuffer
{
public:
	// constrcuter destructer
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	// delete Function
	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

protected:

private:
	ID3D11ShaderResourceView* SRV = nullptr; // ���̴��� �������ټ� �ִ� ����.

	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);
};

