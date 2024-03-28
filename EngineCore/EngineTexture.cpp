#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

UEngineTexture::UEngineTexture() 
{
}

UEngineTexture::~UEngineTexture() 
{
	if (nullptr != RTV)
	{
		RTV->Release();
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::CreateRes(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("��������� ���� �ؽ�ó�� ����Ÿ�ٺ並 �����Ϸ��� �߽��ϴ�.");
		return;
	}

	// ���� �ؽ�ó �޸𸮿��� �̹����� �����Ҽ� �ִ� ������ �����
	// ���̷�Ʈ���� ������ �Ϸ��� �ٺ������� 2���� ���õǾ� �ֽ��ϴ�.
	// �޸� => Device
	// ������ => Context
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("����Ÿ�� �� ������ �����߽��ϴ�.");
		return;
	}
}