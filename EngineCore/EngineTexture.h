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

	// 이미지 그 자체.
	// Directx에서는 메모리를 의미하는 핸들
	// 그리고 그런 메모리가 있어야 메모리 수정권한
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx에서는 이미지(메모리) 수정 권한(여기에 그릴수 있는 권한)
	ID3D11RenderTargetView* RTV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	std::shared_ptr<UEngineSampler> Sampler;

	void CreateRes(ID3D11Texture2D* _Texture);

	void CreateRenderTargetView();
};

