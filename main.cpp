#include <SDL.h>
#include <SDL_image.h>
#include "Core.h"

const char WindowTitle[25] = "MrPhil's Ludum Dare 31";

// This holds our systems
GlobalStruct Global;

bool up = false;
bool down = false;
bool left = false;
bool right = false;

void SwapBackground()
{
	char image1Path[] = ".\\Data\\Images\\Ludum Dare 31.png";
	char image2Path[] = ".\\Data\\Images\\HelloWorld.png";

	static int imageNumber = 1;

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
}

void ProcessPlayerMovement()
{
	if (up)
	{
		Global.PlayerPosition.y -= 1;
	}

	if (down)
	{
		Global.PlayerPosition.y += 1;
	}
								
	if (left)
	{
		Global.PlayerPosition.x -= 1;
	}
	
	if(right)
	{
		Global.PlayerPosition.x += 1;
	}
}

int main(int argc, char *argv[])
{
	// Setup SDL2
	SDL_Log("MrPhil's Ludum Dare 31 has started!");

	// Step 1 - Initialize the Global
	Global.Init();

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
					// Load Images from File to Global Texture Space
					SwapBackground();
					char imagePlayerSprite[] = ".\\Data\\Images\\PlayerSprite.png";
					Global.PlayerSprite = Load(imagePlayerSprite);

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
								if (event.cbutton.which == Global.PlayerControllerId)
								{
									switch (event.cbutton.button)
									{
									case SDL_CONTROLLER_BUTTON_DPAD_UP:
										up = true;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
										down = true;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
										left = true;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
										right = true;
										break;
									case SDL_CONTROLLER_BUTTON_A:
										SwapBackground();
										break;
									case SDL_CONTROLLER_BUTTON_B:
										SwapBackground();
										break;
									case SDL_CONTROLLER_BUTTON_X:
										SwapBackground();
										break;
									case SDL_CONTROLLER_BUTTON_Y:
										SwapBackground();
										break;
									}
								}
								break;
							case SDL_CONTROLLERBUTTONUP:
								if (event.cbutton.which == Global.PlayerControllerId)
								{
									switch (event.cbutton.button)
									{
									case SDL_CONTROLLER_BUTTON_DPAD_UP:
										up = false;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
										down = false;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
										left = false;
										break;
									case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
										right = false;
										break;
									}
								}
								break;
							case SDL_MOUSEBUTTONDOWN:
								SwapBackground();
								break;
							}
						}

						ProcessPlayerMovement();

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