//a class to easily manage the animation of an object 
#pragma once

#include "stdafx.h"
#include "Sprite.h"
#include "TextureRegion.h"
class Animation
{
private:
	TextureRegion *_CurrentRegion;
	//std::vector<TextureRegion> _TextureRegions; //just hold reference, not initialize
	int _Index;				// Current sprite index
	int _Count;				// Number of sprites
	float _FrameInterval;	//the duration of a frame
	float _StateTime;		//current time in one frame
	bool _Flipped;

	std::vector<Vector2> _RectPositions;
	std::vector<Vector2> _RectSizes;

public:
	Animation();
	//consider use AddRegion or SetRegions if using this constructor
	Animation(Texture *texture, float frameInterval);

	//Animation(TextureRegion textureRegions[], float frameInterval);

	~Animation();
	Animation(const Animation &ani);
	Animation& operator=(const Animation &ani);
	

	TextureRegion* GetKeyAnimation();

	//Go to next animation frame
	//If isSameDirection = 0, the animation will be rendered as the opposite direction  
	//If isSameDirection = 1, the animation will be rendered as the same direction  
	//Note that the animation will be automatically returned to its original direction in the next animation frame before checking isSameDirection
	//Set isSameDirection = -1 to disable the effect
	TextureRegion* Next(float deltaTime, int isSameDirection);
	void Reset();
	void SetFrameInterval(float frameInterval);
	void SetRegions(Vector2 rectPositions[], Vector2 rectSizes[]);

	//dimension is the position and the size of the rectangle on the image 
	void AddRegion(float rectLeft, float rectTop, float rectWidth, float Height);

};

