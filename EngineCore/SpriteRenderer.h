#pragma once
#include "Renderer.h"

// Ό³Έν :
class UEngineTexture;
class USpriteRenderer : public URenderer
{
public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetPlusColor(float4 _Color);
	void SetSamplering(ETextureSampling _Value);

	

protected:

private:
	float4 PlusColor = float4::Zero;
	std::shared_ptr<UEngineTexture> CurTexture;

};

