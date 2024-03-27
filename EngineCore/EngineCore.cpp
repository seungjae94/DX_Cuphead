#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>

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
	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	EngineWindow.SetWindowScale(EngineOption.WindowScale);

	EngineDevice.Initialize(EngineWindow);

	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineUpdate, this),
		nullptr
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

void UEngineCore::EngineUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);
}