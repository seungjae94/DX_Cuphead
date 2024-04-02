#include "PreCompile.h"
#include "EngineCore.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineMesh.h"
#include "EngineTexture.h"
#include "EngineVertexShader.h"
#include "EnginePixelShader.h"
#include "EngineRasterizer.h"
#include "EngineMaterial.h"

void UEngineGraphicDevice::EngineResourcesRelease()
{
	// ������ �ڵ����� �������� ���ҽ����� �� ���� ���⼭ Ŭ��� ���� ������?
	// ������ ����Ǵ� ������ �ؽ�ó�� ��δ� �����Ѵ�.
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();

	// Mesh
	UEngineVertexBuffer::ResourcesRelease();
	UEngineIndexBuffer::ResourcesRelease();
	UEngineMesh::ResourcesRelease();

	// ��Ƽ����
	UEngineVertexShader::ResourcesRelease();
	UEnginePixelShader::ResourcesRelease();
	UEngineRasterizer::ResourcesRelease();
	UEngineMaterial::ResourcesRelease();
}

// ��ǲ����� 1�� ��ǲ����� 2�� ���ҽ����� ������ �̴ϼȶ�����
void MeshInit()
{
	FEngineVertex::Info.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);
	FEngineVertex::Info.AddInputLayOut("COLOR", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

	{
		std::vector<FEngineVertex> VertexData;
		VertexData.resize(4);

		{
			VertexData[0] = { {-0.5f, 0.5f, 0.0f, 1.0f} };
			VertexData[1] = { {0.5f, 0.5f, 0.0f, 1.0f} };
			VertexData[2] = { {0.5f, -0.5f, 0.0f, 1.0f} };
			VertexData[3] = { {-0.5f, -0.5f, 0.0f, 1.0f} };
			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("Rect", VertexData);
		}

		// �ﰢ���� ��� �׸����� ���� ����.
		std::vector<UINT> IndexData = { 0, 1, 2, 0, 2, 3 };

		std::shared_ptr<UEngineIndexBuffer> IndexBuffer = UEngineIndexBuffer::Create("Rect", IndexData);

		UEngineMesh::Create("Rect");

		{
			VertexData[0].POSITION *= 2.0f;
			VertexData[1].POSITION *= 2.0f;
			VertexData[2].POSITION *= 2.0f;
			VertexData[3].POSITION *= 2.0f;
			std::shared_ptr<UEngineVertexBuffer> VertexBuffer = UEngineVertexBuffer::Create("FullRect", VertexData);
		}

		UEngineMesh::Create("FullRect", "FullRect", "Rect");
	}

	// ��ǲ���̾ƿ� ����
	// GEngine->GetDirectXDevice()->CreateInputLayout()


}

// �ȼ� �� ���ؽ����̴��� �̴ϼȶ�����
void ShaderInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("EngineShader");

	std::vector<UEngineFile> Files = Dir.GetAllFile({".fx", "hlsl"});

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FullPath = Files[i].GetFullPath();
		std::string AllShaderCode = Files[i].GetString();

		{
			// �տ������� �ڷ�
			size_t ShaderEntryEnd = AllShaderCode.find("_VS("/*, 0*/);

			if (std::string::npos != ShaderEntryEnd)
			{
				// �ڿ������� ������
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_VS";

				UEngineVertexShader::Load(FullPath.c_str(), EntryName);
			}
		}

		{
			// �տ������� �ڷ�
			size_t ShaderEntryEnd = AllShaderCode.find("_PS("/*, 0*/);

			if (std::string::npos != ShaderEntryEnd)
			{
				// �ڿ������� ������
				size_t ShaderEntryStart = AllShaderCode.rfind(" ", ShaderEntryEnd);
				std::string EntryName = AllShaderCode.substr(ShaderEntryStart + 1, ShaderEntryEnd - ShaderEntryStart - 1);
				EntryName += "_PS";

				UEnginePixelShader::Load(FullPath.c_str(), EntryName);
			}
		}
	}

	// UEngineVertexShader::Load("D:ENgineShader\MeshVertexShader", "AAAA_VS");

	//UEngineVertexShader::Load("AAA.png", EntryName);
	//UEngineVertexShader::Load("BBB.png", EntryName);
}

void SettingInit()
{
		//D3D11_FILL_MODE FillMode;
		//D3D11_CULL_MODE CullMode;
		//BOOL FrontCounterClockwise;
		//INT DepthBias;
		//FLOAT DepthBiasClamp;
		//FLOAT SlopeScaledDepthBias;
		//BOOL DepthClipEnable;
		//BOOL ScissorEnable;
		//BOOL MultisampleEnable;
		//BOOL AntialiasedLineEnable;


	D3D11_RASTERIZER_DESC Desc = {};

	// ������ �׷���
	Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	// ������ �׷���.
	// Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

	// �ո��̰� �޸��̰� �� �׷���.
	// �츮 �������� ��
	// �ո� �׸�����
	
	// Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	// �޸� �׸�����
	Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	// �ո�� �޸�
	// �ð�����̸� �޸����� ���ϴ�.

	Desc.AntialiasedLineEnable = TRUE;
	Desc.DepthClipEnable = TRUE;


	// �����Ͷ����� ����
	UEngineRasterizer::Create("EngineBasic", Desc);


	std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("2DImage");
	Mat->SetPixelShader("ImageShader.fx");
	Mat->SetVertexShader("ImageShader.fx");
	Mat->SetRasterizer("EngineBasic");

}

void MaterialInit()
{

}


// �������� �ڽ��ϳ��� ���������ָ� 
void UEngineGraphicDevice::EngineResourcesInit()
{
	MeshInit();
	ShaderInit();
	SettingInit();
	MaterialInit();
}