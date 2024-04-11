#pragma once

class APlayer : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

protected:

private:
	const float RunSpeed = 400.0f;
	EDirection Direction = EDirection::Right;
	UStateManager StateManager;
	USpriteRenderer* Renderer = nullptr;
private:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// �ִϸ��̼� �ʱ�ȭ
	void AnimationInit();

	// ���� �ʱ�ȭ
	void StateInit();

	// ���� �Լ�
	void IdleStart();
	void Idle(float _DeltaTime);
	void IdleEnd();

	void RunStart();
	void Run(float _DeltaTime);
	void RunEnd();

private:
	// ��ƿ �Լ�
	bool IsPressArrowKey();
};

