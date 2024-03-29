#include "PreCompile.h"
#include "EngineVertexBuffer.h"
#include "EngineCore.h"

UEngineVertexBuffer::UEngineVertexBuffer() 
{
}

UEngineVertexBuffer::~UEngineVertexBuffer() 
{
}

void UEngineVertexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	// ���̷�Ʈ���� � �޸𸮸� �Ҵ��Ҷ� �ʱⰪ�� �־��ְ� ������
	// �̰ɷ� �־���� �մϴ�.
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	// ũ��
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);
	// �뵵
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU���� ���ٰ����Ѱ�?
	BufferInfo.CPUAccessFlags = 0;
	// ��������Ұž�?
	// D3D11_USAGE_DEFAULT �׷���ī�忡 ��������.
	// D3D11_USAGE_DYNAMIC �ϴ� �׷���ī�� ���� ������ Ram
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;


	// CreateVertexBuffer ���� �Լ��� �ƶ�
	// ���۰迭�� �Ʒ��� �Լ��� ����
	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}