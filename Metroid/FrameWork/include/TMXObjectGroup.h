#ifndef TMXOBJECTGROUP_H
#define TMXOBJECTGROUP_H

#include <string>
#include <vector>
#include "Body.h"


class TMXObjectGroup
{
private:
	std::string _Name;
	std::vector<Body*> _Bodies;

public:
	TMXObjectGroup();
	~TMXObjectGroup();
	TMXObjectGroup(const TMXObjectGroup &tmxObjectGroup);
	TMXObjectGroup& operator=(const TMXObjectGroup &tmxObjectGroup);

	void SetAttributes(const std::string& name);
	void AddBody(const Body &body);

	std::string GetName();
	const std::vector<Body*>& GetBodies() const;

};

#endif