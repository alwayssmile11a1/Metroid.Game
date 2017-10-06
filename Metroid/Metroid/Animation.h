//a class to easily manage the animation of an object 
#pragma once

#include "stdafx.h"
#include "Sprite.h"
class Animation
{
public:
	Sprite _CurrentSprite; 
	int _Index;						// Current sprite index
	int _Width;								// Sprite width
	int _Height;							// Sprite height
	int _Count;								// Number of sprites
	int _SpritePerRow;						// Number of sprites per row
	LPCWSTR _FilePath;
public:
	Animation();
	Animation(LPDIRECT3DDEVICE9 d3ddev, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	~Animation();
	Animation(const Animation &ani);
	Animation& operator=(const Animation &ani);

	void Next();
	void Reset();

	// Render current sprite at location (X,Y) at the target surface
	void Render(int X, int Y);
	

};

