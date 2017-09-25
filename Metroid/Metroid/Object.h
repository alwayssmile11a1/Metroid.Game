// Object.h: parent class of any game object 
#pragma once

class Object
{
private:
	int width; //the width of the world
	int height; //the height of the world
	DWORD dt; //delta time (time between two frames)


public:
	Object();
	~Object();
};

