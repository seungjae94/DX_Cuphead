#pragma once
class UCupheadMath
{
public:
	UCupheadMath();
	~UCupheadMath();

	UCupheadMath(const UCupheadMath& _Other) = delete;
	UCupheadMath(UCupheadMath&& _Other) noexcept = delete;
	UCupheadMath& operator=(const UCupheadMath& _Other) = delete;
	UCupheadMath& operator=(UCupheadMath&& _Other) noexcept = delete;

	static float PI;
	static FVector DegToDirection(float _Deg);
	static FVector RadToDirection(float _Rad);

	// return: [0, 360)
	static float DirectionToDeg(const FVector& _Direction);

	// return: [0, 2*PI)
	static float DirectionToRad(const FVector& _Direction);
	
	// return: [-180, 180)
	static float SubtractDeg(float _First, float _Second);

	template<typename T>
	static T Max(T _First, T _Second)
	{
		if (_First >= _Second)
		{
			return _First;
		}
		return _Second;
	}

protected:


private:

};

