/*This source code copyrighted by Lazy Foo' Productions (2004-2014)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include "Types.hpp"
#include <stdio.h>
#include <string>

#include "App.h"
#include "MainMenu.h"
#include "PlantMenu.h"
#include "VampMenu.h"
#include "NivelMenu.h"
#include "CrearNivelesMenu.h"
#include "CreateSpawnListMenu.h"

#include <cstdio>
#include <cstdlib>



int main(int argc, char* args[])
{
	App* app = new App();
	
	int next = 0;

	while (true)
	{
		if (next == 0)
		{
			MainMenu* mainMenu = new MainMenu();
			next = mainMenu->run();

			if (next == -1) return 0;
		}

		if (next == 1)
		{
			PlantMenu* plantMenu = new PlantMenu();
			plantMenu->run();
			next = 0;
		}

		if (next == 2)
		{
			VampMenu* vampMenu = new VampMenu();
			vampMenu->run();
			next = 0;
		}

		if (next == 3)
		{
			CrearNivelesMen* crearNivelMenu = new CrearNivelesMen();
			next = crearNivelMenu->run();
			
		}

		if (next == 5)
		{
			CreateSpawnListMenu* crearList = new CreateSpawnListMenu();
			next = crearList->run();
		}

		if (next == 8)
		{
			NivelMenu* crearJuego = new NivelMenu(0);
			next = crearJuego->run();
		}
	}
	return 0;
}



