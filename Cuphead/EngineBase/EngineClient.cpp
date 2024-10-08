#include "PreCompile.h"
#include "EngineClient.h"
#include "EngineDebug.h"

UEngineClient::UEngineClient() 
{
}

UEngineClient::~UEngineClient() 
{
}

void UEngineClient::ServerOpen(int _Port, int _BackLog)
{
	MsgBoxAssert("클라이언트로 구현되어있는 인스턴스가 서버로 다시 오픈하려고 했습니다. 불가능합니다.");
}

void UEngineClient::Connect(std::string _Ip, int _Port)
{
	Session.Create();
	Session.SetAdd(_Ip, _Port);
	Session.Connect();
}