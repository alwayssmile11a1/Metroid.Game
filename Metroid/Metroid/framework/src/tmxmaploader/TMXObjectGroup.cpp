#include "TMXObjectGroup.h"



TMXObjectGroup::TMXObjectGroup()
{
	_Bodies.clear();
}


TMXObjectGroup::~TMXObjectGroup()
{
	for (std::vector<Body*>::iterator bo = _Bodies.begin(); bo != _Bodies.end(); ++bo)
	{
		delete *bo;
	}
}

TMXObjectGroup::TMXObjectGroup(const TMXObjectGroup &tmxObjectGroup)
{
	_Name = tmxObjectGroup._Name;
	for ( std::vector<Body*>:: const_iterator bo = tmxObjectGroup._Bodies.begin(); bo != tmxObjectGroup._Bodies.end(); ++bo)
	{
		Body*body = new Body();
		*body = **bo;

		_Bodies.push_back(body);
	}

}
TMXObjectGroup& TMXObjectGroup::operator=(const TMXObjectGroup &tmxObjectGroup)
{
	_Name = tmxObjectGroup._Name;
	for (std::vector<Body*>::const_iterator bo = tmxObjectGroup._Bodies.begin(); bo != tmxObjectGroup._Bodies.end(); ++bo)
	{
		Body*body = new Body();
		*body = **bo;

		_Bodies.push_back(body);
	}

	return *this;
}

void TMXObjectGroup::SetAttributes(const std::string& name)
{
	_Name = name;
}
void TMXObjectGroup::AddBody(const Body &body)
{
	Body *bo = new Body();
	*bo = body;
	_Bodies.push_back(bo);
}

std::string  TMXObjectGroup::GetName()
{
	return _Name;
}

const std::vector<Body*>& TMXObjectGroup::GetBodies() const
{
	return _Bodies;
}