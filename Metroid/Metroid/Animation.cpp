#include "Animation.h"

Animation::Animation()
{
	_Count = 0;
	_Index = 0;
	_StateTime = 0;
	_FrameInterval = 0;
	_Regions.clear();

}

Animation::Animation(const std::vector<TextureRegion> &regions, float frameInterval)
{
	_Count = regions.size();

	for (int i = 0; i < _Count; i++)
	{
		TextureRegion* textureRegion = new TextureRegion();
		*textureRegion = regions[i];
		_Regions.push_back(textureRegion);
	}

	_Index = 0;
	_StateTime = 0;
	_FrameInterval = frameInterval;
}

Animation::Animation(const Animation &ani)
{
	for (int i = 0; i < _Count; i++)
	{
		TextureRegion* textureRegion = new TextureRegion();
		*textureRegion = *ani._Regions[i];
		_Regions.push_back(textureRegion);
	}

	_Count = ani._Count;
	_Index = ani._Index;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;

}
Animation& Animation::operator=(const Animation &ani)
{
	for (int i = 0; i < _Count; i++)
	{
		TextureRegion* textureRegion = new TextureRegion();
		*textureRegion = *ani._Regions[i];
		_Regions.push_back(textureRegion);
	}

	_Count = ani._Count;
	_Index = ani._Index;
	_StateTime = ani._StateTime;
	_FrameInterval = ani._FrameInterval;
	return *this;
}


Animation::~Animation()
{
	for (std::vector<TextureRegion*>::iterator obj = _Regions.begin(); obj != _Regions.end(); ++obj)
	{
		delete *obj;
	}
}

TextureRegion* Animation::GetKeyAnimation()
{
	return _Regions[_Index];
}

TextureRegion* Animation::Next(float deltaTime, int isSameDirection)
{
	if (_Regions.size() == 0) return NULL;


	//if true, next animation
	if (_StateTime >= _FrameInterval)
	{
		
		//next index
		_Index = (_Index + 1) % _Count;

		//reset state time
		_StateTime = 0;
	}
	_StateTime += deltaTime;
	
	TextureRegion *currentRegion = _Regions[_Index];

	if (isSameDirection != -1)
	{
		//return to origin direction
		if (currentRegion->GetScale().X < 0) currentRegion->Flip(true, false);

		if (isSameDirection == 0)
		{
			currentRegion->Flip(true, false);
		}
	}

	return  currentRegion;
}

void Animation::Reset()
{
	_Index = 0;
	_StateTime = 0;

}

void Animation::SetFrameInterval(float frameInterval)
{
	_FrameInterval = frameInterval;
}

void Animation::AddRegion(const TextureRegion &region)
{
	TextureRegion* textureRegion = new TextureRegion();
	*textureRegion = region;
	_Regions.push_back(textureRegion);
	_Count++;

}

void Animation::AddRegion(const std::vector<TextureRegion> &regions)
{
	_Count += regions.size();

	for (int i = 0; i < _Count; i++)
	{
		TextureRegion* textureRegion = new TextureRegion();
		*textureRegion = regions[i];
		_Regions.push_back(textureRegion);
	}
}