#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

class USetterBase
{
public:
	EShaderType Type = EShaderType::NONE;
	int Slot = -1; // b0, b1, b2
};

// setter��� �༮�� ��� ���� �̴ϴ�.
class UEngineConstantBufferSetter : public USetterBase
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	// �� ���͸��� ������ �ִ� �����͸� ������ �༮
	const void* CPUData = nullptr;
	UINT BufferSize = 0;

	void Setting();
};

class UEngineTextureSetter : public USetterBase
{
public:
	std::shared_ptr<class UEngineTexture> Tex;
	std::shared_ptr<class UEngineSampler> Smp;
	//void Setting();
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

	void SettingAllShaderResources();

protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);

	// �ȼ����̴��� 
	// ���ؽ� ���̴� 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

	std::map<EShaderType, std::map<std::string, UEngineTextureSetter>> Textures;

};

