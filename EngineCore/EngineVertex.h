#pragma once
#include <EngineBase/EngineMath.h>

// 3D�� �׷����� ���� ��ġ�� �����ʿ䰡 �����ϴ�.
// ����
// ��ġ ����� �� ����

// �̰� ���� ������ ������ �ȴ�.
// �� 1���� �����ϴ� ��ҵ��� ���� ������� ������ �ִ�.
// �װ� directx�� �˾ƿ� �����?
// ���� �������
// �� ���� ��� �־�� �մϱ�?
// ������ġ�߿� ��� �ֳ�?
// �׷���ī�� ���� ���� �˴ϴ�.
// => �׷���ī��� �� �������鷡
//    ũ��
struct FEngineVertex
{
public:
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
};


struct FEngineVertexColor
{
public:
	float4 POSITION;
	float4 COLOR;
};

