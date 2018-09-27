#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());
	
	
		return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	SDL_Rect rect = { 0,0,tilesetinfo1.image_width,tilesetinfo1.image_height };
	App->render->Blit(tilesetinfo1.Tiletxt, 0, 0, &rect, 0.0f);
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		pugi::xml_node Mapnode= map_file.child("map");
		LoadMap(Mapnode);
		LoadTileSet(Mapnode.child("tileset"));
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}
void j1Map::LoadMap(pugi::xml_node& node)
{

	mapinfo1.height = node.attribute("height").as_uint();
	mapinfo1.width = node.attribute("width").as_uint();
	mapinfo1.tileHeight = node.attribute("tilewidth").as_uint();
	mapinfo1.tileWidth = node.attribute("tileheight").as_uint();
	mapinfo1.version = node.attribute("version").as_float();

	const char* aux = node.attribute("renderorder").as_string();
	if (aux[0] ==  'r')
	{
		if(aux[6]==  'd')
			mapinfo1.renderorder = Mapinfo::Render_Orientation::right_down;
		else 
			mapinfo1.renderorder = Mapinfo::Render_Orientation::right_up;
	}
	else if (aux[0] ==  'l')
	{
		if (aux[5] ==  'd')
			mapinfo1.renderorder = Mapinfo::Render_Orientation::left_down;
		else
			mapinfo1.renderorder = Mapinfo::Render_Orientation::left_up;
	}

	aux = node.attribute("orientation").as_string();
	if (aux == "orthogonal")
	{
		mapinfo1.orientation = Mapinfo::Orientation_State::orthogonal;
	}
	
}
void j1Map::LoadTileSet(pugi::xml_node& node)
{
	tilesetinfo1.firstgit = node.attribute("firstgid").as_int();
	tilesetinfo1.name = node.attribute("name").as_string();
	tilesetinfo1.tileWidth = node.attribute("tilewidth").as_uint();
	tilesetinfo1.tileHeight = node.attribute("tileheight").as_uint();
	tilesetinfo1.spacing = node.attribute("spacing").as_uint();
	tilesetinfo1.margin = node.attribute("margin").as_uint();
	tilesetinfo1.image_sorce = node.child("image").attribute("source").as_string();

	tilesetinfo1.image_height= node.child("image").attribute("height").as_uint();
	tilesetinfo1.image_width = node.child("image").attribute("width").as_uint();
	LOG("%s", tilesetinfo1.image_sorce);
	tilesetinfo1.Tiletxt = App->tex->Load("maps/tmw_desert_spacing.png");
	/*for (pugi::xml_node tool = node; tool; tool = tool.next_sibling("Tool"))
	{
		xMainNode.select_nodes("name").size()
	}*/
}