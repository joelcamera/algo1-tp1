#pragma once
#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif __linux
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#endif

#include "CurrentGame.h"
#include "App.h"
#include <vector>
#include "ActionPacked.h"
#include "Assets.hpp"

enum KEY_STATE { DOWN, UP };
enum INPUT_EVENT { ON_RELEASE, ON_PRESS, WHILE_PRESSING };

static bool isANumber(char a[])
{
	return *a == '0' || *a == '1' || *a == '2' || *a == '3' || *a == '4' || *a == '5' || *a == '6' || *a == '7' || *a == '8' || *a == '9';
}


class MouseInputData
{

public:
	ActionPacked theActions;

	//InputData::Function function;
	std::vector<int> function;
	std::vector<KEY_STATE> lastState;
	std::vector<INPUT_EVENT> eventAsk;
	std::vector<Uint8> key;

	MouseInputData()
	{}

	MouseInputData(ActionPacked& actions)
	{
		theActions = actions;
	}

	void setActions(ActionPacked actions)
	{
		theActions = actions;
	}

	void AddResponse(Uint8 aKey, INPUT_EVENT inputEvent, int action)
	{
		lastState.push_back(KEY_STATE::UP);
		function.push_back(action);
		eventAsk.push_back(inputEvent);
		key.push_back(aKey);
	}
};

static bool shouldCall(Uint8 mouse_button, INPUT_EVENT anEvent, KEY_STATE& lastState)
{
	SDL_PumpEvents();
	if (SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(mouse_button))
	{
		KEY_STATE lastStateT = lastState;
		lastState = KEY_STATE::DOWN;
		if (anEvent == INPUT_EVENT::ON_PRESS && lastStateT || anEvent == INPUT_EVENT::WHILE_PRESSING)
		{
			//std::cout << "true" << std::endl;
			return true;
		}
	}
	else
	{
		if (lastState != KEY_STATE::UP)
		{
			lastState = KEY_STATE::UP;
			return (anEvent == INPUT_EVENT::ON_RELEASE);
		}
	}
	return false;
}

struct Animation
{
	int textureID = -1;
	SDL_Rect dst;
	int frame = 0;
	double lastTime = 0;
	SDL_Rect src;
	
	int _sw, _sh;
	SDL_RendererFlip flip;

	int framesAmount;

	Animation()
	{}

	Animation(int x, int y, int w, int h, int sw, int sh, int f, int ffs)
	{
		_sw = sw; _sh = sh;
		dst = { x, y, w, h };
		textureID = f;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
		framesAmount = ffs;
	}

	void update(double dt)
	{
		lastTime += dt;
		if (lastTime > 0.1)
		{
			lastTime = 0;
			frame = (frame + 1) % framesAmount;
		}
	}

	void reBuild(int x, int y, int w, int h, int sw, int sh, int f, int ffs)
	{
		_sw = sw; _sh = sh;
		dst = { x, y, w, h };
		textureID = f;
		flip = SDL_RendererFlip::SDL_FLIP_NONE;
		framesAmount = ffs;
	}

	void Render()
	{
		src = { _sw*frame, 0, _sw, _sh };
		SDL_RenderCopyEx(App::gRenderer, Assets::getTexture(textureID), &src, &dst, 0, nullptr, flip);
	}

};

struct Button
{
	int textureID;
	SDL_Rect src;
	SDL_Rect dst;

	ActionPacked actions;
	MouseInputData input;

	FunctionPtr<double>* clickingF;
	FunctionPtr<double>* wclickingF;
	FunctionPtr<double>* releasingF;

	int ID;

	bool taken = false;

	int _x, _y, _w, _h;

	void clickF(double dt)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (dst.x < x && dst.x + dst.w > x && dst.y < y && dst.y + dst.h > y && clickingF != nullptr)
		{
			clickingF->Invoke(ID);
			taken = true;
		}
	}

	void wclickF(double dt)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (taken && wclickingF != nullptr)
		{
			wclickingF->Invoke(ID);
		}
	}

	void releaseF(double dt)
	{
		if (taken && releasingF != nullptr)
		{
			taken = false;
			releasingF->Invoke(ID);
		}
	}


	Button(int x, int y, int w, int h, int ww, int hh, int id, int textureId, FunctionPtr<double>* click, FunctionPtr<double>* whileclick, FunctionPtr<double>* release)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		ID = id;
		textureID = textureId;

		src = { 0, 0, _w, _h };
		dst = { _x, _y, ww, hh };

		auto f = ::CurrentGame->getFunctionPtr<double>();
		f->Bind<Button, &Button::clickF>(this);

		auto f2 = ::CurrentGame->getFunctionPtr<double>();
		f2->Bind<Button, &Button::wclickF>(this);

		auto f3 = ::CurrentGame->getFunctionPtr<double>();
		f3->Bind<Button, &Button::releaseF>(this);


		clickingF = click;
		wclickingF = whileclick;
		releasingF = release;

		actions = *new ActionPacked(3, 3);
		actions.registerAction(0, 0, 1, f);
		actions.registerAction(1, 1, 2, f2);
		actions.registerAction(2, 1, 2, f2);
		actions.registerAction(1, 2, 0, f3);
		actions.registerAction(2, 2, 0, f3);

		input.AddResponse(SDL_BUTTON_LEFT, INPUT_EVENT::ON_PRESS, 0);
		input.AddResponse(SDL_BUTTON_LEFT, INPUT_EVENT::WHILE_PRESSING, 1);
		input.AddResponse(SDL_BUTTON_LEFT, INPUT_EVENT::ON_RELEASE, 2);
		input.theActions = actions;
	}

	void Render()
	{
		SDL_RenderCopyEx(App::gRenderer, Assets::getTexture(textureID), &src, &dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
};


struct ListOfButton
{
	std::vector< Button* > bs;
	int x, y;
	ListOfButton(int xx, int yy, int size, FunctionPtr<double>* drag, FunctionPtr<double>* drop, std::vector<MouseInputData>& elems, std::vector<int>& texturesIDs)
	{
		x = xx;
		y = yy;
		bs.resize(size);

		for (int i = 0; i < size; i++)
		{
			bs[i] = new Button(x*(i + 1) + 50 * i, y, 50, 50, 50, 50, i, texturesIDs[i], drag, drag, drop);

			elems.push_back(bs[i]->input);
		}
	}

	void addButton(FunctionPtr<double>* drag, FunctionPtr<double>* drop, int id, int textid, std::vector<MouseInputData>& elems)
	{
		bs.push_back(new Button(x + 55 * (bs.size() - 1), y, 50, 50, 50, 50, id, textid, drag, drag, drop));
		//elems.push_back(bs[bs.size() - 1]->input);
	}

	void clear()
	{
		bs.resize(0);
	}

	void Render()
	{
		for (unsigned int i = 0; i < bs.size(); i++) bs[i]->Render();
	}

};

struct Sprite
{
	int _x, _y, _w, _h, _textureID, _sh, _sw;
	Sprite()
	{
		_x = 0; _y = 0; _w = 0; _h = 0; _sh = 0; _sw = 0; _textureID = 0;
	}
	
	Sprite(int x, int y, int w, int h, int sw, int sh, int textureID)
	{
		_x = x; _y = y; _w = w; _h = h; _textureID = textureID; _sh = sh; _sw = sw;
	}
	
	void reBuild(int x, int y, int w, int h, int sw, int sh, int textureID)
	{
		_x = x; _y = y; _w = w; _h = h; _textureID = textureID; _sh = sh; _sw = sw;
	}

	void Render()
	{
		SDL_Rect src = {0,0,_sw, _sw};
		SDL_Rect dst = {_x, _y, _w, _h};
		SDL_RenderCopyEx(App::gRenderer, Assets::getTexture(_textureID), &src, &dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

};

struct RenderText
{
	TTF_Font* gFont;
	SDL_Color textColor;

	std::string _quote;
	SDL_Texture* _quoteTexture;
	SDL_Surface* _quoteSurface;

	int _x, _y;
	int _size;
	RenderText()
	{
		_x = 0; _y = 0; _size = 0; _quote = "";
		gFont = TTF_OpenFont("../src/assets/font.ttf", _size);
	}


	RenderText(int x, int y, int s, std::string text)
	{
		_x = x;
		_y = y;
		_size = s;
		textColor = { 0xFF, 0xFF, 0x00, 0xFF };
		gFont = TTF_OpenFont("../src/assets/font.ttf", _size);
		_quote = text;
		_quoteSurface = TTF_RenderText_Solid(gFont, _quote.c_str(), textColor);
		_quoteTexture = SDL_CreateTextureFromSurface(App::gRenderer, _quoteSurface);
	}

	void reBuild(int x, int y, int s, std::string text)
	{
		_x = x;
		_y = y;
		_size = s;
		textColor = { 0xFF, 0x00, 0x00, 0xFF };
		gFont = TTF_OpenFont("../src/assets/font.ttf", _size);
		_quote = text;
		_quoteSurface = TTF_RenderText_Solid(gFont, _quote.c_str(), textColor);
		_quoteTexture = SDL_CreateTextureFromSurface(App::gRenderer, _quoteSurface);
	}

	void Render()
	{
		SDL_Rect src = { 0, 0, _quoteSurface->w, _quoteSurface->h };
		SDL_Rect dst = { _x, _y, _quoteSurface->w, _quoteSurface->h };
		SDL_RenderCopyEx(App::gRenderer, _quoteTexture, &src, &dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}
};

struct InputText
{
	SDL_Surface* textSurface;
	TTF_Font* gFont;
	SDL_Color textColor;
	std::string inputTexts;
	SDL_Texture* textTexture;
	
	
	std::string _quote;
	SDL_Texture* _quoteTexture;
	SDL_Surface* _quoteSurface;

	int _x, _y;

	InputText(int x, int y, std::string quote)
	{
		_x = x;
		_y = y;
		textColor = { 0xFF, 0x00, 0x00, 0xFF };
		gFont = TTF_OpenFont("../src/assets/font.ttf", 40);
		inputTexts = " ";
		_quote = quote;

		_quoteSurface = TTF_RenderText_Solid(gFont, _quote.c_str(), textColor);
		_quoteTexture = SDL_CreateTextureFromSurface(App::gRenderer, _quoteSurface);
		changeText();
	}

	void changeText()
	{
		

		//Render first string
		textSurface = TTF_RenderText_Solid(gFont, inputTexts.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(App::gRenderer, textSurface);
	}

	void Render()
	{
		SDL_Rect src = { 0, 0, _quoteSurface->w, _quoteSurface->h };
		SDL_Rect dst = { _x, _y, _quoteSurface->w, _quoteSurface->h };
		SDL_RenderCopyEx(App::gRenderer, _quoteTexture, &src, &dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);

		src = { 0, 0, _quoteSurface->w - 20, textSurface->h };
		dst = { _x + _quoteSurface->w - 20, _y, textSurface->w, textSurface->h };
		SDL_RenderCopyEx(App::gRenderer, textTexture, &src, &dst, 0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);/**/
	}
};