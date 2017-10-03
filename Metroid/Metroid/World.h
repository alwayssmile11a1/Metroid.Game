// World.h : include anything in our game, such as gameobjects, camera, etc.

#pragma once
#include"stdafx.h"
#include"Object.h"

class World
{
public:
	Vector2 bounds; //the width and height of this game world
	DWORD dt; //delta time (time between two frames)
	std::vector<Object*> objects; //list of all objects. Using pointer like this may be better, I think. 
	
public:
	//Constructor and destructor
	World();
	World(int width, int height, DWORD dt);
	~World();

	//copy constructor - this is really important 
	//"The copy constructor is a constructor which creates an object by initializing it with an object of the same class, 
	//which has been created previously. The copy constructor is used to −
	//Initialize one object from another of the same type.
	//Copy an object to pass it as an argument to a function.
	//Copy an object to return it from a function.
	World(const World &world);


	//All get functions
	Vector2 getBounds();
	std::vector<Object*> getObjectsList() const;
	
	//All set functions
	void setBounds(Vector2 value);
	void setDeltaTime(DWORD dt);

	//Update world (update all the objects in this world)
	void update(DWORD dt, LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer);
	void addObject(Object *object);
	void removeObject(Object* object);
	void removeObject(int index);

};
