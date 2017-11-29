#include"Object.h"
#include"World.h"

#define LIVETIME 0.1f
#define BULLETSPEED 5.0f


class Bullet: public Object
{
private:
	float liveTime;
	float bulletSpeed;

	Body mainBody;
	float stateTime;
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

	float GetBulletSpeed();

};

