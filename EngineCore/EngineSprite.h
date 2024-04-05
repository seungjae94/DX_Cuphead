#pragma once
#include <EnginePlatform/EngineResources.h>

#include <vector>
#include "EngineTexture.h"

class UEngineTexture;
struct FSpriteInfo
{
	// UV값 0.0에서부터
	FVector CuttingPosition = FVector::Zero;
	// 1,1 까지를 
	FVector CuttingSize = FVector::One;
	std::shared_ptr<UEngineTexture> Texture = nullptr;
};

// 설명 :
class UEngineSprite : public UEngineResources<UEngineSprite>
{
public:
	// constrcuter destructer
	UEngineSprite();
	~UEngineSprite();

	// delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> LoadFolder(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, FileName);
		NewRes->ResLoadFolder();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> CreateCutting(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, FileName);
		NewRes->ResLoadFolder();
		return NewRes;
	}



	FSpriteInfo GetSpriteInfo(UINT _Index)
	{
		return Infos[_Index];
	}

	// static std::shared_ptr<UEngineSprite> LoadFolder();

protected:

private:
	std::vector<FSpriteInfo> Infos;

	void ResLoad();

	void ResLoadFolder();
};

