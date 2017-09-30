#pragma once


#include <iostream>
#include <fstream>

#include "CurrentGame.h"
#include "App.h"
#include <vector>
#include "ActionPacked.h"
#include "Types.hpp"
#include <string>
#include "../tp_src/Types.h"

class CrearNivelesMen : BaseScreen
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

	int actual = 0, inputTextMax = 2;
	std::vector<InputText*> inputTexts;
	
	int actuall = 0, inputTextMaxl = 2;
	std::vector<InputText*> inputTextsl;
	
	std::vector<MouseInputData> elems;
	//Screen OBJS

	ListOfButton* habilities;
	std::vector<ClaseVampiro> habs;
	
	std::vector<int> finalHabs;
	ListOfButton* finalButtonHabs;
	ListOfButton* createsObjs;
	ListOfButton* createsObjs2;

	Animation* anim;

	Button* create;
	Button* back;
	Button* createSpawn;

	RenderText* lista;
	RenderText* tab;
	RenderText* plus;
	RenderText* arrastrar;

	bool yaCreada = false;

	CrearNivelesMen()
	{
		TTF_Init();
		
		std::vector<int> ls;
		ls.resize(App::niveles.size(), 0);
		createsObjs = new ListOfButton(90, 690, App::niveles.size(), nullptr, nullptr, elems, ls);
		ls.clear();
		createsObjs2 = new ListOfButton(90, 20, 0, nullptr, nullptr, elems, ls);

		createsObjs = new ListOfButton(90, 690, 0, nullptr, nullptr, elems, finalHabs);
		for (unsigned int i = 0; i < App::spawninglist.size(); i++)
		{
			if (App::spawninglist[i].vampiro.claseV() == ClaseVampiro::Caminante)
			{
				createsObjs2->addButton(nullptr, nullptr, 2, Assets::v1, elems);
			}
			else
			{
				createsObjs2->addButton(nullptr, nullptr, 2, Assets::v2, elems);
			}
		}

		for (unsigned int i = 0; i < App::niveles.size(); i++)
		{
			createsObjs->addButton(nullptr, nullptr, 2, Assets::create, elems);
		}

		cargarSpawnList();
		cargar();
		
		
		::CurrentGame = this;
		SDL_SetWindowSize(App::gWindow, 1200, 800);
		FunctionPtr<double>* f = getFunctionPtr<double>();
		f->Bind<CrearNivelesMen::f>();
	
		//Create the habilities

		FunctionPtr<double>* drag = getFunctionPtr<double>();
		drag->Bind<CrearNivelesMen, &CrearNivelesMen::Drag>(this);

		FunctionPtr<double>* drop = getFunctionPtr<double>();
		drop->Bind<CrearNivelesMen, &CrearNivelesMen::Drop>(this);
		
		
		//habilities = new ListOfButton(20, 70, App::vampiros.size(), drag, drop, elems, ls);
		lista = new RenderText(20, 630, 20, "Niveles creados:");

		anim = new Animation(100, 200, (int)(384*1.4), (int)(216*1.4), 384, 216, Assets::b2, 32);

		inputTexts.resize(3);
		inputTexts[0] = new InputText(650, 200, "Ancho:  ");
		inputTexts[1] = new InputText(650, 250, "Alto:  ");
		inputTexts[2] = new InputText(650, 300, "Soles:  ");

        if (App::MaxFilas > 0) inputTexts[1]->inputTexts = " " + std::to_string(App::MaxFilas);
		if (App::MaxCols > 0) inputTexts[0]->inputTexts = " " + std::to_string(App::MaxCols);
		if (App::MaxFilas > 0 && App::MaxCols > 0 && App::CSoles > 0 && App::spawninglist.size() > 0)
		{
			inputTexts[2]->inputTexts = " " + std::to_string(App::CSoles);
            inputTexts[0]->changeText();
            inputTexts[1]->changeText();
            inputTexts[2]->changeText();
			yaCreada = true;
            createObj(0);
		}else
        {
            yaCreada = false;
        }

		tab = new RenderText(650, 350, 20, "Tab o + para saltar opcion, Enter para continuar");

		//lista = new RenderText(20, 600, "Tipo seleccionado:");
		//arrastrar = new RenderText(10, 10, "Arrastrar al Vampiro su tipo.");
		

		//finalHabs = *new std::vector<int>();
		//finalButtonHabs = new ListOfButton(lista->_quoteSurface->w+80, 600, 0, nullptr, nullptr, elems, finalHabs);

		auto cre = getFunctionPtr<double>();
		cre->Bind<CrearNivelesMen, &CrearNivelesMen::createObj>(this);

		auto cres = getFunctionPtr<double>();
		cres->Bind<CrearNivelesMen, &CrearNivelesMen::createSpawnList>(this);

		auto ba = getFunctionPtr<double>();
		ba->Bind<CrearNivelesMen, &CrearNivelesMen::goback>(this);

		create = new Button(900, 500, 400, 400, 100, 100, 5, 5, cre, nullptr, nullptr);
		//elems.push_back(create->input);
		
		back = new Button(900, 500 + 110, 400, 400, 100, 100, 5, 5, ba, nullptr, nullptr);
		//elems.push_back(back->input);

		createSpawn = new Button(900, 700, 400, 400, 100, 100, 5, 5, cres, nullptr, nullptr);
		//elems.push_back(createSpawn->input);


		

		
	}

	void cargarSpawnList()
	{
		
	}

	void createSpawnList(double dt)
	{
		//std::cout << "click" << std::endl;
		if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1 && inputTexts[2]->inputTexts.size() > 1)
		{
			App::MaxCols = std::stoi(inputTexts[0]->inputTexts);
			App::MaxFilas = std::stoi(inputTexts[1]->inputTexts);
			App::CSoles = std::stoi(inputTexts[2]->inputTexts);
			//App::MaxFilas = std::stoi()
			
			ret = 5;
			quit = true;

			App::spawninglist.clear();
			actual = 0;
		}
	}

	void createObj(double dt)
	{
		//std::cout << "click" << std::endl;
		if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1 && inputTexts[2]->inputTexts.size() > 1)
		{
			App::MaxCols = std::stoi(inputTexts[0]->inputTexts);
			App::MaxFilas = std::stoi(inputTexts[1]->inputTexts);
			App::CSoles = std::stoi(inputTexts[2]->inputTexts);
			//std::cout << "click" << std::endl;
			if (yaCreada)
			{
				Nivel* nn = new Nivel(App::MaxCols, App::MaxFilas, App::CSoles, App::spawninglist);
				App::niveles.push_back(*nn);
				createsObjs->addButton(nullptr, nullptr, 2, 2, elems);
				yaCreada = false;
			}
			inputTexts[0]->inputTexts = " "; inputTexts[0]->changeText();
			inputTexts[1]->inputTexts = " "; inputTexts[1]->changeText();
			inputTexts[2]->inputTexts = " "; inputTexts[2]->changeText();
			App::CSoles = 0;
			App::MaxCols = 0;
			App::MaxFilas = 0;
			App::spawninglist.clear();
			createsObjs2->clear();
			actual = 0;
			//habs.resize(0);
			//finalButtonHabs->clear();
		}
	}

	void addSpawn()
	{
		std::cout << "Add spawn";
	}



	void cargar()
	{
		
	}

	void goback(double dt)
	{
		std::ofstream myfile;
		myfile.open("../src/saves/niveles.txt");
		myfile << App::niveles.size() << std::endl;
		for (unsigned int i = 0; i < App::niveles.size(); i++)
		{
			App::niveles[i].Guardar(myfile); myfile << std::endl;
		}
		myfile.close();

		inputTexts[0]->inputTexts = " "; inputTexts[0]->changeText();
		inputTexts[1]->inputTexts = " "; inputTexts[1]->changeText();
		inputTexts[2]->inputTexts = " "; inputTexts[2]->changeText();
		actual = 0;

		//std::cout << "Flores guardadas" << std::endl;
	}

	void Drag(double dt)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		habilities->bs[(int)dt]->dst = { x, y, 50, 50 };
		//std::cout << "Drag" << std::endl;
	}

	void Drop(double dt)
	{
		habilities->bs[(int)dt]->dst = { ((int)dt + 1) * habilities->x + (int)dt * 50, habilities->y, 50, 50 };

		if (habs.size() == 0)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			if (x < 600 && x > 100 && y > 100 && y < 600)
			{
				if (dt == 0)
				{
					habs.push_back(ClaseVampiro::Caminante);
				}
				if (dt == 1)
				{
					habs.push_back(ClaseVampiro::Desviado);
				}
				finalButtonHabs->addButton(nullptr, nullptr, (int)dt, (int)dt, elems);
			}
		}
	}

	static void f(double dt)
	{
		int a = 0;
	}
};
