#pragma once
#include <EngineBase/EngineSerializer.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineString.h>
#include <sstream>
#include <iostream>
#include <format>

// 설명 : 엔진의 옵션 데이터를 저장하는 용도의 구조체
// 내부에 값형 이외의 것을 넣으면 너죽고 나죽자.
// 가상함수 포인터 std::string 등등이 들어가면 안되는데.
// std::string이 안들어가는건 너무 불편하죠?
struct FEngineOption : public UEngineSerializeObject
{
public:
	FVector WindowScale = FVector::Zero;
	bool IsDebug = false;

	void Serialize(UEngineSerializer& _Ser) override
	{
		{
			// c++ 20에서 문자열 최신 버전이 나왔어요.

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

