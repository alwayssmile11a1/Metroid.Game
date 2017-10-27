#pragma once


#include <unordered_map>
#include "rapidxml.hpp"
#include "TMXMap.h"
#include "TMXTileLayer.h"
#include "TMXTileSet.h"

class TMXLoader
{
private:

	//use unordered_map for fast access purpose
	std::unordered_map<std::string, TMXMap*> _MapContainer;


	//private functions
	void LoadMapSettings(TMXMap* map, rapidxml::xml_node<> *parentNode);
	void LoadTileSets(TMXMap* map, rapidxml::xml_node<> *parentNode, std::string folderPath);
	void LoadLayers(TMXMap* map, rapidxml::xml_node<> *parentNode);


public:
	TMXLoader();
	~TMXLoader();

	void AddMap(std::string mapName, std::string filePath);
	TMXMap* GetMap(std::string mapName);

};
