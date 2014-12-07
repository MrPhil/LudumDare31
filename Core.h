// Core Function of Ludum Dare 31
// Copyright 2014 Philip Ludington

// THE Global/World Context/Blackboard
struct GlobalStruct
{
	SDL_Window *Window;
	SDL_Renderer* Renderer;
	Sint32 PlayerControllerId;
	SDL_Texture* BackgroundTexture;
	SDL_Texture* PlayerSprite;
	SDL_Rect PlayerPosition;
	Uint32 lastTime = 0;
	Uint32 currentTime;
	Uint32 delta;

	void Init()
	{
		Window = NULL;
		Renderer = NULL;
		PlayerControllerId = -1;
		BackgroundTexture = NULL;
		PlayerSprite = NULL;
		PlayerPosition.x = 0;
		PlayerPosition.y = 0;
		PlayerPosition.h = 30;
		PlayerPosition.w = 30;
		lastTime = 0;
		currentTime = 0;
		delta = 0;
	}

	void UpdateDelta()
	{
		currentTime = SDL_GetTicks();
		delta = currentTime - lastTime;
		lastTime = currentTime;
	}
};

extern GlobalStruct Global;

// Image Stuff
SDL_Texture * Load(const char* imagePath);

// Systems
void ClearRenderer();
void Render();

// Error Stuff
void ReportSDL_Error(const char* contextOfError);