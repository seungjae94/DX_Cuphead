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
	static float DirectionToDeg(const FVector& _Direction);
	static float DirectionToRad(const FVector& _Direction);

protected:


private:

};

