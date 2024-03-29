#pragma once
#include <tuple>
#include <vector>
#include <iostream>
#include <string>

#include "Flor.h"
#include "Vampiro.h"

using namespace std;

struct FlorEnJuego
{
	FlorEnJuego(){};
	FlorEnJuego(Flor f, Posicion p, Vida v)
	{
		flor = f;
		pos = p;
		vida = v;
	}

	Flor flor;
	Posicion pos;
	Vida vida;
};

struct VampiroEnJuego
{
	VampiroEnJuego(Vampiro v, Posicion p, Vida vd)
	{
		vampiro = v;
		pos = p;
		vida = vd;
	}
	Vampiro vampiro;
	Posicion pos;
	Vida vida;
};

struct VampiroEnEspera
{
	Vampiro vampiro;
	int fila;
	int turno;

	VampiroEnEspera(Vampiro v, int f, int t)
	{
		vampiro = v;
		fila = f;
		turno = t;
	}

};

class Nivel
{
private:

	int _ancho;
	int _alto;
	int _turno;
	int _soles;

	vector<FlorEnJuego> _flores;
	vector<VampiroEnJuego> _vampiros;
	vector<VampiroEnEspera> _spawning;

	bool valoresDeEntradaEnRango(int ancho, int alto, int soles, int spawnSize);
	vector<VampiroEnEspera> ordenarSpawning(vector<VampiroEnEspera> spawning);
	bool tieneTurnoMinimo(VampiroEnEspera v1, vector<VampiroEnEspera> spawning);
	vector<VampiroEnEspera> eliminarSpawning(vector<VampiroEnEspera> lista, VampiroEnEspera vampiro);
	bool igualesVampiros(VampiroEnEspera v1, VampiroEnEspera v2);
	int vampirosEnCasa(vector<VampiroEnJuego> vampiros);
	int cantidadFloresConHabilidad(Habilidad habilidad);
	FlorEnJuego daniarFlor(FlorEnJuego flor, vector<VampiroEnJuego> vampiros);
	bool florMuerta(FlorEnJuego flor, vector<VampiroEnJuego> vampiros);
	bool florExploto(FlorEnJuego flor, vector<VampiroEnJuego> vampiros);
	bool tieneHabilidad(FlorEnJuego florEnJuego, Habilidad habilidad);
	bool vampiroEnMismaPosicion(FlorEnJuego florEnJuego, vector<VampiroEnJuego> vampiros);
	bool vampiroMuerto(VampiroEnJuego vampiro, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	VampiroEnJuego daniarVampiro(VampiroEnJuego vampiroEnJuego, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	bool enMira(FlorEnJuego flor, VampiroEnJuego vampiro);
	bool intercepta(FlorEnJuego flor, VampiroEnJuego vampiro, vector<VampiroEnJuego> vampiros);
	vector<VampiroEnJuego> nuevosVampiros();
	bool mismaPosicion(Posicion p1, Posicion p2);
	bool florAtaca (FlorEnJuego f);
	vector<VampiroEnJuego> moverVampiros(vector<VampiroEnJuego> vampiros);
	VampiroEnJuego mover(VampiroEnJuego vampiro);
	Posicion intentarAvanzar(VampiroEnJuego vampiro);
	Posicion intentarRetroceder(Posicion posicion, int ancho);
	Posicion intentarDesvio(VampiroEnJuego vampiro);
	bool florExplotada(Posicion posicion, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	bool florSobreviviente(Posicion posicion, vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	vector<VampiroEnJuego> concatenarVampiros(vector<VampiroEnJuego> v1, vector<VampiroEnJuego> v2);
	vector<VampiroEnEspera> proximosVampiros(vector<VampiroEnEspera> spawning, int turno);
	vector<FlorEnJuego> floresDaniadasYSobrevivientes(vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	vector<VampiroEnJuego> vampirosDaniadosYSobrevivientes(vector<FlorEnJuego> flores, vector<VampiroEnJuego> vampiros);
	
public:
	
	Nivel();
	Nivel(int ancho, int alto, int soles, vector<VampiroEnEspera>& spawninglist);
	int anchoN();
	int altoN();
	int turnoN();
	int solesN();
	vector<FlorEnJuego>& floresN();
	vector<VampiroEnJuego>& vampirosN();
	vector<VampiroEnEspera>& spawningN();
	void agregarFlor(Flor f, Posicion p);
	void pasarTurno();
	bool terminado();
	bool obsesivoCompulsivo();
	void comprarSoles(int n);
	void Mostrar(ostream& os);
	void Guardar(ostream& os);
	void Cargar(istream& is);

};
