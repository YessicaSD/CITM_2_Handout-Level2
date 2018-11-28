#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"


j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	BaseFont = App->font->Load("fonts/open_sans/OpenSans-Bold");
	AddLabel({ 0,0 }, "HOLAAAAAA", { 255,255,255,255 }, BaseFont);
	SDL_Rect sec = { 485, 829, 328, 103 };
	AddImage({ 10,10 }, atlas, &sec);
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<itemUi*>* thisItem = ListItemUI.start; thisItem; thisItem = thisItem->next)
	{
		thisItem->data->Draw();
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (p2List_item<itemUi*>* thisItem = ListItemUI.start; thisItem; thisItem = thisItem->next)
	{
		ListItemUI.del(thisItem);
	}
	ListItemUI.clear();
	return true;
}


UiItem_Label* j1Gui::AddLabel(p2Point<int> pos, const char* text, SDL_Color color, TTF_Font * font)
{
	itemUi* newLabel = new UiItem_Label(pos, text, color, font);
	ListItemUI.add(newLabel);
	UiItem_Label* thisLabel = (UiItem_Label*) newLabel;
	return thisLabel;
}

UiItem_Image * j1Gui::AddImage(p2Point<int> pos, SDL_Texture * texture, const SDL_Rect * section)
{
	itemUi* newImage = new UiItem_Image(pos, texture, section);
	ListItemUI.add(newImage);
	UiItem_Image* thisImage = (UiItem_Image*)newImage;
	return thisImage;
	
}
 
// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

