#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

/// UEngineConstantBufferSetter
void UEngineConstantBufferSetter::Setting()
{
	// ������۸� �����Ѵ�.

	if (nullptr == CPUData)
	{
		MsgBoxAssert(Res->GetName() + " ������ۿ� ������ ������ �ʾҽ��ϴ�. ���ּ���...");
		return;
	}

	Res->ChangeData(CPUData, BufferSize);

	Res->Setting(Type, Slot);
}

///

void UEngineShaderResources::ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode)
{
	// std::string_view _EntryName <= ���� ���̴��� ���� ���ҽ��� �ִ��� Ȯ���Ϸ���

	if (nullptr == _ShaderCode)
	{
		MsgBoxAssert("�������� ������ ���̴����� ���ҽ� üũ�� �Ϸ��� �߽��ϴ�");
		return;
	}

	ID3DBlob* ShaderCode = _ShaderCode;
	// ���̷�Ʈ x�� �ڵ��˻� ��ɰ� �Լ��� �������ݴϴ�.
	// �츰 �̿��ϱ⸸ �ϸ� �˴ϴ�.

	// Reflection <= ���� ���� �ɰ��̴�.
	// �������� ������� ���մϴ�. ���α׷��ֿ���

	ID3D11ShaderReflection* CompileInfo = nullptr;

	// ���̴��� �����ϵ� ������ �м��� ����ȭ �ؼ� �츮���� �����մϴ�.
	if (S_OK != D3DReflect(ShaderCode->GetBufferPointer(), ShaderCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)))
	{
		MsgBoxAssert("���̴� ���������� �����߽��ϴ�");
		return;
	}

	D3D11_SHADER_DESC Info = {};

	CompileInfo->GetDesc(&Info);


	// Info.BoundResources ���̴� �ȿ��� ����� �� ���ҽ� ����
	// ���δ� ���ļ� �Դϴ�.
	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		D3D11_SHADER_INPUT_BIND_DESC ResDesc;

		CompileInfo->GetResourceBindingDesc(i, &ResDesc);

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;

		std::string UpperName = UEngineString::ToUpper(ResDesc.Name);

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			// ��������� ������ ������ �˷���
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC ConstantBufferDesc = {};

			BufferInfo->GetDesc(&ConstantBufferDesc);

			_EntryName;

			// ������۴� �̸��� �߿��Ѱ� �ƴ϶�
			// ����Ʈ�� �߿���.
			std::shared_ptr<UEngineConstantBuffer> Buffer = UEngineConstantBuffer::CreateAndFind(_Type, ResDesc.Name, ConstantBufferDesc.Size);

			UEngineConstantBufferSetter& NewSetter = ConstantBuffers[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			NewSetter.BufferSize = ConstantBufferDesc.Size;
			NewSetter.Res = Buffer;
			break;
		}
		case D3D_SIT_TEXTURE:
		case D3D_SIT_SAMPLER:
		{
			UEngineTextureSetter& NewSetter = Textures[_Type][UpperName];
			NewSetter.Type = _Type;
			NewSetter.Slot = ResDesc.BindPoint;
			break;
		}
		default:
			MsgBoxAssert("ó���Ҽ� ���� Ÿ���Դϴ�.");
			break;
		}


		int a = 0;
	}

	CompileInfo->Release();

	int a = 0;
}

void UEngineShaderResources::SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (false ==  ResMap.contains(UpperName))
		{
			continue;
		}

		UEngineConstantBufferSetter& Setter = ResMap[UpperName];

		if (Setter.BufferSize != _Size)
		{
			MsgBoxAssert(Setter.Res->GetName() + "�� ����Ʈ ũ�Ⱑ �ٸ��ϴ�." + std::to_string(Setter.BufferSize) + " Vs " + std::to_string(_Size));
		}

		Setter.CPUData = _Data;
	}
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		if (true == ResMap.contains(UpperName))
		{
			return true;
		}
	}

	return false;
}

void UEngineShaderResources::SettingAllShaderResources()
{
	for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& Pair : ConstantBuffers)
	{
		std::map<std::string, UEngineConstantBufferSetter>& ResMap = Pair.second;

		for (std::pair<const std::string, UEngineConstantBufferSetter>& Setter : ResMap)
		{
			Setter.second.Setting();
		}
	}

}