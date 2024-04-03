// ���̴��� �⺻������
// hlsl�̶�� ���� �ٸ� �� ����մϴ�.
// C++�� �����ٸ� �״� ������� ������
// ������ ������ ����Ҽ� �ֽ��ϴ�.
// ������ ������ ���������� ���Ŀ� ����ؼ� �ۼ������ �մϴ�.

// �Լ��� �̸��� ������� �ص� �˴ϴ�.
// �׷��� ��� ��Ģ�� ����� ��������
// �� ��Ģ�� ȸ�縶�� �ٸ���
// �����е��� ���ʿ� �����̳� �׷��Ƚ� ���α׷��ӷ� ���ٸ�
// �� ���̴� ���ʿ��� ���ؽ��� _VS
// �� ���̴� ���ʿ��� �ȼ��̸� _PS
// ��Ģ�� ��������ϴ�. <= ȸ�縶�� �Ź� �޶����� �ִ�.

#include "EngineShaderBase.hlsli"

// ��ǲ���̾ƿ��� ����
// ��ǲ���̾ƿ��� 2������ ������ �մϴ�.
// ���� ���� ���ؽ� ���۰� Ư�� �ø�ƽ ������ �ִٴ°��� ������ ����ִ� �뵵.
// 2��°�� � ���ؽ� ���̴��� � �ø�ƽ�� �� �ִ����� ���� ������ ����մϴ�.


// ������ ����ü�� ������ �Ѵ�.
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

// ���� ���⿡�ٰ� ��Ʈ��Ʈ�� �ִ´ٰ� �̰� ���̴����� 
// CPU�ʿ��� �־��ֱ�� �� �����ͷ� �������� �ʾƿ�
// CPU���� ���� ����̳� ������ ����� ����
// �־��ְ� �ʹٸ�
// ������۶�� �ϴ� �������̽��� ���� ������ �̿��ؾ߸�
// ���̷�Ʈ�� �־��ټ��� �ֽ��ϴ�.
// hlsl���� struct �̷� �����Ͱ� �����ž�. ��� ���Ǹ� �����ټ� �ְ�


//struct FTransform
//{
//    float4 Scale;
//    float4 Rotation;
//    float4 Position;
//    float4x4 ScaleMat;
//    float4x4 RotationMat;
//    float4x4 PositionMat;
//    float4x4 World;
//    float4x4 View;
//    float4x4 Projection;
//    float4x4 WVP;
//};

// ���ؽ� ���̴��� �־��ټ� ��

ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
{
    ImageVSOutPut Out = (ImageVSOutPut) 0;
    Out.POSITION = mul(_Input.POSITION, WVP);
    return Out;
}

// �ȼ����̴��� ������� 0���� �޶� �ȴ�.
cbuffer OutPutColor : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
};


struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
{
        // �� ��ﶧ�� �� �ȵ� ����� �ʺ����� ������ �׸��ΰ� ������Ѵ�.
        // �׳� ����üó�� �ʱ�ȭ �ϴ°� �ȵǴµ�.
    ImagePSOutPut Out = (ImagePSOutPut) 0;
    // Out.COLOR = Color;
    Out.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    return Out;
}
