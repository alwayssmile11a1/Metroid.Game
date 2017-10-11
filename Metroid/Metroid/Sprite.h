#pragma once

#include "stdafx.h"
#include "Texture.h"

//Texture + Texture Region
class Sprite 
{
private:
	Vector2 _Position; //the position of this sprite
	Vector2 _ScaleFactor; //scale
	Vector2 _RotationOrigin; //the position that will be used as origin for rotating
	float _Rotation;
	float _IsCenterOrigin; //
	Vector2 _RectSize; //the width and height of the rectangle portion in the image
	Vector2 _RectPosition; //the top left position of portion we want to draw

	Texture *_Texture; //we don't initialize this variable, just use this to hold the reference to a texture
public:
	Sprite();
	Sprite(Texture *texture);
	
	//draw a portion of image, stretch it to width and height
	Sprite(Texture *texture, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, float width, float height);
	Sprite(const Sprite &texture);
	~Sprite();

	Sprite& operator=(const Sprite &texture);

	//all get functions
	Vector2 GetRotationOrigin() const;
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;
	Texture* GetTexture() const;
	Vector2 GetRectSize() const;
	Vector2 GetRectPosition() const;

	//all set functions
	void SetRotationOrigin(float centerX, float centerY);
	void SetRotation(float rotation);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);
	void SetTexture(Texture &texture);
	void SetRectPosition(float rectX, float rectY);
	void SetRectSize(float rectWidth, float rectHeight);

	//if true, set the origin of this sprite to be always in the center of this texture
	void SetCenterRotationOrigin(bool center);
	bool IsCenterOrigin() const;

	//Flip the texture. This function is done by multiplying the scale x or y with -1. 
	void Flip(bool flipX, bool flipY);

	//this also affects the texture being reference to
	void ResetToWhole();


};

