// Object.h: parent class of any game object 
#pragma once
#include"stdafx.h"

class Object
{
private:
	int width; //the width of the object
	int height; //the height of the object
	int vx;
	int vy;

public:
	//constructor and destructor
	Object();
	Object(int width, int height);
	~Object();


	//Update object
	void Update(DWORD dt);
};

