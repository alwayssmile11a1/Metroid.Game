#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(LPDIRECT3DDEVICE9 d3ddev, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow, DWORD frameInterval)
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
	_StateTime = 0;
	_FrameInterval = frameInterval;
}

Animation::Animation(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_FilePath = ani._FilePath;
	_CurrentSprite = ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
}
Animation& Animation::operator=(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_FilePath = ani._FilePath;
	_CurrentSprite = ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	return *this;
}


Animation::~Animation()
{

}

Texture Animation::GetKeyAnimation()
{
	return _CurrentSprite;
}

void Animation::Next(DWORD deltaTime)
{
	
	if (_StateTime >= _FrameInterval)
	{
		//calculate top left position (in the image)
		float rectX = (_Index % _SpritePerRow)*_Width + _LeftOffset;
		float rectY = (_Index / _SpritePerRow)*_Height + _TopOffset;

		//set rect position
		_CurrentSprite.SetRectPosition(rectX, rectY);

		//next index
		_Index = (_Index + 1) % _Count;

		//reset state time
		_StateTime = 0;
	}
	_StateTime += deltaTime;

}

void Animation::Reset()
{
	_Index = 0;
	_StateTime = 0;
}

void Animation::SetOffset(float leftOffset, float topOffset)
{
	_LeftOffset = leftOffset;
	_TopOffset = topOffset;
}

void Animation::Render(float x, float y)
{
	_CurrentSprite.Render(x, y);
}

void Animation::SetTranscolor(D3DCOLOR transColor)
{
	_CurrentSprite.SetTranscolor(transColor);
}