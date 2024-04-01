// 쉐이더는 기본적으로
// hlsl이라는 전혀 다른 언어를 사용합니다.
// C++을 익혔다면 그닥 어렵지는 않지만
// 센스가 없으면 고생할수 있습니다.
// 언제나 랜더링 파이프라인 지식에 기반해서 작성해줘야 합니다.

// 함수의 이름은 내맘대로 해도 됩니다.
// 그런데 어떠한 규칙을 만들면 편해져요
// 이 규칙은 회사마다 다르고
// 여러분들은 애초에 엔진이나 그래픽스 프로그래머로 들어간다면
// 각 쉐이더 뒤쪽에는 버텍스면 _VS
// 각 쉐이더 뒤쪽에는 픽셀이면 _PS
// 규칙을 만들었습니다. <= 회사마다 매번 달라질수 있다.

#include "EngineVertex.hlsli"

// 리턴할 구조체도 만들어야 한다.
struct ImageVSOutPut
{
    float4 POSITION : SV_POSITION;
};

// std::vector<FEngineVertex> VertexData;
//for(int i = 0;i < VertexData.size(), ++i)
//{
    ImageVSOutPut ImageShader_VS(FEngineVertex _Input)
    {
        // 언어를 배울때는 왜 안돼 어리석은 초보적인 생각은 그만두고 배워야한다.
        // 그냥 구조체처럼 초기화 하는게 안되는데.
        ImageVSOutPut Out = (ImageVSOutPut) 0;
        Out.POSITION = _Input.POSITION;
        return Out;
    }
//}

struct ImagePSOutPut
{
    float4 COLOR : SV_Target0;
};

// C++코드로 표현한겁니다.
// std::vector<Pixel> Pixels
//for(int i = 0;i < Pixels.size(), ++i)
//{
    ImagePSOutPut ImageShader_PS(ImageVSOutPut _Input)
    {
        // 언어를 배울때는 왜 안돼 어리석은 초보적인 생각은 그만두고 배워야한다.
        // 그냥 구조체처럼 초기화 하는게 안되는데.
        ImagePSOutPut Out = (ImagePSOutPut) 0;
    
        Out.COLOR = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
        return Out;
    }
//}