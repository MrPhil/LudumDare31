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

	static const Sint32 RockCount = 300;
	Rock Rocks[RockCount];

	Sint32 PlayerControllerId;
	SDL_Texture *PlayerSprite;
	SDL_Rect PlayerRect;
	float PlayerPositionX; 
	float PlayerPositionY;

	void Init()
	{
		Window = NULL;
		Renderer = NULL;
		PlayerControllerId = -1;
		BackgroundTexture = NULL;
		PlayerSprite = NULL;
		PlayerPositionX = 30;
		PlayerPositionY = 30;
		PlayerRect.x = (Uint32)PlayerPositionX;
		PlayerRect.y = (Uint32)PlayerPositionY;
		PlayerRect.h = 24;
		PlayerRect.w = 24;
		lastTime = 0;
		delta = 0;
	}

	void UpdateDelta()
	{
		Uint32 currentTime = SDL_GetTicks();
		delta = (float)(currentTime - (float)lastTime);
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