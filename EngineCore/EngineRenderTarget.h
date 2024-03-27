#pragma once
#include <EnginePlatform/EngineResources.h>

// ���� : �ؽ�ó�� �׸��� ������ �ٸ���?
// �ؽ�ó => �̹��� ����ü ��������� ���� HBITMAP

// ����Ÿ�� => �� �̹����� �����ϰ� �׸��� �����ϴ� ����� ���� ��. UWindowImage

class UEngineTexture;
class UEngineRenderTarget : public UEngineResources<UEngineRenderTarget>
{
public:
	// constrcuter destructer
	UEngineRenderTarget();
	~UEngineRenderTarget();

	// delete Function
	UEngineRenderTarget(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget(UEngineRenderTarget&& _Other) noexcept = delete;
	UEngineRenderTarget& operator=(const UEngineRenderTarget& _Other) = delete;
	UEngineRenderTarget& operator=(UEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineRenderTarget> Create(std::shared_ptr<UEngineTexture> _Texture)
	{
		std::shared_ptr<UEngineRenderTarget> NewRes = CreateResUnName();
		NewRes->AddNewTexture(_Texture);
		return NewRes;
	}

protected:

private:
	void AddNewTexture(std::shared_ptr<UEngineTexture> _Texture);

	// �� �ؽ�ó �������� ��� ����Ҽ� �ְ� �Ұ̴ϴ�.
	std::vector<std::shared_ptr<UEngineTexture>> Textures;

};

