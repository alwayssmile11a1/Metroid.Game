//this class really needs to improve later
#pragma once

#include "stdafx.h"

//draw an image at specified position or draw a portion of image 
class Texture
{
public:
	LPDIRECT3DTEXTURE9 _Image; //store the image that was loaded from file
	LPD3DXSPRITE _TextureHandler; //handle to a Texture 

	LPWSTR _FilePath;
	LPDIRECT3DDEVICE9 D3ddev;

	D3DCOLOR _Transcolor; //what color is needed to be transparent?
	Vector2 _Bounds; //the width and height of this sprite
	Vector2 _RectPosition; //the top left position of portion we want to draw

public:
	Texture();
	Texture(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath);
	Texture(LPDIRECT3DDEVICE9 d3ddev, LPWSTR filePath, float width, float height, float rectX, float rectY);
	Texture(const Texture &texture);
	~Texture();

	Texture& operator=(const Texture &texture);

	//all get functions
	Vector2 GetBounds();

	//all set functions
	void SetBounds(float width, float height);
	void SetTranscolor(D3DCOLOR transcolor);
	void SetRectPosition(float rectX, float rectY);

	// Render current sprite 
	void Render(float x, float y);

};

