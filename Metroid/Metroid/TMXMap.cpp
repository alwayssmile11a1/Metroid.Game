#include "TMXMap.h"


TMXMap::TMXMap()
{
	_Width = 0;
	_Height = 0;
	_TileWidth = 0;
	_TileHeight = 0;

	_TileSet = NULL;
	_Layers.clear();
}

TMXMap::~TMXMap()
{
	for (std::vector<TMXTileLayer*>::iterator it = _Layers.begin(); it != _Layers.end(); it++)
	{
		delete *it;
	}

	if (_TileSet != NULL)
	{
		delete _TileSet;
	}

}

void TMXMap::SetAttributes(unsigned int width, unsigned int height, unsigned int tileWidth, unsigned int tileHeight)
{
	_Width = width;
	_Height = height;
	_TileWidth = tileWidth;
	_TileHeight = tileHeight;
}

void TMXMap::SetTileSet(const TMXTileSet &tileSet)
{
	_TileSet = new TMXTileSet();
	*_TileSet = tileSet;
}

void TMXMap::AddLayer(const TMXTileLayer &layer)
{
	TMXTileLayer* tmxlayer = new TMXTileLayer();
	*tmxlayer = layer;
	_Layers.push_back(tmxlayer);
}


TMXTileSet* TMXMap::GetTileSet()
{
	return _TileSet;
}

unsigned int TMXMap::GetWidth()
{
	return _Width;
}


unsigned int TMXMap::GetHeight()
{
	return _Height;
}


unsigned int TMXMap::GetTileWidth()
{
	return _TileWidth;
}


unsigned int TMXMap::GetTileHeight()
{
	return _TileHeight;
}

vector<TMXTileLayer*> TMXMap::GetLayers()
{
	return _Layers;
}

//Render this map
void TMXMap::Render(SpriteBatch &batch)
{

	unsigned int **data = _Layers[0]->GetData();
	unsigned int layerWidth = _Layers[0]->GetWidth();
	unsigned int layerHeight = _Layers[0]->GetHeight();
	Texture* texture = _TileSet->GetTexture();

	unsigned int columns = _TileSet->GetColumns();
	unsigned int tileSetWidth = _TileSet->GetTileWidth();
	unsigned int tileSetHeight = _TileSet->GetTileHeight();


	float x, y, rectLeft, rectTop, rectWidth, rectHeight;

	for (unsigned int row = 0; row < layerHeight; row++)
	{
		for (unsigned int column = 0; column < layerWidth; column++)
		{
			if (data[row][column] == 0) continue;

			rectLeft = (data[row][column] % columns - 1) * tileSetWidth;
			rectTop = (data[row][column] / columns) * tileSetHeight;
			rectWidth = tileSetWidth;
			rectHeight = tileSetHeight;

			x = column*tileSetWidth + rectWidth / 2;
			y = (layerHeight - 1 - row)*tileSetHeight + rectHeight / 2;

			batch.Draw(*texture, x, y, rectLeft, rectTop, rectWidth, rectHeight, rectWidth, rectHeight);
		}
	}


}