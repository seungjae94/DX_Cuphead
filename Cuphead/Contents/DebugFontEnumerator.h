#pragma once

class UDebugFontEnumerator
{
public:
	UDebugFontEnumerator();
	~UDebugFontEnumerator();

	UDebugFontEnumerator(const UDebugFontEnumerator& _Other) = delete;
	UDebugFontEnumerator(UDebugFontEnumerator&& _Other) noexcept = delete;
	UDebugFontEnumerator& operator=(const UDebugFontEnumerator& _Other) = delete;
	UDebugFontEnumerator& operator=(UDebugFontEnumerator&& _Other) noexcept = delete;

	static std::list<std::string> GetAllFontList();

protected:


private:
	static int CALLBACK EnumFontFamExProc(
		ENUMLOGFONTEX* lpelfe,
		NEWTEXTMETRICEX* lpntme,
		DWORD FontType,
		LPARAM lParam
	);

	static std::list<std::string> FontNames;
};

