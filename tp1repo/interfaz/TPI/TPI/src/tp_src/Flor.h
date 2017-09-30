#pragma once
#include "Types.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Flor
{
private:

	Vida _vida;
	vector<Habilidad> _habilidades;
	int _cuantoPega;
	void quitarRepetidosHabilidad(vector<Habilidad>& hs);
	bool atacarPertenece(vector<Habilidad> hs);

public:
	Flor();
	Flor(Vida v, int cP, vector<Habilidad> hs);
	Vida vidaF();
	int cuantoPegaF();
	vector<Habilidad>& habilidadesF();

	void Mostrar(ostream& os) const;
	void Guardar(ostream& os) const;
	void Cargar(istream& is);

};
