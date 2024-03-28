#pragma once
#include "SceneComponent.h"

// ���� : public std::enable_shared_from_this<URenderer>
// shared_ptr�� this�� �����Ҽ� �ִ� ����� ���� Ŭ�����Դϴ�.
class URenderer : public USceneComponent, public std::enable_shared_from_this<URenderer>
{
	friend ULevel;
	GENERATED_BODY(USceneComponent)

public:
	// constrcuter destructer
	URenderer();
	~URenderer();

	// delete Function
	URenderer(const URenderer& _Other) = delete;
	URenderer(URenderer&& _Other) noexcept = delete;
	URenderer& operator=(const URenderer& _Other) = delete;
	URenderer& operator=(URenderer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Render(float _DeltaTime);

};

