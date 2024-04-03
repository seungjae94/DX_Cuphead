#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

// setter라는 녀석을 들고 있을 겁니다.
class UEngineConstantBufferSetter
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	// 각 액터마다 가지고 있는 데이터를 세팅할 녀석
	void* SettingCPU = nullptr;
};

// 설명 :
class URenderer;
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;
	friend URenderer;

public:

protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);

	// 픽셀쉐이더랑 
	// 버텍스 쉐이더 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

};

