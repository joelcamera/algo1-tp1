#pragma once
#include <vector>
#include "App.h"


class Assets
{
public:
	static std::vector<SDL_Texture*> textures;

	static int textureTest;
	static int flower;
	static int generar;
	static int atacar;
	static int explotar;
	static int plant;
	static int flor;
	static int create;
	static int batman;
	static int juegoplay;
	static int spawninglist;

	static int nextS;
	static int prevS;
	static int gone;
	static int gwto;
	static int scot;
	static int explotara;
	static int generara;
	static int atacara;
	static int desviado;
	static int avanzar;
	static int background;

	static int ocd;
	static int keepcalm;
    
    static int nextlvl;

	static int f1, f2, f3, f4, f5, f6, f7, v1, v2, b1, b2, b3, a1, a2, a3, a4, a5, a6, a7;

	static int saveb;

	static void load()
	{
		textureTest = Assets::registerTexture("../src/assets/generar.png");
		flower = Assets::registerTexture("../src/assets/flower.png");
		generar = Assets::registerTexture("../src/assets/generar.png");
		atacar = Assets::registerTexture("../src/assets/atacar.png");
		explotar = Assets::registerTexture("../src/assets/explotar.png");
		plant = Assets::registerTexture("../src/assets/vamp.png");
		flor = Assets::registerTexture("../src/assets/flor.png");
		create = Assets::registerTexture("../src/assets/create.png");
		batman = Assets::registerTexture("../src/assets/batman.png");
		juegoplay = Assets::registerTexture("../src/assets/juegoplay.png");
		spawninglist = Assets::registerTexture("../src/assets/spawninglist.png");
		
		nextS = Assets::registerTexture("../src/assets/next.png");
		prevS = Assets::registerTexture("../src/assets/prev.png");
		gone = Assets::registerTexture("../src/assets/grassone.png");
		gwto = Assets::registerTexture("../src/assets/grasstwo.png");		
		scot = Assets::registerTexture("../src/assets/scot.png");
		explotara = Assets::registerTexture("../src/assets/a3.png");
		generara = Assets::registerTexture("../src/assets/a1.png");
		atacara = Assets::registerTexture("../src/assets/a2.png");
		desviado = Assets::registerTexture("../src/assets/desviado.png");
		avanzar = Assets::registerTexture("../src/assets/avanzar.png");
		background = Assets::registerTexture("../src/assets/background.png");
        nextlvl = Assets::registerTexture("../src/assets/nextlvl.png");

		f1 = Assets::registerTexture("../src/assets/1.png");
		f2 = Assets::registerTexture("../src/assets/2.png");
		f3 = Assets::registerTexture("../src/assets/3.png");
		f4 = Assets::registerTexture("../src/assets/4.png");
		f5 = Assets::registerTexture("../src/assets/5.png");
		f6 = Assets::registerTexture("../src/assets/6.png");
		f7 = Assets::registerTexture("../src/assets/7.png");

		v1 = Assets::registerTexture("../src/assets/v1.png");
		v2 = Assets::registerTexture("../src/assets/v2.png");

		b1 = Assets::registerTexture("../src/assets/b1.bmp");
		b2 = Assets::registerTexture("../src/assets/b2.bmp");
		b3 = Assets::registerTexture("../src/assets/b3.bmp");

		a1 = Assets::registerTexture("../src/assets/a1.png");
		a2 = Assets::registerTexture("../src/assets/a2.png");
		a3 = Assets::registerTexture("../src/assets/a3.png");
		a4 = Assets::registerTexture("../src/assets/a4.png");
		a5 = Assets::registerTexture("../src/assets/a5.png");
		a6 = Assets::registerTexture("../src/assets/a6.png");
		a7 = Assets::registerTexture("../src/assets/a7.png");
		keepcalm = Assets::registerTexture("../src/assets/keepcalm.jpg");

		ocd = Assets::registerTexture("../src/assets/ocd.png");

		saveb = Assets::registerTexture("../src/assets/save.png");

	}

	static SDL_Texture* getTexture(int n)
	{
		return textures[n];
	}

	static void clear()
	{
		textures.clear();
	}

	static int registerTexture(std::string path)
	{
		//The final texture
		SDL_Texture* newTexture = NULL;
		
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0x00, 0x00));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(App::gRenderer, loadedSurface);
			if (newTexture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
		textures.push_back(newTexture);

		return textures.size() - 1;
	}

};
