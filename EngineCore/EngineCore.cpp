#include "EngineCore.h"
#include "EngineOption.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

UEngineWindow UEngineCore::EngineWindow;

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}


void UEngineCore::Start(HINSTANCE _Inst)
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("bin");

	UEngineFile FIle = Dir.GetPathFromFile("EngineOption.EData");
	FEngineOption Option;
	if (false == FIle.IsExists())
	{
		UEngineSerializer Ser;
		Option.Serialize(Ser);

		FIle.Open(EIOOpenMode::Write, EIODataType::Text);
		FIle.Save(Ser);
	}

	{
		UEngineSerializer Ser;
		FIle = Dir.GetPathFromFile("EngineOption.EData");
		FIle.Open(EIOOpenMode::Read, EIODataType::Text);
		FIle.Load(Ser);
		Option.DeSerialize(Ser);
	}

	EngineWindow.Open();
	//UEngineWindow::WindowMessageLoop(
	//	std::bind(&UEngineCore::Update, &Core),
	//	std::bind(&UEngineCore::End, &Core)
	//);
}