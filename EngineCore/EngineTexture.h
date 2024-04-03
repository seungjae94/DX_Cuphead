#pragma once
#include <map>
#include <string>
#include <memory>
#include <list>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineResources.h>

#include "EngineSampler.h"

class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->CreateRes(_Texture);
		return NewRes;
	}

	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

protected:


private:

	// �̹��� �� ��ü.
	// Directx������ �޸𸮸� �ǹ��ϴ� �ڵ�
	// �׸��� �׷� �޸𸮰� �־�� �޸� ��������
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx������ �̹���(�޸�) ���� ����(���⿡ �׸��� �ִ� ����)
	ID3D11RenderTargetView* RTV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	std::shared_ptr<UEngineSampler> Sampler;

	void CreateRes(ID3D11Texture2D* _Texture);

	void CreateRenderTargetView();
};

