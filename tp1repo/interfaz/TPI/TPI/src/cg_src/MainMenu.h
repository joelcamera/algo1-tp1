#pragma once
#include "CurrentGame.h"
#include "App.h"
#include <vector>
#include "ActionPacked.h"
#include "Types.hpp"

#include <string>
#include <iostream>
#include <fstream>

class MainMenu : BaseScreen
{
public:

	bool init();
	bool loadMedia();
	void update(double dt);
	void postUpdate();
	void render();
	void close();
	int run();

	void ProcessMouse();

	int logicFPS = 120, renderFPS = 60;

	
	std::vector<MouseInputData> elems;
	//Screen OBJS

	Button* flor;
	Button* vampiro;
	Button* juego;
	Button* nivel;

	RenderText* titulo;

	void cargarFlores()
	{
		std::ifstream myfile;
		myfile.open("../src/saves/flores.txt");
		std::string n;
		myfile >> n;
		if (n != "")
		{
            std::cout << "Cant : " << n << std::endl;
            App::flores.resize(std::stoi(n));
			for (int i = 0; i < std::stoi(n); i++)
			{
				App::flores[i].Cargar(myfile);
            }
		}
		myfile.close();
	}

	void cargarVamps()
	{
		std::ifstream myfile;
		myfile.open("../src/saves/vampiros.txt");
		std::string n;
		myfile >> n;
		if (n != "")
		{
            App::vampiros.resize(std::stoi(n));
			for (unsigned int i = 0; i < (unsigned int)std::stoi(n); i++)
			{
				App::vampiros[i].Cargar(myfile);
			}
		}
		myfile.close();
	}

	void cargarSpanw()
	{
		std::ifstream myfile;
		myfile.open("../src/saves/spawnlist.txt");
		std::string n;
		myfile >> n;
		if (n != "")
		{
			for (unsigned int i = 0; i < (unsigned int)std::stoi(n); i++)
			{
				Vampiro f;
				f.Cargar(myfile);
				int af, t;
				myfile >> af;
				myfile >> t;
				VampiroEnEspera e(f, af, t);
				App::spawninglist.push_back(e);
			}
		}
		myfile.close();
	}

	void cargarNiveles()
	{
		std::ifstream myfile;
		myfile.open("../src/saves/niveles.txt");
		std::string n;
		myfile >> n;
		if (n != "")
		{
            App::niveles.resize(std::stoi(n));
			for (int i = 0; i < std::stoi(n); i++)
			{
				App::niveles[i].Cargar(myfile);
			}
		}
		myfile.close();
	}

	MainMenu()
	{
		TTF_Init();

		if (App::flores.empty()) cargarFlores();
		if (App::vampiros.empty()) cargarVamps();
		if (App::spawninglist.empty()) cargarSpanw();
		if (App::niveles.empty()) cargarNiveles();


		::CurrentGame = this;
		SDL_SetWindowSize(App::gWindow, 1200, 800);

		auto ff1 = getFunctionPtr<double>();
		ff1->Bind<MainMenu, &MainMenu::clickb1>(this);

		auto ff2 = getFunctionPtr<double>();
		ff2->Bind<MainMenu, &MainMenu::clickb2>(this);

		auto ff3 = getFunctionPtr<double>();
		ff3->Bind<MainMenu, &MainMenu::clickb3>(this);

		auto ff4 = getFunctionPtr<double>();
		ff4->Bind<MainMenu, &MainMenu::clickb4>(this);

		flor = new Button(400, 200, 2939, 2446, 200, 200, 0, Assets::flower, ff1, nullptr, nullptr);
		vampiro = new Button(650, 200, 256, 256, 200, 200, 1, Assets::batman, ff2, nullptr, nullptr);
		nivel = new Button(400, 440, 168, 168, 200, 200, 2, Assets::spawninglist, ff3, nullptr, nullptr);
		juego = new Button(650, 440, 400, 400, 200, 200, 3, Assets::juegoplay, ff4, nullptr, nullptr);

		elems.push_back(flor->input);
		elems.push_back(vampiro->input);
		elems.push_back(nivel->input);
		elems.push_back(juego->input);

		titulo = new RenderText(500, 20, 40, "Flores vs Zombies!");
	}

	void clickb1(double dt)
	{
		ret = 1;
		quit = true;
		//int a = 0;
	}

	void clickb2(double dt)
	{
		ret = 2;
		quit = true;
	}

	void clickb3(double dt)
	{
		ret = 3;
		quit = true;
	}

	void clickb4(double dt)
	{
		ret = 8;
		quit = true;
	}
};