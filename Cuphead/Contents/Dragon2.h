#pragma once
#include "Enemy.h"

class Dragon2 : public AEnemy
{
	GENERATED_BODY(AEnemy)
public:
	Dragon2();
	~Dragon2();

	Dragon2(const Dragon2& _Other) = delete;
	Dragon2(Dragon2&& _Other) noexcept = delete;
	Dragon2& operator=(const Dragon2& _Other) = delete;
	Dragon2& operator=(Dragon2&& _Other) noexcept = delete;

protected:


private:


};

