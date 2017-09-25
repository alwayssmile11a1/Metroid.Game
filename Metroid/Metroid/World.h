// World.h : include anything in our game, such as gameobjects, camera, etc.

#pragma once
#include"stdafx.h"

class World
{
private:
	int width; //the width of the world
	int height; //the height of the world
	DWORD dt; //delta time (time between two frames)
	std::list<Object> objects; //list of all objects
	
public:
	//Constructor and destructor
	World();
	World(int width, int height, DWORD dt);
	~World();

	//All get functions
	void GetWidth();
	void GetHeight();
	void GetObjectsList();
	
	//All set functions
	void SetWidth();
	void SetHeight();
	void SetDeltaTime();

	//Update world (update all the objects in this world)
	void Update(DWORD dt);
	void AddObject(Object* object);
	void RemoveObject(Object* object);
	void RemoveObject(int index);



};
