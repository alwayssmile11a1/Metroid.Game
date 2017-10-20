#pragma once

#include "stdafx.h"
#include "Texture.h"

// draw a portion of image 
class TextureRegion
{
private:
	Texture *_Texture;
	Vector2 _RectSize; //the width and height of the rectangle portion in the image
	Vector2 _RectPosition; //the top left position of portion we want to draw
	Vector2 _ScaleFactor; //scale

public:
	TextureRegion();
	//create a texture from file
	TextureRegion(Texture* texture, float rectLeft, float rectTop, float rectWidth, float rectHeight);
	TextureRegion(const TextureRegion &TextureRegion);
	~TextureRegion();

	TextureRegion& operator=(const TextureRegion &TextureRegion);

	//all get functions
	Vector2 GetRectSize() const;
	Vector2 GetRectPosition() const;
	Texture* GetTexture() const;
	Vector2 GetScale() const;

	//all set functions
	void SetRectPosition(float rectX, float rectY);
	void SetRectSize(float rectWidth, float rectHeight);
	void SetTexture(Texture *Texture);
	//Flip the texture. This function is done by multiplying the scale x or y with -1. 
	void Flip(bool flipX, bool flipY);
};

