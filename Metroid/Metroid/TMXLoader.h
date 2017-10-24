#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <memory>

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
	void LoadTileSets(TMXMap* map, rapidxml::xml_node<> *parentNode);
	void LoadLayers(TMXMap* map, rapidxml::xml_node<> *parentNode);

	/* File loading helper functions */
	bool LoadFile(std::string filePath, std::string &fileContents);

public:
	TMXLoader();
	~TMXLoader();

	void AddMap(std::string mapName, std::string filePath);
	TMXMap* GetMap(std::string mapName);

};
