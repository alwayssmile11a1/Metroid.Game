#pragma once
#include"stdafx.h"
#include"Body.h"
#include"SpriteBatch.h"
#include"Collision.h"
// add body to this class and physic things will be handled
class World
{
private:
	
	float _Gravity;  
	std::vector<Body*> _Bodies; 	//list of all bodies. Using pointer like this may be better, I think. 
									//Note that we do not allocate new memory to this list, just hold the references to our objects
	
	

	Texture _DebugSquareTexture;    //for debug purposes
	
	
public:
	//Constructor and destructor
	World();
	World(float gravity);
	~World();

	World(const World &world);
	World& operator=(const World &world);


	//All get functions
	const std::vector<Body*>& GetBodysList() const;
	
	//All set functions
	void SetGravity(float gravity);

	//Update world (update all the objects in this world)
	void Update(float dt);
	void AddBody(Body *body);
	void AddBody(const std::vector<Body*> &bodies);
	void RemoveBody(Body* body);
	void RemoveBody(int index);

	//Render all bodies by squares
	void RenderBodiesDebug(SpriteBatch &batch);

};
