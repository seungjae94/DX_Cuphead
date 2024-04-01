#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer() 
{
}

URenderer::~URenderer() 
{
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// ����� �Ѵ�/
	GetWorld()->PushRenderer(shared_from_this());
}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	int a = 0;
}

void URenderer::Render(float _DeltaTime)
{
	// ������ ��������ϴ�.

	// ���⿡�� �̰� �ϴ� ������ �� 1���Դϴ�.
	// ���������� ������������������ ������ ���� �������ַ��� �ͻ�����
	// �� �Ʒ��� ������� ������ �ؾ߸� �������� �Ǵ°� �ƴϿ���.
	// Mesh->Setting()
	Mesh->InputAssembler1Setting();
	Material->VertexShaderSetting();
	Mesh->InputAssembler2Setting();
	Material->RasterizerSetting();
	Material->PixelShaderSetting();
	Mesh->IndexedDraw();
}	


void URenderer::SetMesh(std::string_view _Name)
{
	Mesh = UEngineMesh::FindRes(_Name);

	if (nullptr == Mesh)
	{
		MsgBoxAssert("�������� �ʴ� �Ž��� �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}

}

void URenderer::SetMaterial(std::string_view _Name)
{
	Material = UEngineMaterial::FindRes(_Name);

	if (nullptr == Material)
	{
		MsgBoxAssert("�������� �ʴ� ��Ƽ���� �����Ϸ��� �߽��ϴ�." + std::string(_Name));
		return;
	}
}