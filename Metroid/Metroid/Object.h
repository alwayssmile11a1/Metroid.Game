// Object.h: parent class of any game object
#pragma once
#include"stdafx.h"
#include "Texture.h"
class Object
{
public:
	Vector2 _Bounds; //the width and height of this object
	Vector2 _Velocity; //the vx and vy of this object
	Vector2 _Position; //the x, y coordinate of this object

	Texture _Texture; //the sprite of this object - do we put sprite in object class? - this might be changed later 
public:

	//constructor and destructor
	Object();
	Object(float x, float y, float width, float height);
	Object(const Object &object);
	~Object();

	Object& operator=(const Object &object);

	//All get functions
	Vector2 GetBounds();
	Vector2 GetVelocity();
	Vector2 GetPosition();
	Texture GetTexture();

	//All set functions
	void SetBounds(Vector2 value);
	void SetVelocity(Vector2 value);
	void SetPosition(Vector2 value);
	void SetTexture(Texture texture);

	//Update object
	void Update(DWORD dt);
};

