#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct TileSetInfo
{
	uint firstgit = 0;
	const char* name;
	uint tileHeight = 0, tileWidth=0;
	uint spacing = 0;
	uint margin = 0;
	const char* image_sorce;
	uint image_width = 0;
	uint image_height = 0;
	SDL_Texture* Tiletxt;
};


// TODO 1: Create a struct needed to hold the information to Map node
struct Mapinfo
{
	enum class Render_Orientation
	{
		left_down,
		right_down,
		left_up,
		right_up,
		error

	};
	enum class Orientation_State
	{
		
		orthogonal,
		isometric,
		error,

	};

	uint tileHeight = 0, tileWidth=0;
	uint width=0, height=0;
	Render_Orientation renderorder = Render_Orientation::error;
	float version = 0.0f;
	Orientation_State orientation = Orientation_State::error;
};
// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	// TODO 1: Add your struct for map info as public for now
	 Mapinfo mapinfo1;
	 TileSetInfo tilesetinfo1;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;

public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:
	void LoadMap(pugi::xml_node& node);
	void LoadTileSet(pugi::xml_node& node);

};

#endif // __j1MAP_H__