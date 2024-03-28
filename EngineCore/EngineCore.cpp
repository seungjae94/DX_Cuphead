#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineTexture.h>
#include "Level.h"

UEngineCore::UEngineCore() 
{
}

UEngineCore::~UEngineCore() 
{
	// ������ �����Ҷ� ���� ���� �ɼ��� ���̺� �ϰ� �Ѵ�.
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
	UEngineSerializer Ser;
	EngineOption.Serialize(Ser);
	File.Open(EIOOpenMode::Write, EIODataType::Text);
	File.Save(Ser);
}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	// ��üũ
	LeakCheck;
	GEngine = this;

	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	// ����̽� �ʱ�ȭ���� ũ�Ⱑ ���������� �ػ󵵰� �̹� ���� �Ȱſ���.
	// EngineOption.WindowScale �ػ�
	// �ػ󵵴� ������ ũ��� ������ �����ϴ�.
	EngineWindow.SetWindowScale(EngineOption.WindowScale);
	EngineDevice.Initialize(EngineWindow, EngineOption.ClearColor);


	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);
}

void UEngineCore::EngineOptionInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	if (false == Dir.IsFile("EngineOption.EData"))
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		EngineOption.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		EngineOption.DeSerialize(Ser);
	}

}

void UEngineCore::EngineEnd()
{
	// ������ �ڵ����� �������� ���ҽ����� �� ���� ���⼭ Ŭ��� ���� ������?
	// ������ ����Ǵ� ������ �ؽ�ó�� ��δ� �����Ѵ�.
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
}

void UEngineCore::EngineFrameUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);

	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Tick(DeltaTime);

	// ȭ�� �����
	EngineDevice.RenderStart();
	// ���ӿ� ��ҵ��� �׸���

	// CurLevel->Render();

	// ������ �׳� �׷�����.

	// ����Ѵ�
	EngineDevice.RenderEnd();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Level->BeginPlay();
	Levels[_Name] = Level;
	return Level;
}