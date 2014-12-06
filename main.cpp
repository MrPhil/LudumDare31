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
		SDL_Window *window = SDL_CreateWindow(
			WindowTitle,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1024,
			800,
			0); // Window Flags

		if (window != NULL)
		{
			// Get our Renderer
			SDL_Renderer* renderer = SDL_CreateRenderer(
				window, 
				-1, // Index of the rendering driver to initialize (-1 for first supporting)
				0); // Renderer Flags

			if (renderer != NULL)
			{
				// Initialize the Image reader lib (PNG)
				if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
				{
					// Now an image
					char imagePath[] = ".\\Data\\Images\\HelloWorld.png";

					// Load Image from File
					SDL_Surface *surface;
					surface = IMG_Load(imagePath);
					if (surface != NULL)
					{
						// Get the Texture from the Surface (our PNG)
						SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

						if (texture != NULL)
						{
							// Let's clear out the Renderer with MrPhil Green
							SDL_SetRenderDrawColor(renderer, 130, 198, 74, 255);

							//Clear screen
							SDL_RenderClear(renderer);

							//// 
							//SDL_RenderCopy(renderer, texture, NULL, NULL);

							// Show use what we've done!
							SDL_RenderPresent(renderer);

							// Give us time to see the window.
							SDL_Delay(5000);

							// Now a message box
							SDL_ShowSimpleMessageBox(0,
								WindowTitle,
								"Success!",
								window);

							SDL_DestroyTexture(texture);
						}
						else
						{
							SDL_Log("FAILED: SDL_CreateTextureFromSurface");
							SDL_Log(SDL_GetError());
						}

						// We are done with the surface now
						SDL_FreeSurface(surface);
					}
					else
					{
						SDL_Log("FAILED: IMG_Load");
						SDL_Log(SDL_GetError());
					}

					// Shutdown the Image Reader
					IMG_Quit();
				}
				else
				{
					SDL_Log("FAILED: IMG_Init");
					SDL_Log(SDL_GetError());
				}

				// Get rid of our Renderer
				SDL_DestroyRenderer(renderer);
			}
			else
			{
				SDL_Log("FAILED: SDL_GetRenderer");
				SDL_Log(SDL_GetError());
			}

			// bye bye Window
			SDL_DestroyWindow(window);
		}
		else
		{
			SDL_Log("FAILED: SDL_CreateWindow");
			SDL_Log(SDL_GetError());
		}

		// All Done
		SDL_Quit();
	}


	return 0;
}