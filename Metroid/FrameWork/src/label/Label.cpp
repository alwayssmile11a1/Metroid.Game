#include "Label.h"



Label::Label()
{
	_Font = NULL;
}


Label::~Label()
{
}


Label::Label(const std::string &text, Font* font, float x, float y, float width, float height)
{
	_Font = font;
	_Position.Set(x, y);
	_Size.Set(width, height);

	std::wstring stemp = StringToWstring(text);
	_Text = stemp.c_str();
}

void Label::Draw(Camera *cam)
{
	if (_Font == NULL || cam == NULL) return;

	D3DXVECTOR3 postion;
	postion.x = _Position.x;
	postion.y = _Position.y;
	postion.z = 0;

	//get actual position
	D3DXMATRIX _CameraMatrix;
	D3DXVECTOR4 _ActualPosition; //the actual position of the sprite will be drawn
								 //get the actual postion
	D3DXMatrixIdentity(&_CameraMatrix);
	_CameraMatrix._22 = -1;
	_CameraMatrix._41 = -(cam->GetPosition().x - screenWidth / 2.0);
	_CameraMatrix._42 = +cam->GetPosition().y + screenHeight / 2.0;

	D3DXVec3Transform(&_ActualPosition, &postion, &_CameraMatrix);
	postion.x = _ActualPosition.x;
	postion.y = _ActualPosition.y;
	postion.z = 0;

	RECT rect = { postion.x,postion.y,_Size.x,_Size.y };

	_Font->_pFont->DrawText(NULL, _Text, -1, &rect, DT_TOP | DT_LEFT,
		D3DCOLOR_XRGB(255, 255, 0));

}

void Label::SetText(std::string &text)
{
	std::wstring stemp = StringToWstring(text);
	_Text = stemp.c_str();
}