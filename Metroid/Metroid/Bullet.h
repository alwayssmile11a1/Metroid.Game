#include"Object.h"
#include"World.h"

class Bullet: public Object
{
private:
	Body mainBody;
	float liveTime;
	World *world;

	bool isDestroyed;

public:
	Bullet();
	~Bullet();

	Bullet(World *world, Texture* texture);
	
	void Render(SpriteBatch &batch);
	void Update(float dt);
	//void Release();

	bool IsDestroyed();

};

