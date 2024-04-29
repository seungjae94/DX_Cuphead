#pragma once

class UGameData
{
public:
	UGameData();
	~UGameData();

	UGameData(const UGameData& _Other) = delete;
	UGameData(UGameData&& _Other) noexcept = delete;
	UGameData& operator=(const UGameData& _Other) = delete;
	UGameData& operator=(UGameData&& _Other) noexcept = delete;

	static const int BossCount;
	static int ClearBossCount;

protected:


private:


};

