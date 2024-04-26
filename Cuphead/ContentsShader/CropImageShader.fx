#include "..\EngineShader\EngineShaderBase.hlsli"

struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
};

cbuffer FCuttingData : register(b2)
{
    float4 CuttingPosition;
    float4 CuttingSize;
    float4x4 PivotMat;
};

cbuffer FCropData : register(b4)
{
    float4 CropPosition;
    float4 CropSize;
};

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};


ImageVSOutPut CropImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    
    float4x4 PivotWorld = mul(World, PivotMat);
    
    Out.POSITION = mul(_Input.POSITION, PivotWorld);
    Out.POSITION = mul(Out.POSITION, View);
    Out.POSITION = mul(Out.POSITION, Projection);
    
    Out.TEXCOORD.x = (_Input.TEXCOORD.x * CuttingSize.x * CropSize.x) + CuttingSize.x * CropPosition.x + CuttingPosition.x;
    Out.TEXCOORD.y = (_Input.TEXCOORD.y * CuttingSize.y * CropSize.y) + CuttingSize.y * CropPosition.y + CuttingPosition.y;
    
    return Out;
}

TextureSet(Image, 0)

cbuffer ResultColorValue : register(b10)
{
    float4 PlusColor;
    float4 MulColor;
    float4 AlphaColor;
};


ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    
    Out.COLOR = Sampling(Image, _Input.TEXCOORD);
    Out.COLOR.xyz += PlusColor.xyz;
    Out.COLOR.xyzw *= MulColor.xyzw;
    
    return Out;
}
