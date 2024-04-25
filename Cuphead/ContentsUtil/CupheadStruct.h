#pragma once

struct FCreateAnimationParameter
{
public:
	FCreateAnimationParameter()
		: AnimName(""), ImageName(""), Interval(0.0f)
	{
	}

	FCreateAnimationParameter(std::string_view _AnimName, std::string_view _ImageName, float _Interval)
		: AnimName(_AnimName), ImageName(_ImageName), Interval(_Interval)
	{
	}

	std::string AnimName;
	std::string ImageName;
	float Interval;
};