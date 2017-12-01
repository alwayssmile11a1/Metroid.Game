#ifndef TMXOBJECTGROUP_H
#define TMXOBJECTGROUP_H

#include <string>
#include <vector>
#include "Rectangle.h"


class TMXObjectGroup
{
private:
	std::string _Name;
	std::vector<Shape::Rectangle> _Rectangles;

public:
	TMXObjectGroup();
	~TMXObjectGroup();
	//TMXObjectGroup(const TMXObjectGroup &tmxObjectGroup);
	//TMXObjectGroup& operator=(const TMXObjectGroup &tmxObjectGroup);

	void SetAttributes(const std::string& name);
	void AddRect(const Shape::Rectangle &rectangle);

	std::string GetName();
	const std::vector<Shape::Rectangle>& GetRects() const;

};

#endif