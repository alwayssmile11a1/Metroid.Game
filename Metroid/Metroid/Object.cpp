#include"Object.h"

#define FRAME_RATE 30
#define GROUND_Y 450

Object::Object()
{
	size.setX(0);
	size.setY(0);
	velocity.setX(1.0f);
	velocity.setY(1.0f);
}

Object::Object(float width, float height, float x, float y)
{
	size.setX(width);
	size.setY(height);
	velocity.setX(1.0f);
	velocity.setY(1.0f);
	position.setX(x);
	position.setY(y);
}

Object::Object(const Object &object)
{
	this->size = object.size;
	this->velocity = object.velocity;
	this->position = object.position;
}


Object::~Object()
{

}

//All get functions
Vector2 Object::getBounds()
{
	return size;
}

Vector2 Object::getVelocity()
{
	return velocity;
}

Vector2 Object::getPosition()
{
	return position;
}

//All set functions
void Object::setBounds(Vector2 value)
{
	size = value;
}
void Object::setVelocity(Vector2 value)
{
	velocity = value;
}

void Object::setPosition(Vector2 value)
{
	position = value;
}

void Object::update(DWORD dt)
{
	position.setX(position.getX() + velocity.getX()*1);

	//// Animate kitty if she is running
	//DWORD now = GetTickCount();
	//if (now - last_time > 1000 / FRAME_RATE)
	//{
	//	if (velocity.getX() > 0) object_right->Next();
	//	if (velocity.getX()  < 0) object_left->Next();

	//	last_time = now;
	//}

	//// Simulate fall down
	//if (position.getY() < GROUND_Y) velocity.setY(velocity.getX()+0.5f);
	//else
	//{
	//	position.setY(GROUND_Y);
	//	velocity.setY(0);
	//}
}

void Object::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DSURFACE9 backbuffer, int Delta)
{
	//// Background
	//d3ddv->StretchRect(
	//	Background,			// from 
	//	NULL,				// which portion?
	//	backbuffer,		// to 
	//	NULL,				// which portion?
	//	D3DTEXF_NONE);
	
	if (velocity.getX() > 0)
		object_right->Render(position.getX(), position.getY());
	else if (velocity.getX() < 0)
		object_left->Render(position.getX(), position.getY());
	else if (kitty_vx_last < 0)
		object_left->Render(position.getX(), position.getY());
	else
		object_right->Render(position.getX(), position.getY());
}

void Object::LoadResources(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR Filename, LPCWSTR Filename_Left, LPCWSTR Filename_Right, LPDIRECT3DSURFACE9 _Background, int Sprite_Count, int Sprite_per_row, D3DCOLOR transcolor)
{
	srand((unsigned)time(NULL));

	// TO-DO: not a very good place to initial sprite handler
	/*D3DXCreateSprite(d3ddv, &_SpriteHandler);*/

	Background = _Background;

	//HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	//if (res != D3D_OK) return;

	//_SpriteHandler->GetDevice(&d3ddv);

	object_right = new Sprite(d3ddv, Filename_Right, size.getX(), size.getY(), transcolor);
	object_left = new Sprite(d3ddv, Filename_Right, size.getX(), size.getY(), transcolor);
}

