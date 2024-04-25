#pragma once

class APlayer;

class ABullet : public AActor
{
	GENERATED_BODY(AActor)
public:
	ABullet();
	~ABullet();

	ABullet(const ABullet& _Other) = delete;
	ABullet(ABullet&& _Other) noexcept = delete;
	ABullet& operator=(const ABullet& _Other) = delete;
	ABullet& operator=(ABullet&& _Other) noexcept = delete;

	void AnimationInit(FCreateAnimationParameter _MoveAnimParam, FCreateAnimationParameter _DestroyAnimParam);
	void SetDamage(int _Damage);
	void SetDirection(EDirection _Direction);
	void SetPlayer(APlayer* _Player);

protected:

private:
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
private:
	std::string MoveAnimName;
	std::string DestroyAnimName;
private:
	UStateManager StateManager;
	EDirection Direction = EDirection::Right;
	APlayer* Player = nullptr;

	int Damage = 4;
	const float Speed = 2000.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	// �ʱ�ȭ �Լ�
	void StateInit();
	
private:
	// ��ƿ �Լ�
	void RefreshRotation();

private:
	// ���� �Լ�
	void Move(float _DeltaTime);
};

