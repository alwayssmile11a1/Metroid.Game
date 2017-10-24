#pragma once

#include <vector>
#include "TMXTileSet.h"
#include "TMXTileLayer.h"
#include "SpriteBatch.h"

class TMXMap
{
private:
	unsigned int _Width;
	unsigned int _Height;
	unsigned int _TileWidth;
	unsigned int _TileHeight;
	
	TMXTileSet *_TileSet;
	vector<TMXTileLayer*> _Layers;


public:
	TMXMap();
	~TMXMap();

	void SetAttributes(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight);
	void SetTileSet(const TMXTileSet &tileSet);
	void AddLayer(const TMXTileLayer &layer);

	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetTileWidth();
	unsigned int GetTileHeight();

	TMXTileSet *GetTileSet();
	vector<TMXTileLayer*> GetLayers();

	//Render this map
	void Render(SpriteBatch &batch);

};