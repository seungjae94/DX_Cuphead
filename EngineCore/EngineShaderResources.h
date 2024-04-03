#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

// setter��� �༮�� ��� ���� �̴ϴ�.
class UEngineConstantBufferSetter
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	// �� ���͸��� ������ �ִ� �����͸� ������ �༮
	const void* SettingCPU = nullptr;
};

// ���� :
class URenderer;
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;
	friend URenderer;

public:
	template<typename Value>
	void SettingConstantBuffer(std::string_view _Name, Value& _Data)
	{
		SettingConstantBuffer(_Name, &_Data, static_cast<UINT>(sizeof(Value)));
	}

	void SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size);

	bool IsConstantBuffer(std::string_view _Name);


protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);

	// �ȼ����̴��� 
	// ���ؽ� ���̴� 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

};

