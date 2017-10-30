#pragma once
#include"stdafx.h"
#include"Body.h"
// add body to this class and physic things will be handled
class World
{
private:
	
	float _Gravity;  

	//list of all bodies. Using pointer like this may be better, I think. 
	//Note that we do not allocate new memory to this list, just hold the references to our objects
	std::vector<Body*> _Bodies;
	
	
public:
	//Constructor and destructor
	World();
	World(float gravity);
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
	std::vector<Body*> GetBodysList() const;
	
	//All set functions
	void SetGravity(float gravity);

	//Update world (update all the objects in this world)
	void Update(float dt);
	void AddBody(Body *body);
	void RemoveBody(Body* body);
	void RemoveBody(int index);

};
