#include "PreCompile.h"
#include "Renderer.h"
#include "EngineInputLayOut.h"
#include "EngineShaderResources.h"
#include "Camera.h"

URenderer::URenderer() 
{
	Resources = std::make_shared<UEngineShaderResources>();
}

URenderer::~URenderer() 
{
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// ����� �Ѵ�
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

	Resources->SettingAllShaderResources();
	

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

	ResCopy();

	if (true == Resources->IsConstantBuffer("FTransform"))
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
	}

}

void URenderer::ResCopy()
{

	if (nullptr != Material->GetVertexShader())
	{
		// ���ؽ����̴� ���ο��� � ������۸� ����ϰ� �ִ��� �� ��� ���� ���̴�.
		// Material->GetVertexShader()

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& RendererConstantBuffers
			= Resources->ConstantBuffers;

		std::shared_ptr<UEngineShaderResources> ShaderResources = Material->GetVertexShader()->Resources;

		std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>>& ShaderConstantBuffers
			= ShaderResources->ConstantBuffers;

		for (std::pair<const EShaderType, std::map<std::string, UEngineConstantBufferSetter>> Setters : ShaderConstantBuffers)
		{
			for (std::pair<const std::string, UEngineConstantBufferSetter> ConstantBufferSetter : Setters.second)
			{
				RendererConstantBuffers[Setters.first][ConstantBufferSetter.first] = ConstantBufferSetter.second;
			}
		}

	}
}


void URenderer::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
{
	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
}