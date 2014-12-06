#include <SDL.h>
#include <SDL_image.h>
#include "Core.h"

// Setup SDL2

const char WindowTitle[25] = "MrPhil's Ludum Dare 31";

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ReportSDL_Error("SDL_Init");
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
					// Now some images
					char image1Path[] = ".\\Data\\Images\\HelloWorld.png";
					char image2Path[] = ".\\Data\\Images\\Ludum Dare 31.png";

					// Load Image from File
					SDL_Surface *surface;
					surface = IMG_Load(image1Path);
					int imageNumber = 1;
					if (surface != NULL)
					{
						// Get the Texture from the Surface (our PNG)
						SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

						if (texture != NULL)
						{
							// We are done with the surface now
							SDL_FreeSurface(surface);
							surface = NULL;

							bool Running = true;

							// Game Loop
							while (Running)
							{
								// Check events, if ESC then Quit
								SDL_Event event;

								// Put the Game Controller events into the Queue
								SDL_GameControllerUpdate();

								// Event Processing Loop
								while (SDL_PollEvent(&event) == 1)
								{
									// SDL_QUIT

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
														window);
													break;
											}
											break;
										case SDL_CONTROLLERDEVICEADDED:
											//SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_ENABLE);
											SDL_GameControllerOpen(0);
											SDL_Log("Controller plugged in!");
											break;
										case SDL_CONTROLLERBUTTONDOWN:
										case SDL_MOUSEBUTTONDOWN:

											// Swap the image number tracker
											if (imageNumber == 1)
											{
												imageNumber = 2;

												// Load the new Surface/Image #2
												surface = IMG_Load(image2Path);
											}
											else
											{
												imageNumber = 1;

												// Load the new Surface/Image #1
												surface = IMG_Load(image1Path);
											}
											
											// Now create a Texture from it
											if (surface != NULL)
											{
												SDL_Texture *oldTexture = texture;

												// Get the Texture from the Surface (our PNG)
												SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, surface);

												if (newTexture != NULL)
												{
													// Free the no longer needed Surface because now we have a Texture
													SDL_FreeSurface(surface);

													// Save the new Texture
													texture = newTexture;

													// Destroy the old texture
													SDL_DestroyTexture(oldTexture);
												}
											}
											break;
									}
								}

								// Let's clear out the Renderer with MrPhil Green
								SDL_SetRenderDrawColor(renderer, 130, 198, 74, 255);

								//Clear screen
								SDL_RenderClear(renderer);

								// Put image (aka Surface) on the screen
								SDL_RenderCopy(renderer, texture, NULL, NULL);

								// Show use what we've done!
								SDL_RenderPresent(renderer);
							}

							SDL_DestroyTexture(texture);
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

					// Shutdown the Image Reader
					IMG_Quit();
				}
				else
				{
					ReportSDL_Error("IMG_Init");
				}

				// Get rid of our Renderer
				SDL_DestroyRenderer(renderer);
			}
			else
			{
				ReportSDL_Error("SDL_CreateRenderer");
			}

			// bye bye Window
			SDL_DestroyWindow(window);
		}
		else
		{
			ReportSDL_Error("SDL_CreateWindow");
		}

		// All Done
		SDL_Quit();
	}


	return 0;
}