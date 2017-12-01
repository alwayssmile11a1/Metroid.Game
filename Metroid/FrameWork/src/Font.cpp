#include "Font.h"

Font::Font()
{
	_pFont = NULL;
}
Font::~Font()
{

}

Font::Font(const std::string &fontName)
{
	//get path from string
	std::wstring stemp = StringToWstring(fontName);
	LPCWSTR font = stemp.c_str();

	HRESULT result = D3DXCreateFontW(d3ddevice, 24, 0, 1, FW_NORMAL, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, font, &_pFont);

	if (!SUCCEEDED(result))
	{
		//failed
	}



}


