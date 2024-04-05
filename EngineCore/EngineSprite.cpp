#include "PreCompile.h"
#include "EngineSprite.h"

UEngineSprite::UEngineSprite() 
{
}

UEngineSprite::~UEngineSprite() 
{
}


void UEngineSprite::ResLoad()
{
	FSpriteInfo TextureInfo;

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(GetName());

	if (nullptr == Texture)
	{
		Texture = UEngineTexture::Load(GetPath());
	}

	TextureInfo.Texture = Texture;

	Infos.push_back(TextureInfo);
}

void UEngineSprite::ResLoadFolder()
{
	UEngineDirectory Dir = GetEnginePath();

	std::vector<UEngineFile> Files = Dir.GetAllFile({".png", ".jpg", ".jpeg", ".gif", ".bmp" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FileName = Files[i].GetFileName();

		std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(FileName);

		if (nullptr == Texture)
		{
			Texture = UEngineTexture::Load(GetPath());
		}
		FSpriteInfo TextureInfo;
		TextureInfo.Texture = Texture;
		Infos.push_back(TextureInfo);
	}


	int a = 0;
}