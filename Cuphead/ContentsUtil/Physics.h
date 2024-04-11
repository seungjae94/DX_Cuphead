#pragma once

class UPhysics
{
public:
	UPhysics(const UPhysics& _Other) = delete;
	UPhysics(UPhysics&& _Other) noexcept = delete;
	UPhysics& operator=(const UPhysics& _Other) = delete;
	UPhysics& operator=(UPhysics&& _Other) noexcept = delete;


	void Update(float _DeltaTime);

protected:

private:
	static const float Gravity;
	bool IsOnGround = false;
	FVector Velocity = FVector::Zero;

	UPhysics();
	~UPhysics();
};

