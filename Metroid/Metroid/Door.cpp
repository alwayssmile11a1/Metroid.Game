#include "Door.h"

Door::Door()
{

}


Door::~Door()
{

}

void Door::Create(World *world,Texture* doorTexture, int x, int y)
{
	

	this->world = world;
	
	TexturePacker p = TexturePacker(doorTexture, "Resources/door.xml");

	doorAnimation.AddRegion(p.GetRegion("door").at(0));


	right.SetRegion(*doorAnimation.GetKeyAnimation());
	right.SetSize(20, 95);
	right.SetPosition(x + 40, y - 3);
	
	//setup bodyRight
	BodyDef bodyDefRight;
	bodyDefRight.bodyType = Body::BodyType::Static;
	bodyDefRight.position.Set(x+40, y-3);
	bodyDefRight.size.Set(20, 95);
	
	//bodyDefRight.isSensor = true;
	bodyRight = world->CreateBody(bodyDefRight);
	bodyRight->categoryBits = DOOR_BIT;
	bodyRight->maskBits = BULLET_BIT;
	bodyRight->SetID("right");
	bodyRight->PutExtra(this);


	left.SetRegion(*doorAnimation.GetKeyAnimation());
	left.SetSize(20, 95);
	left.SetPosition(x - 40, y - 3);
	left.Flip(true, false);
	//setup bodyLeft
	BodyDef bodyDefLeft;
	bodyDefLeft.bodyType = Body::BodyType::Static;
	bodyDefLeft.position.Set(x - 40, y - 3);
	bodyDefLeft.size.Set(20, 95);
	
	//bodyDefLeft.isSensor = true;
	bodyLeft = world->CreateBody(bodyDefLeft);
	bodyLeft->categoryBits = DOOR_BIT;
	bodyLeft->maskBits = BULLET_BIT;
	bodyLeft->SetID("left");
	bodyLeft->PutExtra(this);


	isLOpen = false;
	isROpen = false;


	pauseTime = 0;

	this->OpenNClose=Sound::LoadSound("Resources/SoundEffect/OpenCloseDoor.wav");
}

void Door::Render(SpriteBatch *batch)
{
	if(this->isLOpen==false)
		batch->Draw(this->left);
	if(this->isROpen==false)
		batch->Draw(this->right);
	if (this->isLOpen == true || this->isROpen == true)
	{

		{
			pauseTime++;
		}
		if (pauseTime > 50)
		{
			Sound::Play(this->OpenNClose);
			this->isLOpen = false;
			this->isROpen = false;
			pauseTime = 0;
		}
	}
}

void Door::Update(float dt)
{
	
}
void Door::LOnhitBullet()
{
	this->isLOpen = true;
	Sound::Play(this->OpenNClose);

}

void Door::ROnhitBullet()
{
	this->isROpen = true;
	Sound::Play(this->OpenNClose);
}