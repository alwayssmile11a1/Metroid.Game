// World.h : include anything in our game, such as gameobjects, camera, etc.

#pragma once
#include"stdafx.h"
#include"Object.h"
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
	int GetWidth();
	int GetHeight();
	std::list<Object> GetObjectsList();
	
	//All set functions
	void SetWidth(int Width);
	void SetHeight(int Height);
	void SetDeltaTime(DWORD dt);

	//Update world (update all the objects in this world)
	void Update(DWORD dt);
	void AddObject(Object* object);
	void RemoveObject(Object* object);
	void RemoveObject(int index);

};
