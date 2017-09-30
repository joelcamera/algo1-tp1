#pragma once
#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif __linux
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif
#include <iostream>
#include "../tp_src/Flor.h"
#include "../tp_src/Vampiro.h"
#include "../tp_src/Nivel.h"


class App
{
public:
	int logicalWith;
	int logicalHeight;
	int renderFPS;
	int logicFPS;

	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;

	static std::vector<Flor> flores;
	static std::vector<Vampiro> vampiros;
	static std::vector<VampiroEnEspera> spawninglist;
	static std::vector<Nivel> niveles;
	static int MaxFilas;
	static int MaxCols;
	static int CSoles;
	static int actualLevel;

	App()
	{
		//Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
		}

		renderFPS = 60;
		logicFPS = 120;

		load();

		//Test
		/*
		vampiros.push_back(*new Vampiro(ClaseVampiro::Caminante, 20, 5));
		vampiros.push_back(*new Vampiro(ClaseVampiro::Caminante, 30, 5));
		vampiros.push_back(*new Vampiro(ClaseVampiro::Desviado, 40, 5));
		vampiros.push_back(*new Vampiro(ClaseVampiro::Caminante, 10, 5));
		vampiros.push_back(*new Vampiro(ClaseVampiro::Desviado, 16, 5));

		flores.push_back(*new Flor(50, 0, std::vector<Habilidad>{Habilidad::Explotar}));
		flores.push_back(*new Flor(50, 12, std::vector<Habilidad>{Habilidad::Atacar}));
		flores.push_back(*new Flor(50, 0, std::vector<Habilidad>{Habilidad::Generar}));
		flores.push_back(*new Flor(33, 12, std::vector<Habilidad>{Habilidad::Generar, Habilidad::Atacar}));
		flores.push_back(*new Flor(33, 12, std::vector<Habilidad>{Habilidad::Explotar, Habilidad::Atacar}));
		flores.push_back(*new Flor(33, 0, std::vector<Habilidad>{Habilidad::Explotar, Habilidad::Generar}));
		flores.push_back(*new Flor(25, 12, std::vector<Habilidad>{Habilidad::Explotar, Habilidad::Atacar, Habilidad::Generar}));

		spawninglist.push_back({ vampiros[0], 0, 0 });
		spawninglist.push_back({ vampiros[1], 1, 0 });
		spawninglist.push_back({ vampiros[2], 2, 0 });
		spawninglist.push_back({ vampiros[3], 3, 0 });
		spawninglist.push_back({ vampiros[4], 4, 0 });
		
		spawninglist.push_back({ vampiros[0], 0, 2 });
		spawninglist.push_back({ vampiros[1], 1, 2 });
		spawninglist.push_back({ vampiros[2], 2, 2 });
		spawninglist.push_back({ vampiros[3], 3, 2 });
		spawninglist.push_back({ vampiros[4], 4, 2 });

		niveles.push_back(*new Nivel(9, 5, 20, spawninglist));/**/
	}

	void load();

	bool init()
	{
		SDL_LogDebug(1, "BOUND: Entrando a la inicializacion");
		//Initialization flag
		bool success = true;
		SDL_SetMainReady();
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				printf("Warning: Linear texture filtering not enabled!");
			}

			

			//Create window
			gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, logicalWith, logicalHeight, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;

			}
			else
			{
				//Create vsynced renderer for window

				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL)
				{
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);

					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						const char* er = IMG_GetError();
						printf("SDL_image could not initialize! SDL_image Error: %s\n", er);
						success = false;
					}
				}
			}
		}

		return success;
	}

	

};