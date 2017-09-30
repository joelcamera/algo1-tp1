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

class PlantMenu : BaseScreen
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
	std::vector<Habilidad> habs;
	
	std::vector<int> finalHabs;
	ListOfButton* finalButtonHabs;
	ListOfButton* createsObjs;

	Animation* anim;

	RenderText* lista;
	RenderText* tab;
	RenderText* arrastrar;
	RenderText* florescreadas;

	PlantMenu()
	{
		cargar();

		TTF_Init();
		::CurrentGame = this;
		SDL_SetWindowSize(App::gWindow, 1200, 800);
		FunctionPtr<double>* f = getFunctionPtr<double>();
		f->Bind<PlantMenu::f>();
	
		//Create the habilities

		FunctionPtr<double>* drag = getFunctionPtr<double>();
		drag->Bind<PlantMenu, &PlantMenu::Drag>(this);

		FunctionPtr<double>* drop = getFunctionPtr<double>();
		drop->Bind<PlantMenu, &PlantMenu::Drop>(this);
		
		std::vector<int> ls = { Assets::generar, Assets::atacar, Assets::explotar };
		habilities = new ListOfButton(20, 20, 3, drag, drop, elems, ls);

		anim = new Animation(100, 100, 400, 480, 500, 600, Assets::b1, 16);

		inputTexts.resize(2);
		inputTexts[0] = new InputText(650, 200, "Vida: ");
		inputTexts[1] = new InputText(650, 250, "Cuanto Pega: ");


		lista = new RenderText(20, 600, 20, "Habilidades seleccionadas:");
		arrastrar = new RenderText(300, 20, 20, "Arrastrar a la Flor sus habilidades. O presionar [a, s, d] segun corresponda.");
		tab = new RenderText(650, 300, 20, "Tab o + para pasar opcion - Enter para crear flor");
		florescreadas = new RenderText(20, 650, 20, "Lista de flores creadas");


		finalHabs = {};
		finalButtonHabs = new ListOfButton(lista->_quoteSurface->w+80, 600, 0, nullptr, nullptr, elems, finalHabs);
		
		createsObjs = new ListOfButton(90, 690, 0, nullptr, nullptr, elems, finalHabs);

		inputTexts[1]->inputTexts = " 0"; inputTexts[1]->changeText();

		for (unsigned int i = 0; i < App::flores.size(); i++)
		{
			if (tiene(App::flores[i].habilidadesF(), 0) && App::flores[i].habilidadesF().size() == 1)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f1, elems);
			}
			if (tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 1)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f2, elems);
			}
			if (tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 1)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f3, elems);
			}
			if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 2)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f4, elems);
			}
			if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f5, elems);
			}
			if (tiene(App::flores[i].habilidadesF(), 1) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f6, elems);
			}
			if (App::flores[i].habilidadesF().size() == 3)
			{
				createsObjs->addButton(nullptr, nullptr, 2, Assets::f7, elems);
			}
		}
		
	}

	bool tiene(std::vector<Habilidad>& v, int h)
	{
		bool ret = false;

		for (unsigned int i = 0; i < v.size(); i++)
		{
			ret = (ret || (v[i] == (Habilidad)h));
		}

		return ret;
	}

	void createObj(double dt)
	{
		//std::cout << "click" << std::endl;
		if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1 && habs.size() > 0 )
		{
			int v = std::stoi(inputTexts[0]->inputTexts);
			int cp = std::stoi(inputTexts[1]->inputTexts);

			if (v == (100 / (habs.size() + 1)))
			{
				if ((tiene(habs, 1) && cp == 12) || (!tiene(habs, 1) && cp == 0))
				{
					App::flores.push_back(*new Flor(v, cp, habs));
					int i = App::flores.size() - 1;
					if (tiene(App::flores[i].habilidadesF(), 0) && App::flores[i].habilidadesF().size() == 1)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f1, elems);
					}
					if (tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 1)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f2, elems);
					}
					if (tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 1)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f3, elems);
					}
					if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 2)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f4, elems);
					}
					if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f5, elems);
					}
					if (tiene(App::flores[i].habilidadesF(), 1) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f6, elems);
					}
					if (App::flores[i].habilidadesF().size() == 3)
					{
						createsObjs->addButton(nullptr, nullptr, 2, Assets::f7, elems);
					}
				}
			}
		}
		inputTexts[0]->inputTexts = " 100"; inputTexts[0]->changeText();
		inputTexts[1]->inputTexts = " 0"; inputTexts[1]->changeText();
		habs.resize(0);
		finalButtonHabs->clear();
	}

	void cargar()
	{
		/*std::ifstream myfile;
		myfile.open("../src/saves/flores.txt");
		int cant = 0;
        myfile >> cant;
        
        App::flores.resize(cant);

		for (unsigned int i = 0; i < cant; i++)
		{
            std::cout << "Flor i : " << i << std::endl;
            
			App::flores[i].Cargar(myfile);
            
            std::cout << "Cant: " << App::flores[i].vidaF() << std::endl;
            
		}
		myfile.close();/**/
	}

	void goback(double dt)
	{
		std::ofstream myfile;
		myfile.open("../src/saves/flores.txt");
		myfile << App::flores.size() << std::endl;
		for (unsigned int i = 0; i < App::flores.size(); i++)
		{
			App::flores[i].Guardar(myfile);
			myfile << std::endl;
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

		int x, y;
		SDL_GetMouseState(&x, &y);

		if (x < 600 && x > 100 && y > 100 && y < 600 && !tiene(habs, (int)dt))
		{

			if (dt == 0)
			{
				habs.push_back(Habilidad::Generar);
			}
			if (dt == 1)
			{
				habs.push_back(Habilidad::Atacar);
				inputTexts[1]->inputTexts = " 12"; inputTexts[1]->changeText();
			}
			if (dt == 2)
			{
				habs.push_back(Habilidad::Explotar);
			}
			inputTexts[0]->inputTexts = " " + std::to_string((int)(100 / (habs.size() + 1))); inputTexts[0]->changeText();
			finalButtonHabs->addButton(nullptr, nullptr, (int)dt, (int)habilities->bs[(unsigned int)dt]->textureID, elems);
		}
		
	}

	static void f(double dt)
	{
		int a = 0;
	}
};
