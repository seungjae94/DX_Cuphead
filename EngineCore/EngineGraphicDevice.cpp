#include "PreCompile.h"
#include "EngineGraphicDevice.h"

// ���̷�Ʈ ���̺귯���� ����ϱ� ���ؼ�


UEngineGraphicDevice::UEngineGraphicDevice() 
{
}

UEngineGraphicDevice::~UEngineGraphicDevice() 
{
	if (nullptr == Context)
	{
		Context->Release();
	}

	if (nullptr == Device)
	{
		Device->Release();
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
	// �׷���ī�尡 2����

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// IDXGIFactory* Factory�� ���̷�Ʈx ���̺귯���� ����� �뵵�� 
	// �������̽��Դϴ�
	// Adapter�� ����� ������  Factory �ʿ��ϴ�.
	// CreateDXGIFactory()
	
	// ���� ���� �ȵǸ� �������
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�");
		return nullptr;
	}

	size_t VideoMemory = 0;
	// �׷���ī�� ���� ū�ְ�
	// ���� ������ ���� �׷���ī���� �����ϰڴ�

	for (int Index = 0;; Index++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// ������ ���� ��Ͱ� �ִٸ�
				// �� ��ʹ� ����������
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}

void UEngineGraphicDevice::Initialize(const UEngineWindow& _Window)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("Open ���� ���� ������� �׷���ī�� ��ġ�� �ʱ�ȭ�Ϸ��� �߽��ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// ����� ����϶���
	//  D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,
	//	D3D11_CREATE_DEVICE_DEBUG = 0x2,
	//	D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,
	//	D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
	//	D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,
	//	D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,
	//	D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
	//	D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,
	//	D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800


	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// �� �׷���ī�尡 ���̷�Ʈ x�� ��������� �����Ҽ� �ִ��� �˾Ƴ��� ���� ����
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �׷���ī�带 ��ǥ�ϴ� �ڵ�
	// �ִ� ���� �׷���ī�带 ã�� ���� �Լ�
	IDXGIAdapter* Adapter = GetHighPerFormanceAdapter();

	if (nullptr == Adapter)
	{
		MsgBoxAssert("�׷���ī�尡 �������� �ʴ� ��ǻ�� �Դϴ�");
		return;
	}

	// �׷���ī�带 ã������
	// Adapter �׷���ī�忡 ����� ������ �ִ� �׷���ī�忡 ����� ������ �ִ� ����̽��� ���ؽ�Ʈ�� ����̴ϴ�.

	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN  // �ϰ� �˾Ƽ� ����
	// D3D_DRIVER_TYPE_HARDWARE	= ( D3D_DRIVER_TYPE_UNKNOWN + 1 ) , �׷���ī���
	// D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1), // Ưȭ�� ���Ҳ�
	// D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),
	// D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1), Cpu�� �����Ҳ�.
	// D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)

	// �Լ��� �뵵�� 2���ΰž�

	HRESULT Result = D3D11CreateDevice(
		Adapter, // nullptr; ���̷�Ʈ x�� 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // -0 
		nullptr,
		iFlag,
		nullptr, // ��ó���� ���������ε�
		0, // ���߿��� ���� ���ð����� ��ó������ ��������� 
		D3D11_SDK_VERSION, // 
		&Device,
		&Level, // ���� ������ ��ó����
		&Context
	);

	if (nullptr == Context)
	{
		MsgBoxAssert("�׷���ī�尡 ������ ���� ���� ���ؽ�Ʈ�� �����ϴµ� �����߽��ϴ�.");
		return;
	}

	if (nullptr == Device)
	{
		MsgBoxAssert("�׷���ī�尡 �޸����� ���� ����̽��� �����ϴµ� �����߽��ϴ�.");
		return;
	}
	
	// �� ������ ��� ������ null�˻�
	// ������ü�� ������ �׳� �ϴ°Ŵϱ�.
	if (nullptr != Adapter)
	{
		Adapter->Release();
	}

	if (S_OK != Result)
	{
		MsgBoxAssert("����̽� ������ �����߽��ϴ�.");
		// DWORD Result = GetLastError(); // �� ������ ���ؼ� �ڼ��ϰ� �˼� �ִ�.
		// ������ ����
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("���̷�Ʈ 11������ ����Ҽ� ���� �׷���ī�� �Դϴ�.");
		return;
	}

	// CPU���� ���� ��Ƽ������ε� �����ϰ� �����ϰ� �ϰڴ�.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		MsgBoxAssert("��Ƽ������ �ɼ��� ����� ���� �����ϴ�.");
		return;
	}

	WindowPtr = &_Window;

}