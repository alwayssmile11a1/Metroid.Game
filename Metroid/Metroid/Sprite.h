#pragma once

#include "stdafx.h"
#include "Texture.h"
#include "TextureRegion.h"
//Texture + Texture Region
class Sprite 
{
private:
	Vector2 _Position; //the position of this sprite
	Vector2 _ScaleFactor; //scale
	Vector2 _Size;
	Vector2 _Velocity; //the vx and vy of this object
	Vector2 _Direction; //the direction that the sprite is heading towards
	Vector2 _RotationOrigin; //the position that will be used as origin for rotating
	float _Rotation;
	float _IsCenterOrigin; //
	Vector2 _RectSize; //the width and height of the rectangle portion in the image
	Vector2 _RectPosition; //the top left position of portion we want to draw

	Texture *_Texture; //we don't initialize this variable by default, just use this to hold the reference to a texture
						//if you do want to allocate a new memory for this texture, consider use _CreateNewTexture variable

	//bool _CreateNewTexture; //if true, allocate a new memory for the texture

public:
	Sprite();

	//if create new is true, allocate a new memory for the texture
	//but may affect the performance
	Sprite(Texture *texture/*, bool createNew*/);
	
	//draw a portion of image, stretch it to width and height
	Sprite(Texture *texture,/* bool createNew,*/ float x, float y, float rectLeft, float rectTop, float rectWidth, float rectHeight, Vector2 Velocity, Vector2 Direction);
	Sprite(const Sprite &sprite);
	~Sprite();

	Sprite& operator=(const Sprite &texture);

	//all get functions
	Vector2 GetRotationOrigin() const;
	Vector2 GetPosition() const;
	Vector2 GetSize() const;
	float GetRotation() const;
	Vector2 GetScale() const;
	Texture* GetTexture() const;
	Vector2 GetRectSize() const;
	Vector2 GetRectPosition() const;
	Vector2 GetVelocity() const;
	Vector2 GetDirection() const;

	//all set functions
	void SetRotationOrigin(float centerX, float centerY);
	void SetRotation(float rotation);
	void SetPosition(float x, float y);
	void SetSize(float width, float height);
	void SetTexture(Texture *texture);
	void SetRegion(TextureRegion *textureRegion);
	void SetRectPosition(float rectX, float rectY);
	void SetRectSize(float rectWidth, float rectHeight);
	void SetVelocity(Vector2 value);
	void SetDirection(Vector2 value);

	//if true, set the origin of this sprite to be always in the center of this texture
	void SetCenterRotationOrigin(bool center);
	bool IsCenterOrigin() const;

	//Flip the texture. This function is done by multiplying the scale x or y with -1. 
	void Flip(bool flipX, bool flipY);

	//this also affects the texture being reference to
	void ResetToWhole();


};

