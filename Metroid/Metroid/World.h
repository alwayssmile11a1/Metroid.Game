#pragma once
#include"stdafx.h"
#include"Object.h"
// check 
class World
{
private:
	Vector2 _Bounds; //the width and height of this game world
	DWORD _DeltaTime; //delta time (time between two frames)
	
	//list of all objects. Using pointer like this may be better, I think. 
	//Note that we do not allocate new memory to this list, just hold the references to our objects
	std::vector<Object*> _Objects;
	
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
	World& operator=(const World &world);


	//All get functions
	Vector2 GetBounds();
	std::vector<Object*> GetObjectsList() const;
	
	//All set functions
	void SetBounds(const Vector2 &value);
	void SetDeltaTime(DWORD dt);

	//Update world (update all the objects in this world)
	void Update(DWORD dt);
	void AddObject(Object *object);
	void RemoveObject(Object* object);
	void RemoveObject(int index);

};
