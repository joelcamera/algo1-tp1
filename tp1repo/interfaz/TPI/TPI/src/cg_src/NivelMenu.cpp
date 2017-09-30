#include "NivelMenu.h"
#include "Assets.hpp"

bool NivelMenu::init()
{
	return true;
}

bool NivelMenu::loadMedia()
{
	SDL_StartTextInput();



	return true;
}


void NivelMenu::ProcessMouse()
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


void NivelMenu::update(double dt)
{
	if (App::niveles.size() > 0)
	{
		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].vampirosN().size(); i++)
		{
			vamps[i].update(dt);
		}

		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].floresN().size(); i++)
		{
			flors[i].update(dt);
		}
	}
}

void NivelMenu::postUpdate()
{
	ProcessMouse();
	
}

void NivelMenu::render()
{
	SDL_SetRenderDrawColor(App::gRenderer, 0x14, 0x14, 0x14, 0xFF);
	SDL_RenderClear(App::gRenderer);

	background.Render();

	

	if (App::niveles.size() > 0)
	{
		if (grows != 5 || gcols != 9)
		{
			SDL_Rect s, d;
			for (int i = 0; i < grows; i++)
			{
				for (int j = 0; j < gcols; j++)
				{
					s = { 0, 0, 200, 200 };
					d = { gridx + (cuadw*j), gridy + (cuadh*i), cuadw, cuadh };
					int tid = 6;
					if ((i + j) % 2 == 0) tid = 7;
					SDL_RenderCopyEx(App::gRenderer, Assets::getTexture(tid), &s, &d, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
				}
			}
		}

		buttons->Render();

		//Actualizo las flores
		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].floresN().size(); i++)
		{
			flors[i].Render();
			vidaFlors[i].Render();
		}

		//Actualizo vampiros
		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].vampirosN().size(); i++)
		{
			vamps[i].Render();
			vidaVamps[i].Render();
		}

		cheat->Render();
		nextTurn->Render();
		agregarF->Render();
		prevTurn->Render();
		osdB->Render();
		save->Render();
	}
	

	

	//Update screen
	SDL_RenderPresent(App::gRenderer);
}

void NivelMenu::close()
{}

int NivelMenu::run()
{
	//Main loop flag
	bool quit = false;

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
				quit = true;
			}
			else if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
			{
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB)
				{
					actual = (actual +1)%3;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && inputTexts[actual].length() > 1)
				{
					inputTexts[actual] = inputTexts[actual].substr(0, inputTexts[actual].length() - 1);
				}
				if (e.type == SDL_TEXTINPUT)
				{
					inputTexts[actual] += e.text.text;
					//std::cout << std::stoi(inputTexts[actual]) << std::endl;
				}
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

	return 0;
	close();
}
