#include "PreCompile.h"
#include "CropSpriteRenderer.h"
#include <EngineCore/EngineShaderResources.h>
#include <EngineCore/EngineSprite.h>

void UCropSpriteRenderer::SetFrameCallback(std::string_view _AnimationName, int _Index, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 콜백을 지정할수 없습니다." + std::string(_AnimationName));
		return;
	}

	Animations[UpperName]->FrameCallback[_Index] = _Function;
}

void UCropSpriteRenderer::SetLastFrameCallback(std::string_view _AnimationName, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션에 콜백을 지정할수 없습니다." + std::string(_AnimationName));
		return;
	}

	std::shared_ptr<USpriteAnimation> Animation = Animations[UpperName];
	int LastIndex = static_cast<int>(Animation->Frame.size()) - 1;
	Animations[UpperName]->FrameCallback[LastIndex] = _Function;
}

UCropSpriteRenderer::UCropSpriteRenderer()
{
	SetMesh("Rect");
	SetMaterial("2DCropImage");
}

UCropSpriteRenderer::~UCropSpriteRenderer()
{
}

void UCropSpriteRenderer::SetAutoSize(float _ScaleRatio, bool _AutoSize)
{
	AutoSize = _AutoSize;
	ScaleRatio = _ScaleRatio;

	if (true == AutoSize && nullptr != CurInfo.Texture)
	{
		SetSpriteInfo(CurInfo);
	}
}

void UCropSpriteRenderer::MaterialSettingEnd()
{
	Super::MaterialSettingEnd();
	Resources->SettingTexture("Image", "EngineBaseTexture.png", "POINT");
	CurTexture = nullptr;
	Resources->SettingConstantBuffer("ResultColorValue", ColorData);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
	Resources->SettingConstantBuffer("FCropData", CropDataValue);
}


void UCropSpriteRenderer::Crop(FVector _CropPosition, FVector _CropSize)
{
	if (_CropSize.X < 0.0f)
	{
		_CropSize.X = 0.0f;
	}
	else if (_CropSize.X > 1.0f)
	{
		_CropSize.X = 1.0f;
	}

	if (_CropSize.Y < 0.0f)
	{
		_CropSize.Y = 0.0f;
	}
	else if (_CropSize.Y > 1.0f)
	{
		_CropSize.Y = 1.0f;
	}

	if (_CropPosition.X < 0.0f)
	{
		_CropPosition.X = 0.0f;
	}
	else if (_CropPosition.X + _CropSize.X > 1.0f)
	{
		_CropPosition.X = 1.0f - _CropSize.X;
	}

	if (_CropPosition.Y < 0.0f)
	{
		_CropPosition.Y = 0.0f;
	}
	else if (_CropPosition.Y + _CropSize.Y> 1.0f)
	{
		_CropPosition.Y = 1.0f - _CropSize.Y;
	}

	CropDataValue.CropPosition = _CropPosition;
	CropDataValue.CropSize = _CropSize;

	if (true == AutoSize && nullptr != CurInfo.Texture)
	{
		SetSpriteInfo(CurInfo);
	}
}

void UCropSpriteRenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	if (nullptr != CurAnimation)
	{
		CurAnimation->Update(_DeltaTime);

		FSpriteInfo Info = CurAnimation->GetCurSpriteInfo();
		SetSpriteInfo(Info);
	}
}

void UCropSpriteRenderer::SetDir(EEngineDir _Dir)
{
	Dir = _Dir;

	if (nullptr != CurInfo.Texture)
	{
		SetSpriteInfo(CurInfo);
	}
}

void UCropSpriteRenderer::SetSpriteInfo(const FSpriteInfo& _Info)
{
	CuttingDataValue.CuttingPosition = _Info.CuttingPosition;
	CuttingDataValue.CuttingSize = _Info.CuttingSize;
	CurTexture = _Info.Texture;

	if (true == AutoSize)
	{
		float4 TexScale = _Info.Texture->GetScale();
		Transform.SetScale(TexScale * CuttingDataValue.CuttingSize * CropDataValue.CropSize * ScaleRatio);
	}

	switch (Pivot)
	{
	case EPivot::BOT:
	{
		float4 Scale = Transform.WorldScale;
		Scale.X = 0.0f;
		Scale.Y = abs(Scale.Y) * 0.5f;
		Scale.Z = 0.0f;
		CuttingDataValue.PivotMat.Position(Scale);
		break;
	}
	case EPivot::RIGHT:
	{
		float4 Scale = Transform.WorldScale;
		Scale.X = -abs(Scale.X) * 0.5f;
		Scale.Y = 0.0f;
		Scale.Z = 0.0f;
		CuttingDataValue.PivotMat.Position(Scale);
		break;
	}
	case EPivot::LEFTTOP:
	{
		float4 Scale = Transform.WorldScale;
		Scale.X = abs(Scale.Y) * 0.5f;
		Scale.Y = -abs(Scale.X) * 0.5f;
		Scale.Z = 0.0f;
		CuttingDataValue.PivotMat.Position(Scale);
		break;
	}
	case EPivot::LEFTBOTTOM:
	{
		float4 Scale = Transform.WorldScale;
		Scale.X = abs(Scale.X) * 0.5f;
		Scale.Y = abs(Scale.Y) * 0.5f;
		Scale.Z = 0.0f;
		CuttingDataValue.PivotMat.Position(Scale);
		break;
	}
	case EPivot::RIGHTBOTTOM:
	{
		float4 Scale = Transform.WorldScale;
		Scale.X = -abs(Scale.X) * 0.5f;
		Scale.Y = abs(Scale.Y) * 0.5f;
		Scale.Z = 0.0f;
		CuttingDataValue.PivotMat.Position(Scale);
		break;
	}
	case EPivot::MAX:
	default:
	{
		CuttingDataValue.PivotMat.Identity();
	}
	break;
	}

	if (Dir != EEngineDir::MAX)
	{
		float4 Scale = Transform.GetScale();

		switch (Dir)
		{
		case EEngineDir::Left:
		{
			if (0 < Scale.X)
			{
				Scale.X = -Scale.X;
			}
			break;
		}
		case EEngineDir::Right:
		{
			if (0 > Scale.X)
			{
				Scale.X = -Scale.X;
			}
			break;
		}
		case EEngineDir::MAX:
		default:
			break;
		}

		Transform.SetScale(Scale);
	}

	CurInfo = _Info;

	Resources->SettingTexture("Image", _Info.Texture, "POINT");
	SetSamplering(SamplingValue);
}

void UCropSpriteRenderer::SetSprite(std::string_view _Name, UINT _Index/* = 0*/)
{
	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes(_Name);

	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 세팅해주려고 했습니다.");
		return;
	}

	FSpriteInfo Info = Sprite->GetSpriteInfo(_Index);
	SetSpriteInfo(Info);
}

void UCropSpriteRenderer::SetSamplering(ETextureSampling _Value)
{
	if (nullptr == CurTexture)
	{
		MsgBoxAssert("텍스처를 세팅하지 않은 상태에서 샘플링부터 바꿀수는 없습니다.");
		return;
	}

	switch (_Value)
	{
	case ETextureSampling::NONE:
		break;
	case ETextureSampling::LINEAR:
	{
		Resources->SettingTexture("Image", CurTexture, "LINEAR");
		break;
	}
	case ETextureSampling::POINT:
	{
		Resources->SettingTexture("Image", CurTexture, "POINT");
		break;
	}
	default:
		break;
	}
}

void UCropSpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter,
	bool _Loop /*= true*/,
	int _Start /*= -1*/,
	int _End /*= -1*/)
{
	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (nullptr == FindSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들수는 없습니다.");
		return;
	}

	std::vector<int> Frame;
	std::vector<float> Inter;

	int Start = _Start;
	int End = _End;

	if (0 > _Start)
	{
		Start = 0;
	}

	if (0 > End)
	{
		End = static_cast<int>(FindSprite->GetInfoSize()) - 1;
	}

	if (End < Start)
	{
		//MsgBoxAssert("아직 역방향 기능은 지원하지 않습니다.");
		for (int i = Start; End <= i; i--)
		{
			Inter.push_back(_Inter);
			Frame.push_back(i);
		}

		CreateAnimation(_AnimationName, _SpriteName, Inter, Frame, _Loop);
		return;
	}



	for (int i = Start; i < End + 1; i++)
	{
		Inter.push_back(_Inter);
		Frame.push_back(i);
	}

	CreateAnimation(_AnimationName, _SpriteName, Inter, Frame, _Loop);
}

void UCropSpriteRenderer::ChangeAnimation(std::string_view _AnimationName, int StartFrame)
{
	if (nullptr != CurAnimation && _AnimationName == CurAnimation->GetName())
	{
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == Animations.contains(UpperName))
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 할수 없습니다." + std::string(_AnimationName));
		return;
	}

	CurAnimation = Animations[UpperName];
	CurAnimation->Reset();
	CurAnimation->CurFrame = StartFrame;

	CurAnimation->FrameCallBackCheck();
}

void UCropSpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<float> _Inter, std::vector<int> _Frame, bool _Loop /*= true*/)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (true == Animations.contains(UpperName))
	{
		MsgBoxAssert("이미 존재하는 이름의 애니메이션은 만들수 없습니다.");
		return;
	}

	std::shared_ptr<UEngineSprite> FindSprite = UEngineSprite::FindRes(_SpriteName);

	if (nullptr == FindSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들수는 없습니다.");
		return;
	}

	std::shared_ptr<USpriteAnimation> NewAnimation = std::make_shared<USpriteAnimation>();

	NewAnimation->Sprite = FindSprite;
	NewAnimation->Inter = _Inter;
	NewAnimation->Frame = _Frame;
	NewAnimation->Loop = _Loop;
	NewAnimation->SetName(_AnimationName);
	NewAnimation->Reset();

	Animations[UpperName] = NewAnimation;
}

bool UCropSpriteRenderer::IsCurAnimationEnd()
{
	return CurAnimation->IsEnd;
}