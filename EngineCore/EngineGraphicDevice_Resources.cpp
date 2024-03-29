#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineTexture.h"

void UEngineGraphicDevice::EngineResourcesRelease()
{
	// ������ �ڵ����� �������� ���ҽ����� �� ���� ���⼭ Ŭ��� ���� ������?
	// ������ ����Ǵ� ������ �ؽ�ó�� ��δ� �����Ѵ�.
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();
}


// �������� �ڽ��ϳ��� ���������ָ� 
void UEngineGraphicDevice::EngineResourcesInit()
{
	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);
		// 0     1
		//   �߾�
		// 3     2
		// w�� 1�� �־���.

		// �̳༮������ �׷���ī�忡�� ������ ����� ���� ���� ��������.
		VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} };
		VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f} };
		VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f} };

		// ���� ���۰� �ƴϴ�.
		// �簢���� ���� ���մϴ�. directx�� �ﰢ�����θ� �ȼ��� �������� �ִ�. 
		// �ﰢ������ �׷��� ���� ��������µ� ���� 4���� �־���.
		std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);

		// �ﰢ���� ��� �׸����� ���� ����.
		std::vector<UINT> IndexData = {0, 1, 2, 0, 2, 3};

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");

		// IndexBuffer
	}
}