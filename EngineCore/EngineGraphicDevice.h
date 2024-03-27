#pragma once

// ���� : ��� ��Ƽ�÷��� �����̸� OpenGl�� ����Ҽ� �ְ�
//        Directx�� ����Ҽ��� �������̴�.
//        �Ϲ������� ������ ���⿡�� �̰� � ���̺귯���� �����ϴ��� �������� �ȵȴ�.

class UEngineWindow;

class UEngineGraphicDevice
{
public:
	// constrcuter destructer
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	// nullptr�� ���ɼ��� ���ֹ����� ���ؼ�
	void Initialize(const UEngineWindow& _Window);

protected:

private:
	// 9���������� Device��� �������̽� �ۿ� ������.
	// �翬�� ���Ұ� ��������ϱ� �ڵ� ����̴�.
	// ID3D9Device* Device; <= com��ü ����� ǥ���̶�µ�
	// Device->MeshRender(); �׸���
	// Device->LoadTexture(); ���ҽ� �����Ҷ�
	// ���� ���� �ܼ����� �ʽ��ϴ�.

	// 11�ͼ� 2���� �о߷� �������̽��� �и��ߴ�.

	// Device->LoadTexture(); ���ҽ� �����Ҷ�
	ID3D11Device* Device = nullptr;

	// Context->MeshRender(); �׸���
	ID3D11DeviceContext* Context = nullptr;

	const class UEngineWindow* WindowPtr;

	// �׷���ī���� ���� ����� ���� �׷���ī�带 �������� �Լ�
	IDXGIAdapter* GetHighPerFormanceAdapter();
};

