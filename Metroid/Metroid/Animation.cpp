#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(LPDIRECT3DDEVICE9 d3ddev, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	_Width = Width;
	_Height = Height;
	_Count = Count;
	_SpritePerRow = SpritePerRow;
	_Index = 0;
	_FilePath = FilePath;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = Texture(d3ddev, FilePath, Width, Height, 0, 0);

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

Texture Animation::GetKeyAnimation()
{
	return _CurrentSprite;
}

void Animation::Next()
{
	//calculate top left position (in the image)
	float rectX = (_Index % _SpritePerRow)*_Width + _LeftOffset;
	float rectY = (_Index / _SpritePerRow)*_Height + _TopOffset;

	//set rect position
	_CurrentSprite.SetRectPosition(rectX, rectY);

	//next index
	_Index = (_Index + 1) % _Count;
}

void Animation::Reset()
{
	_Index = 0;
}

void Animation::SetOffset(float leftOffset, float topOffset)
{
	_LeftOffset = leftOffset;
	_TopOffset = topOffset;
}