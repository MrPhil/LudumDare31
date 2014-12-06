#include <SDL.h>
#include <SDL_image.h>
#include "Core.h"

SDL_Texture * Load(const char* imagePath)
{
	// Load Image from File
	SDL_Surface *surface = IMG_Load(imagePath);

	if (surface != NULL)
	{
		// Get the Texture from the Surface (our PNG)
		SDL_Texture *texture = SDL_CreateTextureFromSurface(Global.Renderer, surface);

		if (texture != NULL)
		{
			// We are done with the surface now
			SDL_FreeSurface(surface);
			
			return texture;
		}
		else
		{
			ReportSDL_Error("SDL_CreateTextureFromSurface");
		}
	}
	else
	{
		ReportSDL_Error("IMG_Load");
	}

	return NULL;
}