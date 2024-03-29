#pragma once
#include <vector>
#include <iostream>

#include "Flor.h"
#include "Vampiro.h"
#include "Nivel.h"
#include "Types.h"

class Juego
{
private:

	vector<Flor> _flores;
	vector<Vampiro> _vampiros;
	vector<Nivel> _niveles;
	int _nivelActual;
	
	bool nivelVacio(Nivel n);
	void quitarRepetidosFlores(vector<Flor>& flores);
	bool mismasHabilidadesFlor(Flor f1,Flor f2);
	bool habilidadPerteneceAFlor(int h, Flor f2);
	void quitarRepetidosVampiros(vector<Vampiro>& vamp);
	bool vampirosIguales(Vampiro v1, Vampiro v2);
	bool igualesVampirosEnEspera(VampiroEnEspera v1, VampiroEnEspera v2);
	vector<int> darNivelesGanados();
	void reducirVidaALaMitad(VampiroEnJuego& vampiro);
	void chitearNivel(Nivel& nivelTrucado);
	bool estadoFuturo(Nivel& ni, Nivel& nf);

public:

	Juego();
	Juego(vector<Flor>& flores, vector<Vampiro>& vamps);
	int nivelActual();
	void pasarNivel();
	vector<Flor>& floresJ();
	vector<Vampiro>& vampirosJ();
	vector<Nivel>& nivelesJ();
	void agregarNivel(Nivel& n, int i);
	void jugarNivel(Nivel& n, int i);
	vector<Nivel> estosSaleFacil();
	void altoCheat(int n);
	bool muyDeExactas();

	void Mostrar(ostream& os);
	void Guardar(ostream& os);
	void Cargar(istream& is);
};
