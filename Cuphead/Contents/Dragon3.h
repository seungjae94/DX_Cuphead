#pragma once
#include "Enemy.h"

class Dragon3 : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	Dragon3();
	~Dragon3();

	Dragon3(const Dragon3& _Other) = delete;
	Dragon3(Dragon3&& _Other) noexcept = delete;
	Dragon3& operator=(const Dragon3& _Other) = delete;
	Dragon3& operator=(Dragon3&& _Other) noexcept = delete;

protected:


private:


};

