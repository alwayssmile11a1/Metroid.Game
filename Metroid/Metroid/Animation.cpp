#include "Animation.h"

Animation::Animation()
{
	_Count = 0;
	_Index = 0;
	_StateTime = 0;
	_FrameInterval = 0;
	_Flipped = false;
	_CurrentRegion = NULL;
	_RectPositions.clear();
	_RectSizes.clear();
}

Animation::Animation(Texture *texture, float frameInterval)
{
	_CurrentRegion = new TextureRegion(texture,0,0,0,0);
	_Count = 0;
	_Index = 0;
	_StateTime = 0;
	_FrameInterval = frameInterval;
	_Flipped = false;
	_RectPositions.clear();
	_RectSizes.clear();
}

//Animation::Animation(TextureRegion textureRegions[], float frameInterval)
//{
//	_TextureRegions.insert(_TextureRegions.end(), &textureRegions[0], &textureRegions[0] + (int)(sizeof(textureRegions) / sizeof(textureRegions[0])));
//	_Count = (int)(sizeof(textureRegions) / sizeof(textureRegions[0]));
//	_Index = 0;
//	_StateTime = 0;
//	_FrameInterval = frameInterval;
//	_Flipped = false;
//	_CurrentRegion = &_TextureRegions[0];
//}

Animation::Animation(const Animation &ani)
{
	_CurrentRegion = new TextureRegion();
	*_CurrentRegion = *ani._CurrentRegion;
	_Count = ani._Count;
	_Index = ani._Index;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
	_RectPositions = ani._RectPositions;
	_RectSizes = ani._RectSizes;
}
Animation& Animation::operator=(const Animation &ani)
{
	_CurrentRegion = new TextureRegion();
	*_CurrentRegion = *ani._CurrentRegion;
	_Count = ani._Count;
	_Index = ani._Index;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	_Flipped = ani._Flipped;
	_RectPositions = ani._RectPositions;
	_RectSizes = ani._RectSizes;
	return *this;
}


Animation::~Animation()
{
	delete _CurrentRegion;
}

TextureRegion* Animation::GetKeyAnimation()
{
	return _CurrentRegion;
}

TextureRegion* Animation::Next(float deltaTime, int isSameDirection)
{
	if (_CurrentRegion == NULL) return NULL;

	if (isSameDirection != -1)
	{
		//return to origin direction
		if (_Flipped) _CurrentRegion->Flip(true, false);

		if (isSameDirection == 0)
		{
			_CurrentRegion->Flip(true, false);
		}

		_Flipped = !isSameDirection;
	}

	//if true, next animation
	if (_StateTime >= _FrameInterval)
	{
	
		//get top left
		float rectLeft = _RectPositions[_Index].X;
		float rectTop = _RectPositions[_Index].Y;

		//get rectSize
		float rectWidth = _RectSizes[_Index].X;
		float rectHeight = _RectSizes[_Index].Y;

		_CurrentRegion->SetRectPosition(rectLeft, rectTop);
		_CurrentRegion->SetRectSize(rectWidth, rectHeight);

		//next index
		_Index = (_Index + 1) % _Count;

		//reset state time
		_StateTime = 0;
	}
	_StateTime += deltaTime;

	return _CurrentRegion;
}

void Animation::Reset()
{
	_Index = 0;
	_StateTime = 0;
	_CurrentRegion->SetRectPosition(_RectPositions[0].X, _RectPositions[0].Y);
	_CurrentRegion->SetRectSize(_RectSizes[0].X, _RectSizes[0].Y);
}

void Animation::SetFrameInterval(float frameInterval)
{
	_FrameInterval = frameInterval;
}

void Animation::SetRegions(Vector2 rectPositions[], Vector2 rectSizes[])
{
	_RectPositions.clear();
	_RectSizes.clear();
	_RectPositions.insert(_RectPositions.end(),&rectPositions[0], &rectPositions[0]+ (int)(sizeof(rectPositions) / sizeof(rectPositions[0])));
	_RectSizes.insert(_RectSizes.end(), &rectSizes[0], &rectSizes[0] + (int)(sizeof(rectSizes) / sizeof(rectSizes[0])));
	_Count = (int)(sizeof(rectPositions) / sizeof(rectPositions[0]));
}

void Animation::AddRegion(float rectLeft, float rectTop, float rectWidth, float rectHeight)
{
	_Count++;
	Vector2 rectPosition(rectLeft,rectTop);
	Vector2 rectSize(rectWidth,rectHeight);
	_RectPositions.push_back(rectPosition);
	_RectSizes.push_back(rectSize);

}