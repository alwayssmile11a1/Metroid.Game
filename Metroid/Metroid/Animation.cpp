#include "Animation.h"

Animation::Animation()
{
	_Width = 0;
	_Height = 0;
	_Count = 0;
	_SpritePerRow = 0;
	_Index = 0;
	_FilePath = NULL;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = NULL;
	_StateTime = 0;
	_FrameInterval = 0;
	_Flipped = false;
}

Animation::Animation(LPWSTR filePath, int width, int height, int count, int spritePerRow, DWORD frameInterval)
{
	_Width = width;
	_Height = height;
	_Count = count;
	_SpritePerRow = spritePerRow;
	_Index = 0;
	_FilePath = filePath;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = new Texture(filePath, 0, 0, width, height);
	_StateTime = 0;
	_FrameInterval = frameInterval;
	_Flipped = false;
}

Animation::Animation(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_FilePath = ani._FilePath;
	_CurrentSprite = new Texture();
	*_CurrentSprite = *ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
}
Animation& Animation::operator=(const Animation &ani)
{
	_Width = ani._Width;
	_Height = ani._Height;
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_FilePath = ani._FilePath;
	_CurrentSprite = new Texture();
	*_CurrentSprite = *ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
	return *this;
}


Animation::~Animation()
{
	if (_CurrentSprite != NULL)
	{
		delete _CurrentSprite;
		_CurrentSprite = NULL;
	}
}

Texture* Animation::GetKeyAnimation()
{
	return _CurrentSprite;
}

void Animation::Next(DWORD deltaTime, int isSameDirection)
{
	//if (isSameDirection != -1)
	//{
	//	//return to origin direction
	//	if (_Flipped) _CurrentSprite.Flip(true, false);

	//	if (isSameDirection == 0)
	//	{
	//		_CurrentSprite.Flip(true, false);
	//	}

	//	_Flipped = !isSameDirection;
	//}

	//if true, next animation
	if (_StateTime >= _FrameInterval)
	{
		//calculate top left position (in the image)
		float rectX = (_Index % _SpritePerRow)*_Width + _LeftOffset;
		float rectY = (_Index / _SpritePerRow)*_Height + _TopOffset;

		//set rect position
		_CurrentSprite->SetRectPosition(rectX, rectY);

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

void Animation::SetTranscolor(D3DCOLOR transColor)
{
	_CurrentSprite->SetTranscolor(transColor);
}