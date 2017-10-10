#include "Animation.h"

Animation::Animation()
{
	_Count = 0;
	_SpritePerRow = 0;
	_Index = 0;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = NULL;
	_StateTime = 0;
	_FrameInterval = 0;
	_Flipped = false;
}

Animation::Animation(Sprite *sprite, int count, int spritePerRow, DWORD frameInterval)
{
	_Count = count;
	_SpritePerRow = spritePerRow;
	_Index = 0;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = sprite;
	_StateTime = 0;
	_FrameInterval = frameInterval;
	_Flipped = false;
}

Animation::Animation(Sprite &sprite, float rectWidth, float rectHeight, int count, int spritePerRow, DWORD frameInterval)
{

	_Count = count;
	_SpritePerRow = spritePerRow;
	_Index = 0;
	_LeftOffset = 0;
	_TopOffset = 0;
	_CurrentSprite = &sprite;
	_StateTime = 0;
	_FrameInterval = frameInterval;
	_CurrentSprite->SetRectSize(rectWidth, rectHeight);
	_Flipped = false;
}

Animation::Animation(const Animation &ani)
{
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_CurrentSprite = ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
}
Animation& Animation::operator=(const Animation &ani)
{
	_Count = ani._Count;
	_SpritePerRow = ani._SpritePerRow;
	_Index = ani._Index;
	_CurrentSprite = ani._CurrentSprite;
	_LeftOffset = ani._LeftOffset;
	_TopOffset = ani._TopOffset;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
	return *this;
}


Animation::~Animation()
{
	
}

Sprite* Animation::GetKeyAnimation()
{
	return _CurrentSprite;
}

void Animation::Next(DWORD deltaTime, int isSameDirection)
{
	if (_CurrentSprite == NULL) return;

	if (isSameDirection != -1)
	{
		//return to origin direction
		if (_Flipped) _CurrentSprite->Flip(true, false);

		if (isSameDirection == 0)
		{
			_CurrentSprite->Flip(true, false);
		}

		_Flipped = !isSameDirection;
	}

	//if true, next animation
	if (_StateTime >= _FrameInterval)
	{
		//calculate top left position (in the image)
		float rectX = (_Index % _SpritePerRow)*_CurrentSprite->GetRectSize().X + _LeftOffset;
		float rectY = (_Index / _SpritePerRow)*_CurrentSprite->GetRectSize().Y + _TopOffset;

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
