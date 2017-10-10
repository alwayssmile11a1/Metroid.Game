#pragma once

#include "stdafx.h"
#include "DirectXDevice.h"
#include "Texture.h"

//let's extend Texture class 
class Sprite : public Texture
{
private:
	Vector2 _Position; //the position of this sprite

	Vector2 _ScaleFactor; //scale
	Vector2 _RotationOrigin; //the position that will be used as origin for rotating
	float _Rotation;

	float _IsCenterOrigin; //

public:
	Sprite();
	Sprite(LPWSTR filePath);
	
	//draw a portion of image, stretch it to width and height
	Sprite(LPWSTR filePath, float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, float width, float height);
	Sprite(const Sprite &texture);
	~Sprite();

	Sprite& operator=(const Sprite &texture);

	//all get functions
	Vector2 GetRotationOrigin() const;
	Vector2 GetPosition() const;
	float GetRotation() const;
	Vector2 GetScale() const;

	//all set functions
	void SetRotationOrigin(float centerX, float centerY);
	void SetRotation(float rotation);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);

	//if true, set the origin of this sprite to be always in the center of this texture
	void SetCenterRotationOrigin(bool center);
	bool IsCenterOrigin() const;

	//Flip the texture. This function is done by multiplying the scale x or y with -1. 
	void Flip(bool flipX, bool flipY);

	void ResetToWhole();
};

