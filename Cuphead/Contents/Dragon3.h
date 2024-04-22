#pragma once
#include "Enemy.h"

class ADragon3 : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	ADragon3();
	~ADragon3();

	ADragon3(const ADragon3& _Other) = delete;
	ADragon3(ADragon3&& _Other) noexcept = delete;
	ADragon3& operator=(const ADragon3& _Other) = delete;
	ADragon3& operator=(ADragon3&& _Other) noexcept = delete;

protected:


private:


};

