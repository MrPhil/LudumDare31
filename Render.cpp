#include <SDL.h>
#include "Core.h"

// Put images (aka Surfaces) on the screen
void Render()
{
	// Render Background
	SDL_RenderCopy(Global.Renderer, Global.BackgroundTexture, NULL, NULL);

	// Render the Rocks
	for (int index = 0; index < Global.RockCount; index++)
	{
		SDL_RenderCopy(Global.Renderer, Global.Rocks[index].RockTexture, NULL, &Global.Rocks[index].RockPosition);
	}

	// Render the Player
	SDL_Rect rotation = Global.PlayerRect;
	SDL_RenderCopyEx(Global.Renderer, Global.PlayerSprite, NULL, 
		&Global.PlayerRect, Global.PlayerFacingAngle, NULL, SDL_FLIP_NONE);

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