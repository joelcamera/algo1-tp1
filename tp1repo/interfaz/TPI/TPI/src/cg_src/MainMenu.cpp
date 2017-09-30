#include "MainMenu.h"
#include "Assets.hpp"


std::vector<SDL_Texture*> Assets::textures;

bool MainMenu::init()
{
	return true;
}

bool MainMenu::loadMedia()
{
	
	return true;
}


void MainMenu::ProcessMouse()
{
	unsigned int size = elems.size();
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < elems[i].function.size(); j++)
		{
			if (shouldCall(elems[i].key[j], elems[i].eventAsk[j], elems[i].lastState[j]))
			{
				elems[i].theActions.callResponse(elems[i].function[j], 0.1);
			}
		}
	}
}

void MainMenu::update(double dt)
{

}

void MainMenu::postUpdate()
{
	ProcessMouse();
}

void MainMenu::render()
{
	SDL_SetRenderDrawColor(App::gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(App::gRenderer);
	
	titulo->Render();
	flor->Render();
	vampiro->Render();
	nivel->Render();
	juego->Render();

	//Update screen
	SDL_RenderPresent(App::gRenderer);
}

void MainMenu::close()
{
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

int MainMenu::run()
{
	//Event handler
	SDL_Event e;

	//Current animation frame
	double t = 0.0;
	double dt = 1.0 / logicFPS;

	double currentTime = 0.0;
	double accumulator = 0.0;

	//State toDraw;

	//TODO: Add in the Scene loading screen
	loadMedia();

	//While application is running
	while (!quit)
	{
		double newTime = SDL_GetTicks() / 1000.0;
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				close();
				return -1;
			}
		}

		double delta = newTime - currentTime;
		currentTime = newTime;
		accumulator += delta;

		while (accumulator >= dt)
		{
			//previous = current;
			t += dt;
			accumulator -= dt;

			//Call update from game
			update(dt);

		}

		postUpdate();

		//toDraw = current.interpolate(previous, accumulator/dt);
		render();

		double drawTime = SDL_GetTicks() / 1000.0;
		drawTime = drawTime - newTime;

		while (drawTime < 1.0 / renderFPS)
		{
			drawTime = (SDL_GetTicks() / 1000.0) - newTime;
		}/**/
	}

	return ret;
	close();
}