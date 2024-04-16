#pragma once

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

	void SetDirection(EDirection _Direction);

protected:

private:
	// ������Ʈ
	UDefaultSceneComponent* Root = nullptr;
	USpriteRenderer* Renderer = nullptr;
	UCollision* Collision = nullptr;
private:
	UStateManager StateManager;
	EDirection Direction = EDirection::Right;

	const int Damage = 40;
	const float Speed = 2000.0f;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void DebugMsgUpdate(float _DeltaTime);
private:
	// �ʱ�ȭ �Լ�
	void AnimationInit();
	void StateInit();
	
private:
	// ��ƿ �Լ�
	void RefreshRotation();

private:
	// ���� �Լ�
	void Move(float _DeltaTime);
};

