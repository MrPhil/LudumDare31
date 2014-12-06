#include <SDL.h>
#include <SDL_image.h>

// Setup SDL2

const char WindowTitle[25] = "MrPhil's Ludum Dare 31";

int main(int argc, char *argv[])
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

		if (window)
		{
			// Initialize the Image reader lib (PNG)
			if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) 
			{
				SDL_Log(IMG_GetError());
			}
			else
			{
				// Now an image
				char imagePath[] = ".\\Data\\Images\\HelloWorld.png";

				// Load Image from File
				SDL_Surface *image;
				image = IMG_Load(imagePath);
				if (image) 
				{
					SDL_Log("Success!");
				}
				else
				{
					SDL_Log(IMG_GetError());
				}

				// Shutdown the Image Reader
				IMG_Quit();
			}

			// Now a message box
			SDL_ShowSimpleMessageBox(0,
				WindowTitle,
				"All Done!",
				window);

			// bye bye Window
			SDL_DestroyWindow(window);
		}
	
		// All Done
		SDL_Quit();
	}


	return 0;
}