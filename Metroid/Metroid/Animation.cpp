#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(LPDIRECT3DDEVICE9 d3ddev, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	//D3DXIMAGE_INFO info;

	//HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);

	//_Image = NULL;
	//HRESULT res = D3DXCreateSprite(d3ddev, &_SpriteHandler);
	//if (res != D3D_OK) return;

	//_SpriteHandler->GetDevice(&d3ddev);

	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;
	_FilePath = FilePath;
	_CurrentSprite = Sprite(d3ddev, FilePath, 0, 0);

	//if (result != D3D_OK)
	//{
	//	return;
	//}


	///*result = D3DXGetImageInfoFromFile((LPWSTR)FilePath, &info);*/


	///*SpriteHandler->GetDevice(&d3ddev);*/

	//result = D3DXCreateTextureFromFileEx(
	//	d3ddev,
	//	FilePath,
	//	info.Width,
	//	info.Height,
	//	1,
	//	D3DPOOL_DEFAULT,
	//	D3DFMT_UNKNOWN,
	//	D3DPOOL_DEFAULT,
	//	D3DX_DEFAULT,
	//	D3DX_DEFAULT,
	//	D3DCOLOR_XRGB(0, 0, 0),
	//	&info,
	//	NULL,
	//	&_Image);

	//if (result != D3D_OK)
	//{
	//	return;
	//}
}

Animation::Animation(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = 0;
	_FilePath = ani._FilePath;
	_CurrentSprite = ani._CurrentSprite;
}
Animation& Animation::operator=(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = 0;
	_FilePath = ani._FilePath;
	_CurrentSprite = ani._CurrentSprite;
	return *this;
}


Animation::~Animation()
{

}


void Animation::Render(int X, int Y)
{
	//_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	//RECT srect;

	//srect.left = (_Index % _SpritePerRow)*(_Width)+1;
	//srect.top = (_Index / _SpritePerRow)*(_Height)+1;
	//srect.right = srect.left + _Width;
	//srect.bottom = srect.top + _Height + 1;

	////srect.left = 0;
	////srect.top = 0;
	////srect.right = srect.left + _Width;
	////srect.bottom = srect.top + _Height + 1;

	//D3DXVECTOR3 position((float)X, (float)Y, 0);

	//_SpriteHandler->Draw(
	//	_Image,
	//	&srect,
	//	NULL,
	//	&position,
	//	D3DCOLOR_XRGB(255, 255, 255)
	//);

	//_SpriteHandler->End();
	//_CurrentSprite.Render(X, Y, 0,0);
}

void Animation::Next()
{
	_Index = (_Index + 1) % _Count;

}

void Animation::Reset()
{
	_Index = 0;
}
