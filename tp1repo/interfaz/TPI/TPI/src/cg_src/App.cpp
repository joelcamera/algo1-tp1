#include "App.h"
#include "Assets.hpp"

SDL_Window* App::gWindow = 0;
SDL_Renderer* App::gRenderer = 0;
std::vector<Flor> App::flores;
std::vector<Vampiro> App::vampiros;
std::vector<VampiroEnEspera> App::spawninglist;
std::vector<Nivel> App::niveles;
int App::MaxFilas = 0;
int App::CSoles = 0;
int App::MaxCols = 0;
int App::actualLevel = 0;

int Assets::textureTest = 0;
int Assets::flower = 0;
int Assets::generar = 0;
int Assets::atacar = 0;
int Assets::explotar = 0;
int Assets::plant = 0;
int Assets::flor = 0;
int Assets::create = 0;
int Assets::batman = 0;
int Assets::juegoplay = 0;
int Assets::spawninglist = 0;

int Assets::nextS = 0;
int Assets::prevS = 0;
int Assets::gone = 0;
int Assets::gwto = 0;
int Assets::scot = 0;
int Assets::explotara = 0;
int Assets::generara = 0;
int Assets::atacara = 0;
int Assets::desviado = 0;
int Assets::avanzar = 0;
int Assets::background = 0;

int Assets::f1 = 0;
int Assets::f2 = 0;
int Assets::f3 = 0;
int Assets::f4 = 0;
int Assets::f5= 0;
int Assets::f6 = 0;
int Assets::f7 = 0;

int Assets::a1 = 0;
int Assets::a2 = 0;
int Assets::a3 = 0;
int Assets::a4 = 0;
int Assets::a5 = 0;
int Assets::a6 = 0;
int Assets::a7 = 0;

int Assets::v1 = 0;
int Assets::v2 = 0;

int Assets::b1 = 0;
int Assets::b2 = 0;
int Assets::b3 = 0;

int Assets::nextlvl = 0;

int Assets::keepcalm = 0;

int Assets::ocd = 0;

int Assets::saveb = 0;


void App::load()
{
	Assets::load();
}