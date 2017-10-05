//draw an image at specified position or draw a portion of image 
#pragma once

#include "stdafx.h"

class Sprite
{
public:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file
	LPD3DXSPRITE _SpriteHandler; //handle to a sprite 

	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _Position; //where we draw this sprite in our scene 
	Vector2 _Bounds; //the width and height of this sprite
	Vector2 _RectPosition; //the top left position of portion we want to draw

public:
	Sprite();
	Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR filePath, float x, float y);
	Sprite(LPDIRECT3DDEVICE9 d3ddev, LPCWSTR filePath, float x, float y, float width, float height, float rectX, float rectY);
	~Sprite();

	//all get functions
	Vector2 GetPosition();
	Vector2 GetBounds();

	//all set functions
	void SetBounds(float width, float height);
	void SetPosition(int x, int y);
	void SetTranscolor(D3DCOLOR transcolor);
	void SetRectPosition(float rectX, float rectY);

	// Render current sprite 
	void Render();

};

