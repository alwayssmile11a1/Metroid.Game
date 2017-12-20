#include "Kraid.h"



Kraid::Kraid()
{

}


Kraid::~Kraid()
{
}

void Kraid::Create(World *world, Texture *texture,Player*player, int x, int y)
{
	this->player = player;
	health = 20;
	stateTime = -1;

	TexturePacker p = TexturePacker(texture, "Resources/bosses_packer.xml");

	animation.AddRegion(p.GetRegion("kraid"));
	animation.SetFrameInterval(0.2);


	SetRegion(*animation.GetKeyAnimation());
	SetSize(160, 130);
	SetPosition(x, y);

	//setup body
	BodyDef bodyDef;
	bodyDef.bodyType = Body::BodyType::Kinematic;
	bodyDef.position.Set(x, y);
	bodyDef.size.Set(160, 130);
	bodyDef.isSensor = true;
	body = world->CreateBody(bodyDef);
	body->categoryBits = KRAID_BIT;
	body->maskBits = PLAYER_BIT | BULLET_BIT | EXPLOSION_BIT;
	body->PutExtra(this);
}


void Kraid::Render(SpriteBatch *batch)
{
	batch->Draw(*this);
}

void Kraid::Update(float dt)
{
	SetRegion(*animation.Next(dt));
	

	if (player->GetPosition().x > this->GetPosition().x && !this->IsFlipX() && stateTime==-1)
	{
		stateTime = 0; //start flipping
	}

	if (player->GetPosition().x < this->GetPosition().x && this->IsFlipX() && stateTime == -1)
	{
		stateTime = 0; //start flipping
	}

	if (stateTime == 0)
	{
		stateTime+=dt;
	}

	if (stateTime > TURNINGDELAYTIME)
	{
		if (player->GetPosition().x > this->GetPosition().x)
		{
			if (stateTime > TURNINGDELAYTIME)
			{
				Flip(true, false);
				stateTime = -1;
			}
		}
		else
		{
			if (stateTime > TURNINGDELAYTIME)
			{
				Flip(false, false);
				stateTime = -1;
			}
		}
	}



}


void Kraid::OnHitBullet()
{
	health--;
}

void Kraid::OnHitBomb()
{
	health -= 3;
}

bool Kraid::IsDead()
{
	return health <= 0;
}
