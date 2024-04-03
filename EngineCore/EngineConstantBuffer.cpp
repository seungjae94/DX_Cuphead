#include "PreCompile.h"
#include "EngineConstantBuffer.h"
#include "EngineCore.h"

std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineConstantBuffer>>>> UEngineConstantBuffer::ConstantBuffers;

UEngineConstantBuffer::UEngineConstantBuffer() 
{
}

UEngineConstantBuffer::~UEngineConstantBuffer() 
{
}

void UEngineConstantBuffer::ResCreate(UINT _ByteSize)
{
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// CPU���� ��������� ������ ���� ����ڴ�.
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	// �ٲ��.
	// ���� �߸� �����Ѱ� �����ϴ�.
	// D3D11_USAGE_DEFAULT
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}