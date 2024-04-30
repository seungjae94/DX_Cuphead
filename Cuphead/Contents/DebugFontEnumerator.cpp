#include "PreCompile.h"
#include "DebugFontEnumerator.h"

std::list<std::string> UDebugFontEnumerator::FontNames;

UDebugFontEnumerator::UDebugFontEnumerator()
{
}

UDebugFontEnumerator::~UDebugFontEnumerator()
{
}

std::list<std::string> UDebugFontEnumerator::GetAllFontList()
{
	LOGFONT lf;
	lf.lfFaceName[0] = '\0';
	lf.lfCharSet = DEFAULT_CHARSET;
	HDC hDC = ::GetDC(GEngine->EngineWindow.GetHWND());
	EnumFontFamiliesEx(hDC, &lf, (FONTENUMPROC)&UDebugFontEnumerator::EnumFontFamExProc, 0, 0);
	ReleaseDC(GEngine->EngineWindow.GetHWND(), hDC);

	return FontNames;
}

int UDebugFontEnumerator::EnumFontFamExProc(ENUMLOGFONTEX* lpelfe, NEWTEXTMETRICEX* lpntme, DWORD FontType, LPARAM lParam)
{
	char str[(sizeof lpelfe->elfFullName) + 1];
	memcpy(str, lpelfe->elfFullName, sizeof lpelfe->elfFullName);
	str[sizeof lpelfe->elfFullName] = 0; // Null termination.

	std::string Result = str;
	FontNames.push_back(Result);

	return 1;
}
