#include <SDL.h>

// Setup SDL2

const char WindowTitle[25] = "MrPhil's Ludum Dare 31";

int main(int something, char *args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log(SDL_GetError());
	}
	else
	{
		SDL_Log("Hello World.");

		// We need a Window!
		SDL_Window *window = SDL_CreateWindow(WindowTitle,
			50,
			50,
			1024,
			800,
			0);

		SDL_ShowSimpleMessageBox(0, 
			WindowTitle,
			"Hellow World!",
			window);
	}


	return 0;
}