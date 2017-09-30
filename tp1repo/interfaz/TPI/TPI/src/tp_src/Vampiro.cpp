#include "Vampiro.h"
#include <cassert>

using namespace std;

Vampiro::Vampiro()
{
}

Vampiro::Vampiro(ClaseVampiro cv, Vida v, int cP)
{
	// si no esta en rango, pone el valor mas cercano dentro del rango 
	// (v<0 --> v = 1 || v>100 --> v == 100) y (cP<=0 --> 1)
	if(!vidaEnRango(v)) ponerVidaEnRango(v);
	if(!cuantoPegaEnRango(cP)) ponerCuantoPegaEnRango(cP);
	this->_vida = v;
	this->_cuantoPega = cP;
	this->_clase = cv;
}

Vida Vampiro::vidaV()
{
	return this->_vida;
}

ClaseVampiro Vampiro::claseV()
{
	return this->_clase;
}

int Vampiro::cuantoPegaV()
{
	return this->_cuantoPega;
}

void Vampiro::Mostrar(ostream& os)
{
	os << "INFO. DEL VAMPIRO:" << endl;
	os << "Vida del Vampiro: " << this->_vida << endl;
	os << "Cuanto Pega el Vampiro: " << this->_cuantoPega << endl;
	os << "Clase del Vampiro: ";

	if(this->_clase == Caminante){
		os << "Caminante" << endl;
	} else {
		os << "Desviado" << endl;
	}
	os << endl;
}

void Vampiro::Guardar(ostream& os)
{
	os << "{ V ";
	if(this->_clase == 0){
		os << "Caminante ";
	} else {
		os << "Desviado ";
	}

	string strVida = to_string(this->_vida);
	os << strVida << " ";
	string strCuantoPega = to_string(this->_cuantoPega);
	os << strCuantoPega << " }";
}

void Vampiro::Cargar(istream& is)
{
	string buscaValores;
	int num = 0;

	getline(is,buscaValores,'V');
	getline(is,buscaValores,' ');
	getline(is,buscaValores,' '); // aca veo la clase del vampiro

	if(buscaValores == "Desviado"){
		this->_clase = Desviado;
	} else {
		this->_clase = Caminante;
	}

	getline(is,buscaValores,' '); // aca veo la vida
	this->_vida = atoi(buscaValores.c_str());
	if(!vidaEnRango(this->_vida)) ponerVidaEnRango(this->_vida);

	getline(is,buscaValores,' '); // aca veo cuanto pega

	this->_cuantoPega = atoi(buscaValores.c_str());
	if(!cuantoPegaEnRango(this->_cuantoPega)) ponerCuantoPegaEnRango(this->_cuantoPega);

	getline(is,buscaValores,' '); // "}" para otros cargar pongo esta linea
}

bool Vampiro::vidaEnRango(int v){
	return (v >= 0 && v <= 100);
}

void Vampiro::ponerVidaEnRango(int& v){
	if(v < 0){
		v = 0;
	} else {
		v = 100;
	}
}

bool Vampiro::cuantoPegaEnRango(int cP){
	return (cP > 0);
}

void Vampiro::ponerCuantoPegaEnRango(int& cP){
	cP = 1;
}
