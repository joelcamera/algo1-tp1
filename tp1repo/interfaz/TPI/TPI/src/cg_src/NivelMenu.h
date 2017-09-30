#pragma once
#include "CurrentGame.h"
#include "App.h"
#include <vector>
#include "ActionPacked.h"
#include "Types.hpp"
#include <string>

#include <iostream>
#include <fstream>

#include "../tp_src/Juego.h"

class NivelMenu : BaseScreen
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

	
	std::vector<std::string> inputTexts;
	int actual = 0;

	TTF_Font *gFont = NULL;
	SDL_Surface* textSurface;
	SDL_Color textColor;
	SDL_Texture* textTexture;

	std::vector<MouseInputData> elems;
	//Screen OBJS

	ListOfButton* buttons;
	

	std::vector<int> finalHabs;
	ListOfButton* finalButtonHabs;

	//Grid values
	int gridx = 255, gridy = 130, cuadw = 80, cuadh = 125, grows = 8, gcols = 12;


	//Para mostrar flores del nivel
	std::vector<Animation> flors;
	std::vector<RenderText> vidaFlors;
	std::vector<Animation> vamps;
	std::vector<RenderText> vidaVamps;

	Animation avanzar;
	int tiempoDeAvanzar = 500;
	int tiempoPorAvanzar = 0;

	//Turns
	Button* nextTurn;
	Button* prevTurn;

	Button* nextLvl;
	Button* prevLvl;
	Button* cheat;
	Button* osdB;
	Button* save;

	RenderText* agregarF;

	Juego juego;

	Sprite background;

	int elNivelJugando;

	void upVampiros()
	{
		//Actualizo vampiros
		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].vampirosN().size(); i++)
		{
			if (tiempoPorAvanzar > 0)
			{
				vamps[i].reBuild(juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.x * cuadw + gridx, juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.y * cuadh + gridy - 10, 71, 82, 500, 575, 8, 8);
			}
			else
			{
				if (juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].vampiro.claseV() == ClaseVampiro::Caminante)
				{

					vamps[i].reBuild(juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.x * cuadw + gridx, juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.y * cuadh + gridy - 10, 71, 82, 500, 575, Assets::scot, 8);

				}
				else
				{

					vamps[i].reBuild(juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.x * cuadw + gridx - 20, juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.y * cuadh + gridy - 40, 125, 108, 500, 432, Assets::desviado, 6);

				}
			}
			vidaVamps[i].reBuild(juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.x * cuadw + gridx + 35, juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].pos.y * cuadh + gridy + 30, 20, std::to_string(juego.nivelesJ()[juego.nivelActual()].vampirosN()[i].vida));
		}
	}

	NivelMenu(int aLvl)
	{
		::CurrentGame = this;
		TTF_Init();
		if (App::niveles.size() > 0)
		{
			SDL_SetWindowSize(App::gWindow, 1400, 800);
			juego = *new Juego(App::flores, App::vampiros);

			for (unsigned int i = 0; i < App::niveles.size(); i++)
			{
				juego.agregarNivel(App::niveles[i], i);
			}

			//Create the habilities
			auto drag = getFunctionPtr<double>();
			drag->Bind<NivelMenu, &NivelMenu::Drag>(this);

			auto drop = getFunctionPtr<double>();
			drop->Bind<NivelMenu, &NivelMenu::Drop>(this);

			//Flores para agregar
			std::vector<int> ls;
			ls.resize(App::flores.size(), 0);

			for (unsigned int i = 0; i < App::flores.size(); i++)
			{
				if (tiene(App::flores[i].habilidadesF(), 0) && App::flores[i].habilidadesF().size() == 1)
				{
					ls[i] = Assets::f1;
				}
				if (tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 1)
				{
					ls[i] = Assets::f2;
				}
				if (tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 1)
				{
					ls[i] = Assets::f3;
				}
				if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 1) && App::flores[i].habilidadesF().size() == 2)
				{
					ls[i] = Assets::f4;
				}
				if (tiene(App::flores[i].habilidadesF(), 0) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
				{
					ls[i] = Assets::f5;
				}
				if (tiene(App::flores[i].habilidadesF(), 1) && tiene(App::flores[i].habilidadesF(), 2) && App::flores[i].habilidadesF().size() == 2)
				{
					ls[i] = Assets::f6;
				}
				if (App::flores[i].habilidadesF().size() == 3)
				{
					ls[i] = Assets::f7;
				}
			}
			
			buttons = new ListOfButton(20, 20, App::flores.size(), drag, drop, elems, ls);
			//Next Turn
			auto n = getFunctionPtr<double>();
			n->Bind<NivelMenu, &NivelMenu::goNextTurn>(this);

			auto p = getFunctionPtr<double>();
			p->Bind<NivelMenu, &NivelMenu::goPrevTurn>(this);

			auto cc = getFunctionPtr<double>();
			cc->Bind<NivelMenu, &NivelMenu::cheatAlto>(this);

			auto osdF = getFunctionPtr<double>();
			osdF->Bind<NivelMenu, &NivelMenu::osd>(this);

			auto saveF = getFunctionPtr<double>();
			saveF->Bind<NivelMenu, &NivelMenu::savec>(this);

			nextTurn = new Button(1000, 100, 958, 553, 958*0.2, 553*0.2, 0, Assets::nextS, n, nullptr, nullptr);
			elems.push_back(nextTurn->input);

			prevTurn = new Button(1200, 100, 600, 275, 600*0.25, 275*0.25, 0, Assets::nextlvl, p, nullptr, nullptr);
			elems.push_back(prevTurn->input);

			cheat = new Button(1200, 500, 183, 275, 183, 275, 0, Assets::keepcalm, cc, nullptr, nullptr);
			elems.push_back(cheat->input);

			osdB = new Button(1210, 400, 701, 354, (int)(701 * 0.2), (int)(354 * 0.2), 0, Assets::ocd, osdF, nullptr, nullptr);
			elems.push_back(osdB->input);

			save = new Button(1210, 300, 50, 50, 50, 50, 0, Assets::saveb, saveF, nullptr, nullptr);
			elems.push_back(save->input);

			background = *new Sprite(0, 0, 1400, 800, 1400, 600, Assets::background);

			agregarF = new RenderText(20, 100, 20, "Arrastrar al mapa para agregar una Flor al nivel");
		}
		elNivelJugando = aLvl;
		play();
	}

	void savec(double dt)
	{
		std::ofstream myfile;
		myfile.open("../src/saves/juego.txt");
		juego.Guardar(myfile);
		myfile.close();
	}

	void osd(double dt)
	{
		std::string s = "Nah";
		if (juego.nivelesJ()[juego.nivelActual()].obsesivoCompulsivo()) s = "Oh si.";

		std::cout << "Obsesivo compulsivo? : " << s << std::endl;
	}

	void cheatAlto(double dt)
	{
		juego.altoCheat(juego.nivelActual());
	}

	void reBuild(int aLvl)
	{
		elNivelJugando = aLvl;
		play();
	}

	void play()
	{
		if (App::niveles.size() > 0)
		{
			grows = App::niveles[juego.nivelActual()].altoN();
			gcols = App::niveles[juego.nivelActual()].anchoN();

			vamps.clear();
			vidaVamps.clear();
			flors.clear();
			vidaFlors.clear();

			flors.resize(grows*gcols * 2);
			vidaFlors.resize(grows*gcols * 2);
			vamps.resize(grows*gcols * 2);
			vidaVamps.resize(grows*gcols * 2);

			upVampiros();
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

	void goNextTurn(double dt)
	{
		juego.nivelesJ()[juego.nivelActual()].pasarTurno();
		upVampiros();
	}

	void goPrevTurn(double dt)
	{
		if ((unsigned int)juego.nivelActual() < juego.nivelesJ().size() - 1 && juego.nivelesJ()[juego.nivelActual()].terminado())
		{
			juego.pasarNivel();
			reBuild(juego.nivelActual());
		}
	}

	void Drag(double dt)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		buttons->bs[(int)dt]->dst = { x, y, 50, 50 };
		//std::cout << "Drag" << std::endl;
	}

	void Drop(double dt)
	{
		//If the button is from a list somewhere
		buttons->bs[(int)dt]->dst = { ((int)dt + 1) * buttons->x + (int)dt * 50, buttons->y, 50, 50 };

		//If I want to drop it in the grid
		int x, y;
		SDL_GetMouseState(&x, &y);
		int xx = (x - gridx) / cuadw;
		int yy = (y - gridy) / cuadh;
		//buttons->bs[(int)dt]->dst = { xx * 50 + gridx, yy * 50 + gridy, cuadw, cuadh };
		juego.nivelesJ()[juego.nivelActual()].agregarFlor(App::flores[(int)dt], Posicion(xx, yy));
		
		//Actualizo las flores
		for (unsigned int i = 0; i < juego.nivelesJ()[juego.nivelActual()].floresN().size(); i++)
		{
			std::vector<Habilidad>& hs = juego.nivelesJ()[juego.nivelActual()].floresN()[i].flor.habilidadesF();
			if (tiene(hs, 0) && hs.size() == 1)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 10, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 10, 66, 100, 51, 77, Assets::a1, 6);
				//createsObjs->addButton(nullptr, nullptr, 2, Assets::f1, elems);
			}
			if (tiene(hs, 1) && hs.size() == 1)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 30, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 10, 120, 90, 120, 90, Assets::a2, 8);
			}
			if (tiene(hs, 2) && hs.size() == 1)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 30, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 25, 100, 109, 500, 547, Assets::a3, 6);
			}
			if (tiene(hs, 0) && tiene(hs, 1) && hs.size() == 2)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 5, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 10, (int)(500 * 0.2), (int)(408 * 0.2), 500, 408, Assets::a4, 8);
			}
			if (tiene(hs, 0) && tiene(hs, 2) && hs.size() == 2)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 5, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 40, (int)(500 * 0.2), (int)(608 * 0.2), 500, 608, Assets::a5, 16);
			}
			if (tiene(hs, 1) && tiene(hs, 2) && hs.size() == 2)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 5, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 10, 98, 91, 98, 91, Assets::a6, 8);
			}
			if (hs.size() == 3)
			{
				flors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx - 5, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy - 10, (int)(73 * 1.2), (int)(73 * 1.2), 73, 73, Assets::a7, 9);
			}
			vidaFlors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy, 30, std::to_string(juego.nivelesJ()[juego.nivelActual()].floresN()[i].vida));
			vidaFlors[i].reBuild(juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.x * cuadw + gridx, juego.nivelesJ()[juego.nivelActual()].floresN()[i].pos.y * cuadh + gridy, 30, std::to_string(juego.nivelesJ()[juego.nivelActual()].floresN()[i].vida));

		}
	}

	
};
