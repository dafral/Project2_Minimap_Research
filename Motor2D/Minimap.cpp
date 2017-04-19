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

#define POS_X 700 - App->render->camera.x + (coords.x * 0.1)
#define POS_Y 500 - App->render->camera.y + (coords.y * 0.1)

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

					iPoint coords = App->map->MapToWorld(x, y);
					
					if (tile_id > 0 && tile_id <= 7)

						App->render->Blit(minimap_atlas, POS_X, POS_Y, &green);

					else

						App->render->Blit(minimap_atlas, POS_X, POS_Y, &blue);

				}
			}
		}
	}
}

void Minimap::UpdateMinimap() {

	//ALLIED UNITS
	for (list<Unit*>::iterator it = App->entityManager->friendlyUnitList.begin(); it != App->entityManager->friendlyUnitList.end(); it++) {

		iPoint coords;
		coords.x = (*it)->entityPosition.x;
		coords.y = (*it)->entityPosition.y;

		App->render->Blit(minimap_atlas, POS_X, POS_Y, &yellow);
	}

	//ENEMY UNITS
	for (list<Unit*>::iterator it = App->entityManager->enemyUnitList.begin(); it != App->entityManager->enemyUnitList.end(); it++) {

		iPoint coords;
		coords.x = (*it)->entityPosition.x;
		coords.y = (*it)->entityPosition.y;

		App->render->Blit(minimap_atlas, POS_X, POS_Y, &red);
	}
}