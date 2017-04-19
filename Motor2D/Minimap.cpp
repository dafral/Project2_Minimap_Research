#include "Application.h"
#include "Minimap.h"
#include "Render.h"
#include "FileSystem.h"
#include "Textures.h"
#include "Map.h"
#include "EntityManager.h"
#include "p2Log.h"
#include <math.h>

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

#define MAP_POS_X 700 - App->render->camera.x + (mini_tiles[i].coords.x * 0.1)
#define MAP_POS_Y 500 - App->render->camera.y + (mini_tiles[i].coords.y * 0.1)
#define UNITS_POS_X 700 - App->render->camera.x + (coords.x * 0.1)
#define UNITS_POS_Y 500 - App->render->camera.y + (coords.y * 0.1)

Minimap::Minimap() : Module()
{
	name = "minimap";
}

//Destructor
Minimap::~Minimap()
{}

bool Minimap::Awake(pugi::xml_node& config)
{
	return true;
}

bool Minimap::CleanUp()
{
	return true;
}

void Minimap::LoadAtlas(const char* atlas) 
{
	//TODO 1
	//Load the atlas in minimap_atlas. One single line of code -.-
	minimap_atlas = App->tex->Load(atlas);
}



void Minimap::CreateMinimap()
{

	if (App->map->map_loaded == false)
		return;

	for (list<MapLayer*>::iterator it = App->map->data.layers.begin(); it != App->map->data.layers.end(); it++)
	{
		MapLayer* layer = *it;

		if (layer->properties.Get("Nodraw") != 0)
			continue;

		for (int y = 0; y < App->map->data.height; ++y)
		{
			for (int x = 0; x < App->map->data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if (tile_id > 0)
				{
					//TODO 2
					//Get all the information of the real map. We will use it to draw our Mini-map later. Store all the information (the id and the pos should be enough) in the mini_tiles vector.
					//Remember this vector is a minimap_tiles vector.
					minimap_tiles tile;

					tile.coords = App->map->MapToWorld(x, y);
					tile.id = tile_id;

					mini_tiles.push_back(tile);
				}
			}
		}
	}
}

void Minimap::DrawMinimap() {

	//TODO 3
	//Let's draw now the terrain of the map in our minimap. 
	//The SDL_Rects are already created. They are called green, yellow, red and blue. Choose the colors you like the most. 
	//Remember tiles with IDs from 1 to 7 are walkable terrain. The others are water.
	//MAP
	for (uint i = 0; i < mini_tiles.size(); i++) {
		if (mini_tiles[i].id > 0 && mini_tiles[i].id <= 7)

			App->render->Blit(minimap_atlas, MAP_POS_X, MAP_POS_Y, &green);
		
		else
	
			App->render->Blit(minimap_atlas, MAP_POS_X, MAP_POS_Y, &blue);
	}

	//TODO 4
	//Now it's turn for the units. Draw them in the correct position, and remember to choose a different color from the terrain.
	//ALLIED UNITS
	for (list<Unit*>::iterator it = App->entityManager->friendlyUnitList.begin(); it != App->entityManager->friendlyUnitList.end(); it++) {

		iPoint coords;
		coords.x = (*it)->entityPosition.x;
		coords.y = (*it)->entityPosition.y;

		App->render->Blit(minimap_atlas, UNITS_POS_X, UNITS_POS_Y, &yellow);
	}

	//TODO 5
	//Do the same with the enemies
	//ENEMY UNITS
	for (list<Unit*>::iterator it = App->entityManager->enemyUnitList.begin(); it != App->entityManager->enemyUnitList.end(); it++) {

		iPoint coords;
		coords.x = (*it)->entityPosition.x;
		coords.y = (*it)->entityPosition.y;

		App->render->Blit(minimap_atlas, UNITS_POS_X, UNITS_POS_Y, &red);
	}

	//TODO 6
	//SCREEN
	App->render->DrawQuad({ (int)(700 - App->render->camera.x*0.01), (int)(500 - App->render->camera.y*0.01), 80, 60 }, 255, 255, 255, 255, false);
}