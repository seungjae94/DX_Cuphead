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
	// CPU에서 상수버퍼의 내용을 덮어 씌우겠다.
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	// 바뀐다.
	// 전에 잘못 설명한거 같습니다.
	// D3D11_USAGE_DEFAULT
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}