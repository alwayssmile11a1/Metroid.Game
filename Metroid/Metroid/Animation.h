//a class to easily manage the animation of an object 
#pragma once

#include "stdafx.h"
#include "Sprite.h"
#include "TextureRegion.h"
class Animation
{
private:
	Sprite* _CurrentSprite; //just hold reference, not initialize
	int _Index;				// Current sprite index
	int _Count;				// Number of sprites
	int _SpritePerRow;		// Number of sprites per row
	float _LeftOffset;		//The left offset in case the first sprite is not placed at (0,0)
	float _TopOffset;		//The top offset in case the first sprite is not placed at (0,0)
	DWORD _FrameInterval;	//the duration of a frame
	DWORD _StateTime;		//current time in one frame
	bool _Flipped;

	std::vector<Vector2> _RectPositions;
	std::vector<Vector2> _RectSizes;

public:
	Animation();
	Animation(Sprite *sprite,  int count, int spritePerRow, DWORD frameInterval);

	~Animation();
	Animation(const Animation &ani);
	Animation& operator=(const Animation &ani);
	

	Sprite* GetKeyAnimation();

	//Go to next animation frame
	//If isSameDirection = 0, the animation will be rendered as the opposite direction  
	//If isSameDirection = 1, the animation will be rendered as the same direction  
	//Note that the animation will be automatically returned to its original direction in the next animation frame before checking isSameDirection
	//Set isSameDirection = -1 to disable the effect
	void Next(DWORD deltaTime, int isSameDirection);
	void Reset();
	void SetOffset(float leftOffset, float topOffset);
	
	void SetDimensions(Vector2 rectPositions[], Vector2 rectSizes[]);

	//dimension is the position and the size of the rectangle on the image 
	void AddDimension(float rectLeft, float rectTop, float rectWidth, float Height);

};

