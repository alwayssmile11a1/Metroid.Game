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
	bodyDefRight.bodyType = Body::BodyType::Kinematic;
	bodyDefRight.position.Set(x+40, y-3);
	bodyDefRight.size.Set(20, 95);
	//bodyDefRight.isSensor = true;
	bodyRight = world->CreateBody(bodyDefRight);
	bodyRight->categoryBits = DOOR_BIT;
	bodyRight->maskBits = BULLET_BIT|PLAYER_BIT;
	bodyRight->SetID("right");
	bodyRight->PutExtra(this);



	left.SetRegion(*doorAnimation.GetKeyAnimation());
	left.SetSize(20, 95);
	left.SetPosition(x - 40, y - 3);
	left.Flip(true, false);
	//setup bodyLeft
	BodyDef bodyDefLeft;
	bodyDefLeft.bodyType = Body::BodyType::Kinematic;
	bodyDefLeft.position.Set(x - 40, y - 3);
	bodyDefLeft.size.Set(20, 95);
	//bodyDefLeft.isSensor = true;
	bodyLeft = world->CreateBody(bodyDefLeft);
	bodyLeft->categoryBits = DOOR_BIT;
	bodyLeft->maskBits = BULLET_BIT|PLAYER_BIT;
	bodyLeft->SetID("left");
	bodyLeft->PutExtra(this);



	//setup bodyMid
	BodyDef bodyDefMid;
	bodyDefMid.bodyType = Body::BodyType::Static;
	bodyDefMid.position.Set(x, y);
	bodyDefMid.size.Set(2*32, 3*32);
	//bodyDefMid.isSensor = true;
	bodyMid = world->CreateBody(bodyDefMid);
	bodyMid->categoryBits = DOOR_BIT;
	bodyMid->maskBits = BULLET_BIT | PLAYER_BIT | ZOOMER_BIT;
	bodyMid->SetID("mid");
	bodyMid->PutExtra(this);

	
	isLOpen = false;
	isROpen = false;


	pauseTimeL = 0;
	pauseTimeR = 0;

	this->OpenNClose=Sound::LoadSound("Resources/SoundEffect/OpenCloseDoor.wav");
}

void Door::Render(SpriteBatch *batch)
{
	if(this->isLOpen==false)
		batch->Draw(this->left);
	if(this->isROpen==false)
		batch->Draw(this->right);
	if (this->isLOpen == true)
	{
		this->bodyLeft->categoryBits = 0;
		pauseTimeL++;
		if (pauseTimeL > 50)
		{
			Sound::Play(this->OpenNClose);
			this->isLOpen = false;
			//this->isROpen = false;
			pauseTimeL = 0;
			this->bodyLeft->categoryBits = DOOR_BIT;
			//this->bodyMid->categoryBits = DOOR_BIT;
			this->canPassLeft=false;
		}
	}
	if (this->isROpen == true)
	{
		this->bodyRight->categoryBits = 0;
		pauseTimeR++;
		if (pauseTimeR > 50)
		{
			Sound::Play(this->OpenNClose);
			//this->isLOpen = false;
			this->isROpen = false;
			pauseTimeR = 0;
			this->bodyRight->categoryBits = DOOR_BIT;
			//this->bodyMid->categoryBits = DOOR_BIT;
			this->canPassRight = false;
		}
	}

	if (this->isLOpen == false && this->isROpen==false)
	{
		this->bodyMid->maskBits = BULLET_BIT | PLAYER_BIT | ZOOMER_BIT;
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

void Door::SetLeftOpen(bool state)
{
	this->isLOpen = state;
	if (state == false)
		this->bodyLeft->categoryBits = DOOR_BIT;
	//Sound::Play(this->OpenNClose);
}

void Door::SetRightOpen(bool state)
{
	this->isROpen = state;
	if (state == false)
		this->bodyRight->categoryBits = DOOR_BIT;
	//Sound::Play(this->OpenNClose);
}

bool Door::IsROpen()
{
	return this->isROpen;
}

bool Door::IsLOpen()
{
	return this->isLOpen;
}

void Door::SetCanPassLeft(bool flag)
{
	this->canPassLeft = flag;
}

bool Door::GetCanPassLeft()
{
	return this->canPassLeft;
}

void Door::SetCanPassRight(bool flag)
{
	this->canPassRight = flag;
}

bool Door::GetCanPassRight()
{
	return this->canPassRight;
}

