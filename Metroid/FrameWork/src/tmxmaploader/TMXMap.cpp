#include "TMXMap.h"


TMXMap::TMXMap()
{
	_Width = 0;
	_Height = 0;
	_TileWidth = 0;
	_TileHeight = 0;

	_TileSet = NULL;
	_Layers.clear();
	_ObjectGroups.clear();
	_Cam = NULL;

	_ScaleFactor = 1;
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

	for (std::unordered_map<std::string, TMXObjectGroup*>::iterator it = _ObjectGroups.begin(); it != _ObjectGroups.end(); it++)
	{
		delete it->second;
	}

}

void TMXMap::SetCamera(Camera* camera)
{
	_Cam = camera;
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

void TMXMap::AddObjectGroup(const std::string &groupName, const TMXObjectGroup &objectGroup)
{
	TMXObjectGroup* group = new TMXObjectGroup;
	*group = objectGroup;
	_ObjectGroups[groupName] = group;
}

TMXObjectGroup* TMXMap::GetObjectGroup(const std::string &groupName) const
{
	// Attempt to find and return a map using provided name, else return nullptr
	std::unordered_map<std::string, TMXObjectGroup*>::const_iterator it = _ObjectGroups.find(groupName);

	if (it == _ObjectGroups.end())
	{
		return NULL;
	}
	else
	{
		//first means key, which is mapName
		//second means value, which is TMXMap
		return it->second;
	}
}

TMXTileSet* TMXMap::GetTileSet() const
{
	return _TileSet;
}

unsigned int TMXMap::GetWidth() const
{
	return _Width;
}


unsigned int TMXMap::GetHeight() const
{
	return _Height;
}


unsigned int TMXMap::GetTileWidth() const
{
	return _TileWidth;
}


unsigned int TMXMap::GetTileHeight() const
{
	return _TileHeight;
}

const vector<TMXTileLayer*>& TMXMap::GetLayers() const
{
	return _Layers;
}

//Render this map
void TMXMap::Render(SpriteBatch *batch)
{
	//get necessary variables
	unsigned int **data = _Layers[0]->GetData();
	unsigned int layerWidth = _Layers[0]->GetWidth();
	unsigned int layerHeight = _Layers[0]->GetHeight();

	Texture* texture = _TileSet->GetTexture();
	unsigned int columns = _TileSet->GetColumns();
	unsigned int tileSetWidth = _TileSet->GetTileWidth();
	unsigned int tileSetHeight = _TileSet->GetTileHeight();

	float x, y, rectLeft, rectTop, rectWidth, rectHeight;
	rectWidth = tileSetWidth;
	rectHeight = tileSetHeight;

	float width = tileSetWidth * _ScaleFactor;
	float height = tileSetHeight * _ScaleFactor;

	//Get cam position 
	Vector2 camPostion;
	if (_Cam != NULL)
	{
		camPostion = _Cam->GetPosition();
	}

	for (unsigned int row = 0; row < layerHeight; row++)
	{
		for (unsigned int column = 0; column < layerWidth; column++)
		{
			if (data[row][column] == 0) continue;

			rectLeft = (data[row][column] % columns - 1) * rectWidth;
			rectTop = (data[row][column] / columns) * rectHeight;

			x = column*width + width / 2;
			y = (layerHeight - 1 - row)*height + height / 2;

			//check to see if this tile is out of the scope of the camera
			if (_Cam != NULL)
			{

				if (x + width / 2 < camPostion.x - screenWidth/2 ||
					x - width / 2 > camPostion.x + screenWidth/2 ||
					y + height/2 < camPostion.y - screenHeight/2 ||
					y - height / 2 > camPostion.y + screenHeight / 2)
					continue;

			}

			batch->Draw(*texture, x, y, rectLeft, rectTop, rectWidth, rectHeight, width, height);
		}
	}


}

void TMXMap::SetScale(float scale)
{
	_ScaleFactor = scale;
}

float TMXMap::GetScale()
{
	return _ScaleFactor;
}