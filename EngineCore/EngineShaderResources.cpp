#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineConstantBuffer.h"

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
			std::string UpperName = UEngineString::ToUpper(ResDesc.Name);
			ConstantBuffers[_Type][UpperName].Res = Buffer;
			break;
		}
		case D3D_SIT_TEXTURE:
			break;
		case D3D_SIT_SAMPLER:
			break;
		default:
			MsgBoxAssert("ó���Ҽ� ���� Ÿ���Դϴ�.");
			break;
		}


		int a = 0;
	}

	CompileInfo->Release();

	int a = 0;
}