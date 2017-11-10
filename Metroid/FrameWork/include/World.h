#ifndef WORLD_H
#define WORLD_H

#include "..\src\others\stdafx.h"
#include"Body.h"
#include"SpriteBatch.h"
#include"Collision.h"
#include"WorldContactListener.h"


// add body to this class and physic things will be handled
class World: public GameObject
{
private:
	
	float _Gravity;  
	std::vector<Body*> _Bodies; 	//list of all bodies. Using pointer like this may be better, I think. 
									//Note that we do not allocate new memory to this list, just hold the references to our objects

	WorldContactListener* _Listener;  //listen to the collision
	


public:
	//Constructor and destructor
	World();
	World(float gravity);
	~World();

	//World(const World &world);
	//World& operator=(const World &world);


	//All get functions
	const std::vector<Body*>& GetBodysList() const;
	
	//All set functions
	void SetGravity(float gravity);

	void SetContactListener(WorldContactListener *listener);


	//Update world (update all the objects in this world)
	void Update(float dt);
	void AddBody(Body *body);
	void AddBody(const std::vector<Body*> &bodies);
	void RemoveBody(Body* body);
	void RemoveBody(int index);

	//Render all bodies by squares
	void RenderBodiesDebug(SpriteBatch &batch);

};

#endif