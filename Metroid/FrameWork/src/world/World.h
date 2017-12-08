#ifndef WORLD_H
#define WORLD_H

#include<vector>
#include "GameObject.h"
#include"..\drawable\SpriteBatch.h"
#include"Collision.h"
#include"WorldContactListener.h"
#include <algorithm>  
#include "BodyDef.h"
#include "..\collisionquadtree\QuadTree.h"

// add body to this class and physic things will be handled
class World: public GameObject
{
private:
	
	float _Gravity;  
	std::vector<Body*> _Bodies; 	//list of all bodies. Using pointer like this may be better, I think. 
									//Note that we do not allocate new memory to this list, just hold the references to our objects

	WorldContactListener* _Listener;  //listen to the collision
	
	QuadTree* _QuadTree;			//Quadtree of this world

	Camera* _Cam;

private:
	friend class Collision;

public:
	//Constructor and destructor
	World();
	World(float gravity);
	~World();

	//World(const World &world);
	//World& operator=(const World &world);
	void SetCamera(Camera *cam);

	//All get functions
	const std::vector<Body*>& GetBodysList() const;
	
	//All set functions
	void SetGravity(float gravity);

	void SetContactListener(WorldContactListener *listener);


	//Update world (update all the objects in this world)
	void Update(float dt);
	//void AddBody(Body *body);
	//void AddBody(const std::vector<Body*> &bodies);
	void DestroyBody(Body* body);

	Body* CreateBody(const BodyDef &bodyDef);

	//Render all bodies by squares
	void RenderBodiesDebug(SpriteBatch *batch);

	void Release();

};

#endif