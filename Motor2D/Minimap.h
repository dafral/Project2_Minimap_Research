#ifndef __MINIMAP_H__
#define __MINIMAP_H__

#include "Module.h"

class Minimap : public Module
{
public:

	Minimap();

	//Destructor
	virtual ~Minimap();

	//Called before render is available
	bool Awake(pugi::xml_node&);

	//Called before quitting
	bool CleanUp();

	//Create Minimap terrain
	void Minimap::CreateMinimap();

public:

	SDL_Texture* minimap_atlas;

	SDL_Rect green =	{ 0, 0, 4, 4 };
	SDL_Rect blue =		{ 4, 0, 4, 4 };
	SDL_Rect red =		{ 0, 4, 4, 4 };
	SDL_Rect yellow =	{ 4, 4, 4, 4 };

};


#endif //__MINIMAP_H__