#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <sstream>
#include <iostream>
#include <format>

// ���� : ������ �ɼ� �����͸� �����ϴ� �뵵�� ����ü
// ���ο� ���� �̿��� ���� ������ ���װ� ������.
// �����Լ� ������ std::string ����� ���� �ȵǴµ�.
// std::string�� �ȵ��°� �ʹ� ��������?
struct FEngineOption : public UEngineSerializeObject
{
public:
	FVector WindowScale = FVector::Zero;
	bool IsDebug = false;

	void Serialize(UEngineSerializer& _Ser) override
	{
		{
			// c++ 20���� ���ڿ� �ֽ� ������ ���Ծ��.

			std::string DebugOptionText;

			DebugOptionText += std::format("WindowScale : [{}], [{}]\n", WindowScale.iX(), WindowScale.iY());
			DebugOptionText += std::format("IsDebug : [{}]\n", IsDebug);

			_Ser.WriteText(DebugOptionText);
		}
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		std::string OptionText = _Ser.ToString();

		std::vector<std::string> Values = UEngineString::StringCutting(OptionText, "[", "]");
	}

};

