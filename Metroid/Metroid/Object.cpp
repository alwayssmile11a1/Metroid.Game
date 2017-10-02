#include"Object.h"

#define FRAME_RATE 30
#define GROUND_Y 450

Object::Object()
{
	bounds.setX(0);
	bounds.setY(0);
	velocity.setX(1.0f);
	velocity.setY(1.0f);
}

Object::Object(int width, int height)
{
	bounds.setX(width);
	bounds.setY(height);
	velocity.setX(1.0f);
	velocity.setY(1.0f);
}



Object::~Object()
{

}

//All get functions
Vector2 Object::getBounds()
{
	return bounds;
}

Vector2 Object::getVelocity()
{
	return velocity;
}

//All set functions
void Object::setBounds(Vector2 value)
{
	bounds = value;
}
void Object::setVelocity(Vector2 value)
{
	velocity = value;
}

void Object::update(DWORD dt)
{
	bounds.setX(velocity.getX()*dt);
	/*bounds.setX(velocity.getX()*dt);*/

	// Animate kitty if she is running
	DWORD now = GetTickCount();
	if (now - last_time > 1000 / FRAME_RATE)
	{
		if (velocity.getX() > 0) object_right->Next();
		if (velocity.getX()  < 0) object_left->Next();

		last_time = now;
	}

	// Simulate fall down
	if (bounds.getY() < GROUND_Y) velocity.setY(velocity.getX()+0.5f);
	else
	{
		bounds.setY(GROUND_Y);
		velocity.setY(0);
	}
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

	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (velocity.getX() > 0)
		object_right->Render(bounds.getX(), bounds.getY());
	else if (velocity.getX() < 0)
		object_left->Render(bounds.getX(), bounds.getY());
	else if (kitty_vx_last < 0)
		object_left->Render(bounds.getX(), bounds.getY());
	else
		object_right->Render(bounds.getX(), bounds.getY());

	_SpriteHandler->End();
}

void Object::LoadResources(LPDIRECT3DDEVICE9 d3ddv, LPCWSTR Filename, LPCWSTR Filename_Left, LPCWSTR Filename_Right, LPDIRECT3DSURFACE9 _Background, int Sprite_Count, int Sprite_per_row)
{
	srand((unsigned)time(NULL));

	// TO-DO: not a very good place to initial sprite handler
	/*D3DXCreateSprite(d3ddv, &_SpriteHandler);*/

	Background = _Background;

	HRESULT res = D3DXCreateSprite(d3ddv, &_SpriteHandler);
	if (res != D3D_OK) return;

	_SpriteHandler->GetDevice(&d3ddv);

	object_right = new Sprite(d3ddv,_SpriteHandler, Filename_Right, 91, 60, Sprite_Count, Sprite_per_row);
	object_left = new Sprite(d3ddv, _SpriteHandler, Filename_Right, 91, 60, Sprite_Count, Sprite_per_row);
}

