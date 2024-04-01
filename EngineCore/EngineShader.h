#pragma once

// ���� :
class UEngineShader
{
public:
	// constrcuter destructer
	UEngineShader();
	~UEngineShader();

	// delete Function
	UEngineShader(const UEngineShader& _Other) = delete;
	UEngineShader(UEngineShader&& _Other) noexcept = delete;
	UEngineShader& operator=(const UEngineShader& _Other) = delete;
	UEngineShader& operator=(UEngineShader&& _Other) noexcept = delete;

protected:
	// �����ϵ� ���̴��ڵ��� �ڵ��Դϴ�.
	// �����ϵ� ������� ���⿡ ���ٰ� �ϰ� �����ϰų� Ư�� �Լ����� ����Ҷ� �ʿ��մϴ�.
	ID3DBlob* ShaderCodeBlob = nullptr;
	ID3DBlob* ErrorCodeBlob = nullptr;

private:

};

