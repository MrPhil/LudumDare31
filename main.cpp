#include <SDL.h>
#include <SDL_image.h>
#include "Core.h"

const char WindowTitle[25] = "MrPhil's Ludum Dare 31";

// This holds our systems
GlobalStruct Global;

int main(int argc, char *argv[])
{
	// Setup SDL2
	SDL_Log("MrPhil's Ludum Dare 31 has started!");

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // 0 means success
	{
		// We need a Window!
		Global.Window = SDL_CreateWindow(
			WindowTitle,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			1024,
			800,
			0); // Window Flags

		if (Global.Window != NULL)
		{
			// Get our Renderer
			Global.Renderer = SDL_CreateRenderer(
				Global.Window,
				-1, // Index of the rendering driver to initialize (-1 for first supporting)
				0); // Renderer Flags

			if (Global.Renderer != NULL)
			{
				// One time clear before kicking off the Game Loop
				ClearRenderer();

				// Initialize the Image reader lib (PNG)
				if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG)
				{
					// Now some images
					char image1Path[] = ".\\Data\\Images\\Ludum Dare 31.png";
					char image2Path[] = ".\\Data\\Images\\HelloWorld.png";
					char imagePlayerSprite[] = ".\\Data\\Images\\PlayerSprite.png";

					// Load Images from File to Global Texture Space
					Global.BackgroundTexture = Load(image1Path);
					Global.PlayerSprite = Load(imagePlayerSprite);

					int imageNumber = 1;
					bool Running = true;

					// Game Loop
					while (Running)
					{
						// Check events
						SDL_Event event;

						// Event Processing Loop
						while (SDL_PollEvent(&event) == 1)
						{
							// Process the event
							switch (event.type)
							{
							case SDL_QUIT:
								Running = false;
								break;
							case SDL_KEYDOWN:
								switch (event.key.keysym.sym)
								{
								case SDLK_ESCAPE:
									Running = false;
									break;
								case SDLK_KP_ENTER:
									// Now a message box
									SDL_ShowSimpleMessageBox(0,
										WindowTitle,
										"Good Job! You Pressed Keypad Enter!",
										Global.Window);
									break;
								case SDLK_a:
									SDL_Log("A Press!");
									break;
								}
								break;
							case SDL_CONTROLLERDEVICEADDED:
								if (Global.PlayerControllerId == -1)
								{
									Global.PlayerControllerId = event.cdevice.which;
									SDL_GameControllerOpen(0);
									SDL_Log("Player 1 controller plugged in!");
								}
								else
								{
									SDL_Log("Unused controller plugged in!");
								}
								break;
							case SDL_CONTROLLERBUTTONDOWN:
							case SDL_MOUSEBUTTONDOWN:

								// Swap the image number tracker
								SDL_Texture *newTexture;
								if (imageNumber == 1)
								{
									imageNumber = 2;

									// Load the new Surface/Image #2
									newTexture = Load(image2Path);
								}
								else
								{
									imageNumber = 1;

									// Load the new Surface/Image #1
									newTexture = Load(image1Path);
								}

								// Now create a Texture from it
								if (newTexture != NULL)
								{
									// Destroy the old texture
									SDL_DestroyTexture(Global.BackgroundTexture);

									// Save the new Texture
									Global.BackgroundTexture = newTexture;
								}
								break;
							}
						}

						Render();
					}

					SDL_DestroyTexture(Global.BackgroundTexture);
					SDL_DestroyTexture(Global.PlayerSprite);

					// Shutdown the Image Reader
					IMG_Quit();
				}
				else
				{
					ReportSDL_Error("IMG_Init");
				}

				// Get rid of our Renderer
				SDL_DestroyRenderer(Global.Renderer);
			}
			else
			{
				ReportSDL_Error("SDL_CreateRenderer");
			}

			// bye bye Window
			SDL_DestroyWindow(Global.Window);
		}
		else
		{
			ReportSDL_Error("SDL_CreateWindow");
		}

		// All Done
		SDL_Quit();
	}
	else
	{
		ReportSDL_Error("SDL_Init");
	}

	return 0;
}