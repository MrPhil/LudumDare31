// Core Function of Ludum Dare 31
// Copyright 2014 Philip Ludington

// THE Global/World Context/Blackboard
struct GlobalStruct
{
	SDL_Window *Window;
	SDL_Renderer* Renderer;
	Sint32 PlayerControllerId = -1;
};

extern GlobalStruct Global;

// Image Stuff
SDL_Texture * Load(const char* imagePath);

// Error Stuff
void ReportSDL_Error(const char* contextOfError);