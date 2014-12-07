// Core Function of Ludum Dare 31
// Copyright 2014 Philip Ludington

// Image Stuff
SDL_Texture * Load(const char* imagePath);

// The Rock Object
struct Rock
{
	SDL_Texture *RockTexture;
	SDL_Rect  RockPosition;
};

// THE Global/World Context/Blackboard
struct GlobalStruct
{
	SDL_Window *Window;
	SDL_Renderer *Renderer;

	Uint32 lastTime = 0;
	float delta;

	SDL_Texture *BackgroundTexture;

	static const Sint32 RockCount = 200;
	Rock Rocks[RockCount];

	Sint32 PlayerControllerId;
	SDL_Texture *PlayerSprite;
	SDL_Rect PlayerPosition;

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
		delta = 0;
	}

	void UpdateDelta()
	{
		Uint32 currentTime = SDL_GetTicks();
		delta = (float)(currentTime - (float)lastTime);

		SDL_Log("%d - %d = %f", currentTime, lastTime, delta);

		lastTime = currentTime;
	}

	void LoadSprites()
	{
		char imagePlayerSprite[] = ".\\Data\\Images\\PlayerSprite.png";
		PlayerSprite = Load(imagePlayerSprite);

		char imageRockSprite[] = ".\\Data\\Images\\Rock.png";
		SDL_Texture *rockSprite = Load(imageRockSprite);

		for (int index = 0; index < RockCount; index++)
		{
			Rocks[index].RockTexture = rockSprite;
		}
	}

	void DeleteTextures()
	{
		SDL_DestroyTexture(BackgroundTexture);
		SDL_DestroyTexture(PlayerSprite);

		for (int index = 0; index < RockCount; index++)
		{
			SDL_DestroyTexture(Rocks[index].RockTexture);
		}
	}
};

extern GlobalStruct Global;

// Systems
void ClearRenderer();
void Render();

// Error Stuff
void ReportSDL_Error(const char* contextOfError);