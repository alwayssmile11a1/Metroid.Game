#ifndef TMXMAP_H
#define TMXMAP_H

#include <vector>
#include "TMXTileSet.h"
#include "TMXTileLayer.h"
#include "TMXObjectGroup.h"
#include "SpriteBatch.h"
#include <unordered_map>

class TMXMap
{
private:
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _TileWidth;
	unsigned int _TileHeight;
	
	TMXTileSet *_TileSet;
	vector<TMXTileLayer*> _Layers;
	std::unordered_map<std::string, TMXObjectGroup*> _ObjectGroups;

	Camera* _Cam; //hold camera reference

public:
	TMXMap();
	~TMXMap();

	//set camera to reduce the amount of tiles that have to be loaded 
	void SetCamera(Camera* camera);
	void SetAttributes(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight);
	void SetTileSet(const TMXTileSet &tileSet);
	void AddLayer(const TMXTileLayer &layer);
	void AddObjectGroup(const std::string &name, const TMXObjectGroup &objectGroup);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	unsigned int GetTileWidth() const;
	unsigned int GetTileHeight() const;

	TMXTileSet *GetTileSet() const;
	const vector<TMXTileLayer*>& GetLayers() const;
	TMXObjectGroup* GetObjectGroup(const std::string &groupName) const;

	//Render this map
	void Render(SpriteBatch *batch);

};

#endif