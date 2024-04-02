#pragma once
#include "EngineShaderResources.h"

class UEngineInputLayOut;
// ���� :
class UEngineShader
{
	friend UEngineInputLayOut;

public:
	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

	UEngineShaderResources Resources;

protected:
	// �����ϵ� ���̴��ڵ��� �ڵ��Դϴ�.
	// �����ϵ� ������� ���⿡ ���ٰ� �ϰ� �����ϰų� Ư�� �Լ����� ����Ҷ� �ʿ��մϴ�.
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;

	std::string EntryName = "NONE";

	void ShaderResCheck();

private:

};

