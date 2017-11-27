#ifndef WORLDCONTACTLISTENER_H
#define WORLDCONTACTLISTENER_H

#include "Body.h"
class WorldContactListener: public GameObject
{
public:
	WorldContactListener();
	~WorldContactListener();

	//Call everytime two object collide with each other. 
	//Occur at the same moment of update world function
	//Note that if it's possible, don't try to perform any of the physic things here because it may lead to wrong physic results later. 
	void virtual OnContact(Body *bodyA, Body *bodyB) = 0;

};

#endif