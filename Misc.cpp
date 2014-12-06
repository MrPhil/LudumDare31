#include <SDL.h>
#include <SDL_image.h>
#include "Core.h"

void ReportSDL_Error(const char* contextOfError)
{
	SDL_Log(contextOfError);
	const char* errorMessage = SDL_GetError();
	SDL_Log(errorMessage);

	// Pop-up Error Message
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		contextOfError,
		errorMessage,
		NULL);
}