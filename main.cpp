#include <SDL.h>

// Setup SDL2

int main(int something, char *args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Log("Hello World.");

	return 0;
}