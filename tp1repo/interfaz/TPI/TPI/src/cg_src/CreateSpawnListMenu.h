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

class CreateSpawnListMenu : BaseScreen
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

	
	std::vector<ClaseVampiro> habs;
	
	std::vector<int> finalHabs;
	
	ListOfButton* finalButtonHabs;
	ListOfButton* createsObjs;
	ListOfButton* habilities;
	
	Animation* anim;

	Button* create;
	Button* back;

	RenderText* lista;
	RenderText* tab;
	RenderText* space;
	RenderText* arrastrar;

	CreateSpawnListMenu()
	{
		borrar();

		TTF_Init();
		::CurrentGame = this;
		SDL_SetWindowSize(App::gWindow, 1200, 800);
		FunctionPtr<double>* f = getFunctionPtr<double>();
		f->Bind<CreateSpawnListMenu::f>();
	
		//Create the habilities

		FunctionPtr<double>* drag = getFunctionPtr<double>();
		drag->Bind<CreateSpawnListMenu, &CreateSpawnListMenu::Drag>(this);

		FunctionPtr<double>* drop = getFunctionPtr<double>();
		drop->Bind<CreateSpawnListMenu, &CreateSpawnListMenu::Drop>(this);
		
		std::vector<int> ls = { 0, 1 };
		habilities = new ListOfButton(20, 20, 2, drag, drop, elems, ls);

		anim = new Animation(100, 100, 500, 500, 500, 500, 3, 8);

		inputTexts.resize(3);
		inputTexts[0] = new InputText(250, 200, "Index del vampiro [0 to " + std::to_string((int)App::vampiros.size()-1) + "]: ");
		inputTexts[1] = new InputText(250, 250, "Fila: [0 to " + std::to_string(App::MaxFilas-1) + "]: ");
		inputTexts[2] = new InputText(250, 300, "Turno: ");

		//arrastrar = new RenderText(300, 20, "Arrastrar al Vampiro su tipo.");
		tab = new RenderText(250, 350, 20, "Tab o + para saltar opcion, enter para agregar Spawn, Espacio para terminar");
		space = new RenderText(250, 4000, 20, "Espacio para terminar");
		//finalHabs = *new std::vector<int>();
		//finalButtonHabs = new ListOfButton(lista->_quoteSurface->w+80, 600, 0, nullptr, nullptr, elems, finalHabs);

		FunctionPtr<double>* cre = getFunctionPtr<double>();
		cre->Bind<CreateSpawnListMenu, &CreateSpawnListMenu::createObj>(this);

		FunctionPtr<double>* ba = getFunctionPtr<double>();
		ba->Bind<CreateSpawnListMenu, &CreateSpawnListMenu::goback>(this);

		create = new Button(900, 500, 400, 400, 100, 100, 5, 5, cre, nullptr, nullptr);
		//elems.push_back(create->input);

		back = new Button(900, 500 + 100, 400, 400, 100, 100, 5, 5, ba, nullptr, nullptr);
		//elems.push_back(back->input);

		lista = new RenderText(20, 620, 20, "Spawns creados: ");
		
		createsObjs = new ListOfButton(90, 690, 0, nullptr, nullptr, elems, finalHabs);
		
	}

	void crearSpawn()
	{
        if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1)
        {
            unsigned int idvamp = std::stoi(inputTexts[0]->inputTexts);
            int filaselec = std::stoi(inputTexts[1]->inputTexts);
            int turno = std::stoi(inputTexts[2]->inputTexts);
            if (idvamp < App::vampiros.size() && filaselec < App::MaxFilas)
            {
                App::spawninglist.push_back(*new VampiroEnEspera(App::vampiros[idvamp], filaselec, turno));
                createsObjs->addButton(nullptr, nullptr, 0, 0, elems);
            }
            inputTexts[0]->inputTexts = " "; inputTexts[0]->changeText();
            inputTexts[1]->inputTexts = " "; inputTexts[1]->changeText();
            inputTexts[2]->inputTexts = " "; inputTexts[2]->changeText();
            actual = 0;
        }
    }

	void createObj(double dt)
	{
		/*std::cout << "click" << std::endl;
		if (inputTexts[0]->inputTexts.size() > 1 && inputTexts[1]->inputTexts.size() > 1 && habs.size() > 0)
		{
			App::vampiros.push_back(*new Vampiro(habs[0], std::stoi(inputTexts[0]->inputTexts), std::stoi(inputTexts[1]->inputTexts)));
			createsObjs->addButton(nullptr, nullptr, 2, elems);
		}
		inputTexts[0]->inputTexts = " ";
		inputTexts[1]->inputTexts = " ";
		habs.resize(0);
		finalButtonHabs->clear();/**/
	}
	void borrar()
	{
		std::ofstream myfile;
		myfile.open("../src/saves/spawnlist.txt");
		myfile.close();
	}

	void cargar()
	{
		std::ifstream myfile;
		myfile.open("../src/saves/spawnlist.txt");
		std::string n;
		myfile >> n;
		if (n != "")
		{
			for (unsigned int i = 0; i < (unsigned int)std::stoi(n); i++)
			{
				Vampiro f = *new Vampiro();
				f.Cargar(myfile);
				int af, t;
				myfile >> af;
				myfile >> t;
				VampiroEnEspera e(f, af, t);
				App::spawninglist.push_back(e);
				createsObjs->addButton(nullptr, nullptr, 2, 2, elems);
			}
		}
		myfile.close();
	}

	void goback(double dt)
	{
		std::ofstream myfile;
		myfile.open("../src/saves/spawnlist.txt");
		myfile << App::spawninglist.size() << std::endl;
		for (unsigned int i = 0; i < App::spawninglist.size(); i++)
		{
			App::spawninglist[i].vampiro.Guardar(myfile); 
			myfile << App::spawninglist[i].fila << " "; 
			myfile << App::spawninglist[i].turno << " ";
			myfile << std::endl;
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
