// Object.h: parent class of any game object 
#pragma once
#include"stdafx.h"
class Object
{
private:
	Vector2 bounds; //the width and height of this object
	Vector2 velocity; //the vx and vy of this object

public:
	//constructor and destructor
	Object();
	Object(int width, int height);
	~Object();

	//All get functions
	Vector2 getBounds();
	Vector2 getVelocity();

	//All set functions
	void setBounds(Vector2 value);
	void setVelocity(Vector2 value);


	//Update object
	void update(DWORD dt);
};

