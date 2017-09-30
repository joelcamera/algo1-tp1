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

class VampMenu : BaseScreen
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
	
	
	std::vector<MouseInputData> elems;
	//Screen OBJS

	ListOfButton* habilities;
	std::vector<ClaseVampiro> habs;
	
	std::vector<int> finalHabs;
	ListOfButton* finalButtonHabs;
	ListOfButton* createsObjs;

	Animation* anim;

	Button* create;
	Button* back;

	RenderText* lista;
	RenderText* tab;
	RenderText* arrastrar;
	RenderText* vampiroscreadas;

	VampMenu()
	{
		finalHabs = *new std::vector<int>();
		createsObjs = new ListOfButton(90, 690, 0, nullptr, nullptr, elems, finalHabs);
		for (unsigned int i = 0; i < App::vampiros.size(); i++)
		{
			if (App::vampiros[i].claseV() == ClaseVampiro::Caminante)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::v1, elems);
			}
			else
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::v2, elems);
			}
		}

		cargar();
	
		TTF_Init();
		::CurrentGame = this;
		SDL_SetWindowSize(App::gWindow, 1200, 800);
		FunctionPtr<double>* f = getFunctionPtr<double>();
		f->Bind<VampMenu::f>();
	
		//Create the habilities

		FunctionPtr<double>* drag = getFunctionPtr<double>();
		drag->Bind<VampMenu, &VampMenu::Drag>(this);

		FunctionPtr<double>* drop = getFunctionPtr<double>();
		drop->Bind<VampMenu, &VampMenu::Drop>(this);
		
		std::vector<int> ls = { Assets::v1, Assets::v2 };
		habilities = new ListOfButton(20, 20, 2, drag, drop, elems, ls);

		anim = new Animation(100, 200, (int)(384 * 1.4), (int)(216 * 1.4), 384, 216, Assets::b3, 8);

		inputTexts.resize(2);
		inputTexts[0] = new InputText(650, 200, "Vida:  ");
		inputTexts[1] = new InputText(650, 250, "Cuanto Pega:  ");


		lista = new RenderText(20, 600,20, "Tipo seleccionado:");
		arrastrar = new RenderText(300, 20, 20, "Arrastrar al Vampiro su tipo. O presionar [a, s] segun corresponda.");
		tab = new RenderText(650, 300, 20, "Tab o + para pasar opcion - Enter para crear vampiro");
		vampiroscreadas = new RenderText(20, 650, 20, "Lista de vampiros creados");

		finalButtonHabs = new ListOfButton(lista->_quoteSurface->w+80, 600, 0, nullptr, nullptr, elems, finalHabs);

		FunctionPtr<double>* cre = getFunctionPtr<double>();
		cre->Bind<VampMenu, &VampMenu::createObj>(this);

		FunctionPtr<double>* ba = getFunctionPtr<double>();
		ba->Bind<VampMenu, &VampMenu::goback>(this);

		create = new Button(900, 500, 400, 400, 100, 100, 5, 5, cre, nullptr, nullptr);
		//elems.push_back(create->input);

		back = new Button(900, 500+100, 400, 400, 100, 100, 5,5, ba, nullptr, nullptr);
		//elems.push_back(back->input);

		

		
	}

	void createObj(double dt)
	{
		//std::cout << "click" << std::endl;

		
		if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1 && habs.size() > 0)
		{
			int v = std::stoi(inputTexts[0]->inputTexts);
			ClaseVampiro c = habs[0];
			int cp = std::stoi(inputTexts[1]->inputTexts);

			if (v < 100)
			{
				App::vampiros.push_back(*new Vampiro(c, v, cp));
				createsObjs->addButton(nullptr, nullptr, 2,Assets::v1+c, elems);
			}
		}
		inputTexts[0]->inputTexts = " ";
		inputTexts[1]->inputTexts = " ";
		inputTexts[0]->changeText();
		inputTexts[1]->changeText();
		habs.resize(0);
		actual = 0;
		finalButtonHabs->clear();


	}

	void cargar()
	{
		
	}

	void goback(double dt)
	{
		std::ofstream myfile;
		myfile.open("../src/saves/vampiros.txt");
		myfile << App::vampiros.size() << std::endl;
		for (unsigned int i = 0; i < App::vampiros.size(); i++)
		{
			App::vampiros[i].Guardar(myfile); myfile << std::endl;
		}
		myfile.close();
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
					finalButtonHabs->addButton(nullptr, nullptr, (int)dt, Assets::v1, elems);
					habs.push_back(ClaseVampiro::Caminante);
				}
				if (dt == 1)
				{
					finalButtonHabs->addButton(nullptr, nullptr, (int)dt, Assets::v2, elems);
					habs.push_back(ClaseVampiro::Desviado);
				}
			}
		}
	}

	static void f(double dt)
	{
		int a = 0;
	}
};
