#include <SDL.h>
#include "Core.h"

void Render()
{
	// Render Background
	SDL_RenderCopy(Global.Renderer, Global.BackgroundTexture, NULL, NULL);

	// Put image (aka Surface) on the screen
	SDL_RenderCopy(Global.Renderer, Global.PlayerSprite, NULL, NULL);

	// Show use what we've done!
	SDL_RenderPresent(Global.Renderer); 
}

void ClearRenderer()
{
	// Let's clear out the Renderer with MrPhil Green
	SDL_SetRenderDrawColor(Global.Renderer, 130, 198, 74, 255);

	//Clear screen
	SDL_RenderClear(Global.Renderer);
}