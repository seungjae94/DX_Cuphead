#include "PreCompile.h"
#include "Renderer.h"
#include "EngineInputLayOut.h"

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
	
	// InputAssembler1
	Mesh->InputAssembler1Setting();
	LayOut->Setting();

	// VertexShader
	Material->VertexShaderSetting();

	// InputAssembler2
	Mesh->InputAssembler2Setting();

	// Rasterizer
	Material->RasterizerSetting();

	// PixelShader
	Material->PixelShaderSetting();

	// OM

	// Draw
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

	if (nullptr != Material)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
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

	if (nullptr != Mesh)
	{
		LayOut = UEngineInputLayOut::Create(Mesh->VertexBuffer, Material->GetVertexShader());
	}
}