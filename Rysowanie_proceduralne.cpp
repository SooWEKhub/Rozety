

//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <math.h>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const double radiany = 3.1415 / 180;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Rozety", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Nothing to load
	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
int przelicz(bool czycos, double krok, int fi)
{
	if (czycos) return static_cast<int>(round(krok * cos(radiany * fi)));
	return static_cast<int>(round(krok* sin(radiany* fi)));
}

double funkcjabiegunowa(int k, int a, int b, double omega)
{
	return k * cos(a * sin(b * omega));
}

int main(int argc, char* args[])
{

	int dfi{};
	int d1{};
	int d2{};
	double krok{};
	int dkkrok{};
	int algo{};
	int m{};
	int fi{ 0 };
	bool doonce{ true };
	bool jeszczeraz{ 1 };
	char wybor{};
	int a{}, b{};
	double r;

	while (jeszczeraz)
	{
	std::cout << "Wybierz algorytm:"<<"\n"<<" 1) Spirala wielokatna"<<"\n" << " 2) Gwiazda" << "\n";
	std::cin >> algo;
		switch (algo)
		{
			case 1:
			{
				std::cout << "Wybrano spirale\n";
				std::cout << "Podaj krok (np. 10): ";
				std::cin >> krok;
				std::cout << "Podaj kat (np. 144): ";
				std::cin >> dfi;
				std::cout << "Podaj delta krok (np.5): ";
				std::cin >> dkkrok;
			break;
			}
			case 2:
			{
				std::cout << "Wybrano gwiazde\n";
				std::cout << "Podaj krok (np. 80): ";
				std::cin >> krok;
				std::cout << "Podaj pierwszy kat (np. 50): ";
				std::cin >> d1;
				std::cout << "Podaj drugi kat (np.-50): ";
				std::cin >> d2;
				std::cout << "Liczba krokow miedzt zmiana kata (np. 7): ";
				std::cin >> m;
			break;
			}
			case 3:
			{
				std::cout << "Wybrano krzywe biegunowe\n";
				std::cout << "Podaj A (np. 4): ";
				std::cin >> a;
				std::cout << "Podaj B (np. 2): ";
				std::cin >> b;
				break;
			}

			default:
			{
				std::cout << "Domyœlnie wybrano spirale ";
				std::cout << "Podaj krok: ";
				std::cin >> krok;
				std::cout << "Podaj kat: ";
				std::cin >> dfi;
				std::cout << "Podaj delta krok: ";
				std::cin >> dkkrok;
				algo = 1;
				break;
			}
		}	
	
		//Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
		}
		else
		{
			//Load media
			if (!loadMedia())
			{
				printf("Failed to load media!\n");
			}
			else
			{
				//Main loop flag
				bool quit = false;

				//Event handler
				SDL_Event e;

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);

				//While application is running
				while (!quit)
				{
					//Handle events on queue
					while (SDL_PollEvent(&e) != 0)
					{
						//User requests quit
						if (e.type == SDL_QUIT)
						{
							quit = true;
						}
					}

					if (doonce)
					{
						//	std::cout << doonce;

						int k1{ 400 };
						int w1{ 300 };
						double omega{};
						int k2{};
						int w2{};
						int l{};

						switch (algo)
						{
						case 1:
						{

							for (int i = 1; i <= 100; ++i)
							{
								k2 = k1 + przelicz(1, krok, fi);
								w2 = w1 - przelicz(0, krok, fi);
								fi += dfi;
								if (fi > 360) { fi -= 360; }
								SDL_RenderDrawLine(gRenderer, k1, w1, k2, w2);
								SDL_RenderPresent(gRenderer);
								k1 = k2;
								w1 = w2;
								krok += dkkrok;
							}
							break;
						}
						case 2:
						{

							for (int i = 1; i <= 250; ++i)
							{
								k2 = k1 + przelicz(1, krok, fi);
								w2 = w1 - przelicz(0, krok, fi);
								SDL_RenderDrawLine(gRenderer, k1, w1, k2, w2);
								SDL_RenderPresent(gRenderer);
								k1 = k2;
								w1 = w2;
								if (l % m == 0) { dfi = d1; }
								else dfi = d2;
								//krok += dkkrok;
								fi += dfi;
								if (fi > 360) { fi -= 360; }
								++l;
							}
							break;
						}
						case 3:
						{

							for (int k = 10; k <= 90; k+=10)
							{
								omega = 0;
								r = funkcjabiegunowa(k, a, b, omega);
								k1 = 320 + round(r * cos(omega));
								w1 =200 - round(r * sin(omega));
								for (int fi = 1; fi <= 360; ++fi)
								{
									omega = fi * radiany;
									r = funkcjabiegunowa(k, a, b, omega);
									k2 = 320 + round(r * cos(omega));
									w2 = 200 - round(r * sin(omega));
									SDL_RenderDrawLine(gRenderer, k1, w1, k2, w2);
									SDL_RenderPresent(gRenderer);
									k1 = k2;
									w1 = w2;
								}
							}
							break;
						}

						}

					}
					doonce = false;


					//Update screen
					SDL_RenderPresent(gRenderer);
				}
			}
		}

		//Free resources and close SDL
		close();
		std::cout << "Jeszcze raz? (t/n) \n";
		std::cin >> wybor;
		jeszczeraz = false;
		if (wybor == 116) { doonce = true; jeszczeraz = true; }
	}
	return 0;
}