#pragma once

class UPhysics
{
	friend AActor;
public:
	UPhysics(AActor* _Actor);
	~UPhysics();

	UPhysics(const UPhysics& _Other) = delete;
	UPhysics(UPhysics&& _Other) noexcept = delete;
	UPhysics& operator=(const UPhysics& _Other) = delete;
	UPhysics& operator=(UPhysics&& _Other) noexcept = delete;

	void SetVelocityX(float _X);
	void AddForce(FVector _Force);
	void Update(float _DeltaTime);


protected:

private:
	AActor* Actor = nullptr;

	static const FVector Gravity;
	bool OnGroundValue = true;
	FVector Velocity = FVector::Zero;
};

