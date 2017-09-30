#include "Juego.h"
#include "Vampiro.h"
#include "Nivel.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(){

  cout << " Trabajo practico Flores vs Vampiros" << endl;
  
  vector<Habilidad> hab;
  hab.push_back(Atacar);
  
  vector<Habilidad> hab2;
  hab2.push_back(Atacar);
  hab2.push_back(Generar);
  
  vector<Habilidad> hab3;
  hab3.push_back(Explotar);
  hab3.push_back(Generar);
  
  Flor f(25,0,hab3);
  
  cout << f.vidaF() << ' ' << f.cuantoPegaF() << endl;
  
  Vampiro v(Caminante,50,50);
  
  cout << v.vidaV() << ' ' << v.cuantoPegaV() << endl;
  
  vector<VampiroEnEspera> spawn;
  spawn.push_back(VampiroEnEspera(v,2,2));
  
  Nivel n(5,5,100,spawn);
  
  cout << n.solesN() << endl;
    
  n.agregarFlor(f, Posicion(2,2));
  
  cout << n.solesN() << endl;
  
  n.pasarTurno();
  
  cout << n.solesN() << endl;
  
  cout << n.terminado() << ' ' << n.obsesivoCompulsivo() << endl;
  
  
  vector<Flor> fs;
  fs.push_back(f);
  
  vector<Vampiro> vs;
  vs.push_back(v);
  
  Juego j(fs,vs);
  
  j.agregarNivel(n,0);
  
  cout << j.muyDeExactas() << endl;

  cout << endl;
  
  /*    TESTS DE JUEGO PARA ENTREGAR    */
  cout << "TEST DE JUEGO" << endl << endl;

  vector<Habilidad> habilidad1;  
  habilidad1.push_back(Atacar);
  habilidad1.push_back(Explotar);
  habilidad1.push_back(Generar);
  vector<Habilidad> habilidad2;
  habilidad2.push_back(Atacar);
  habilidad2.push_back(Explotar);
  vector<Habilidad> habilidad3;
  habilidad3.push_back(Generar);

  //el constructor de flor genera la vida y el cuanto pega segun las habilidades
  Flor f1(1,1,habilidad1);
  Flor f2(1,1,habilidad2);
  Flor f3(1,1,habilidad3);

  Vampiro vampiro1(Caminante,10,10);
  Vampiro vampiro2(Caminante,12,12);
  Vampiro vampiro3(Desviado,15,15);

  vector<Flor> floresJuego;
  floresJuego.push_back(f1);
  floresJuego.push_back(f2);
  floresJuego.push_back(f3);

  vector<Flor> floresVacio;

  vector<Vampiro> vampirosJuego;
  vampirosJuego.push_back(vampiro1);
  vampirosJuego.push_back(vampiro2);
  vampirosJuego.push_back(vampiro3);

  vector<Vampiro> vampirosVacio;

  VampiroEnEspera v1 = VampiroEnEspera(vampiro1, 1, 1);
  VampiroEnEspera v2 = VampiroEnEspera(vampiro2, 2, 2);
  VampiroEnEspera v3 = VampiroEnEspera(vampiro3, 3, 3);
  VampiroEnEspera v4 = VampiroEnEspera(vampiro1, 4, 4);
  VampiroEnEspera v5 = VampiroEnEspera(vampiro2, 3, 6);
  VampiroEnEspera v6 = VampiroEnEspera(vampiro3, 4, 2);

  vector<VampiroEnEspera> spawningList1;
  spawningList1.push_back(v1);
  spawningList1.push_back(v2);
  spawningList1.push_back(v3);
  vector<VampiroEnEspera> spawningList2;
  spawningList2.push_back(v4);
  spawningList2.push_back(v5);
  spawningList2.push_back(v6);
  vector<VampiroEnEspera> spawningList3;
  spawningList3.push_back(v1);
  spawningList3.push_back(v4);
  spawningList3.push_back(v6);
  vector<VampiroEnEspera> spawningList4;
  spawningList4.push_back(v2);
  spawningList4.push_back(v5);
  spawningList4.push_back(v3);
  vector<VampiroEnEspera> spawningVacio;
  
  Nivel n1(10,10,50,spawningList1);
  Nivel n2(9,9,13,spawningList2);
  Nivel n3(12,12,24,spawningList3);
  Nivel n4(15,15,47,spawningList4);
  Nivel n5(15,15,0, spawningVacio);

  Juego juegoTest(floresJuego,vampirosJuego);

  //  TESTS AGREGAR NIVEL

  /*
  Test 1:
  Agrego el nivel n1 a juegoTest, la lista de niveles deberia tener un nivel.
  */

  cout << "TEST 1 AGREGAR NIVEL" << endl;
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;
  juegoTest.agregarNivel(n1,0);
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;

  /*
  Salida del primer test:
  TEST 1 AGREGAR NIVEL
  Longitud de la lista de niveles de juego: 0
  Longitud de la lista de niveles de juego: 1
  */
  cout << endl << endl;
  
  /*
  Test 2:
  Agrego el nivel n2 a juegoTest en la posicion 1. El nivel deberia agregarse despues de n1.
  Reviso si el nivel se agrego correctamente viendo el ancho, algo y soles del nivel en
  cada posicion.
  */

  cout << "TEST 2 AGREGAR NIVEL" << endl;
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;
  juegoTest.agregarNivel(n2,1);
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;

  cout << endl << "Veo si los niveles estan en sus posiciones:" << endl << endl;
  if(juegoTest.nivelesJ().at(0).anchoN() == 10 && juegoTest.nivelesJ().at(0).altoN() == 10 &&
    juegoTest.nivelesJ().at(0).solesN() == 50){
    cout << "Nivel n1 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n1 NO esta en la posicion correcta." << endl;
  }

  if(juegoTest.nivelesJ().at(1).anchoN() == 9 && juegoTest.nivelesJ().at(1).altoN() == 9 &&
    juegoTest.nivelesJ().at(1).solesN() == 13){
    cout << "Nivel n2 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n2 NO esta en la posicion correcta." << endl;
  }

  /*
  Salida del segundo test:
  TEST 2 AGREGAR NIVEL
  Longitud de la lista de niveles de juego: 1
  Longitud de la lista de niveles de juego: 2

  Veo si los niveles estan en sus posiciones:

  Nivel n1 en la posicion correcta.
  Nivel n2 en la posicion correcta.
  */
  cout << endl << endl;
  
  /*
  Test 3:
  Agrego el nivel n3 a juegoTest en la posicion 1. El nivel deberia agregarse entre el n1 y n2.
  */

  cout << "TEST 3 AGREGAR NIVEL" << endl;
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;
  juegoTest.agregarNivel(n3,1);
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;

  cout << endl << "Veo si los niveles estan en sus posiciones:" << endl << endl;
  if(juegoTest.nivelesJ().at(0).anchoN() == 10 && juegoTest.nivelesJ().at(0).altoN() == 10 &&
    juegoTest.nivelesJ().at(0).solesN() == 50){
    cout << "Nivel n1 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n1 NO esta en la posicion correcta." << endl;
  }

  if(juegoTest.nivelesJ().at(1).anchoN() == 12 && juegoTest.nivelesJ().at(1).altoN() == 12 &&
    juegoTest.nivelesJ().at(1).solesN() == 24){
    cout << "Nivel n3 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n3 NO esta en la posicion correcta." << endl;
  }  

  if(juegoTest.nivelesJ().at(2).anchoN() == 9 && juegoTest.nivelesJ().at(2).altoN() == 9 &&
    juegoTest.nivelesJ().at(2).solesN() == 13){
    cout << "Nivel n2 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n2 NO esta en la posicion correcta." << endl;
  }

  /*
  Salida del tercer test:
  TEST 3 AGREGAR NIVEL
  Longitud de la lista de niveles de juego: 2
  Longitud de la lista de niveles de juego: 3
  
  Veo si los niveles estan en sus posiciones:

  Nivel n1 en la posicion correcta.
  Nivel n3 en la posicion correcta.
  Nivel n2 en la posicion correcta.
  */
  cout << endl << endl;
  
  /*
  Test 4:
  Agrego el nivel n4 a juegoTest en la posicion 2. El nivel deberia agregarse entre el n3 y n2.
  */

  cout << "TEST 4 AGREGAR NIVEL" << endl;
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;
  juegoTest.agregarNivel(n4,2);
  cout << "Longitud de la lista de niveles de juego: " << juegoTest.nivelesJ().size() << endl;

  cout << endl << "Veo si los niveles estan en sus posiciones:" << endl << endl;
  
  if(juegoTest.nivelesJ().at(0).anchoN() == 10 && juegoTest.nivelesJ().at(0).altoN() == 10 &&
    juegoTest.nivelesJ().at(0).solesN() == 50){
    cout << "Nivel n1 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n1 NO esta en la posicion correcta." << endl;
  }

  if(juegoTest.nivelesJ().at(1).anchoN() == 12 && juegoTest.nivelesJ().at(1).altoN() == 12 &&
    juegoTest.nivelesJ().at(1).solesN() == 24){
    cout << "Nivel n3 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n3 NO esta en la posicion correcta." << endl;
  }

  if(juegoTest.nivelesJ().at(2).anchoN() == 15 && juegoTest.nivelesJ().at(2).altoN() == 15 &&
    juegoTest.nivelesJ().at(2).solesN() == 47){
    cout << "Nivel n4 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n4 NO esta en la posicion correcta." << endl;
  }

  if(juegoTest.nivelesJ().at(3).anchoN() == 9 && juegoTest.nivelesJ().at(3).altoN() == 9 &&
    juegoTest.nivelesJ().at(3).solesN() == 13){
    cout << "Nivel n2 en la posicion correcta." << endl;
  } else {
    cout << "Nivel n2 NO esta en la posicion correcta." << endl;
  }

  /*
  Salida del cuarto test:
  TEST 4 AGREGAR NIVEL
  Longitud de la lista de niveles de juego: 3
  Longitud de la lista de niveles de juego: 4
  
  Veo si los niveles estan en sus posiciones:

  Nivel n1 en la posicion correcta.
  Nivel n3 en la posicion correcta.
  Nivel n4 en la posicion correcta.
  Nivel n2 en la posicion correcta.
  */
  cout << endl << endl;

  
  //  TESTS JUGAR NIVEL

  vector<VampiroEnEspera> spawningList5;
  spawningList5.push_back(v1);
  spawningList5.push_back(v2);
  spawningList5.push_back(v3);
  spawningList5.push_back(v4);
  Nivel nivelTest(9,9,100,spawningList5);

  /*
  Test:
  Agrego el nivelTest a la posicion 0 de la lista de niveles de juegoTest.
  Voy usando la funcion pasarturno en nivelTest para obtener un "estado futuro" del juego y
  luego aplico la funcion jugarNivel.
  El nivel deberia ir cambiandose al estado nuevo de nivelTest.
  */

  juegoTest.agregarNivel(nivelTest,0);

  cout << "TEST 1 JUGAR NIVEL" << endl;
  cout << "Nivel antes de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;
  nivelTest.pasarTurno();
  juegoTest.jugarNivel(nivelTest,0);
  cout << "Nivel despues de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;

  /*
  Salida del primer test:
  TEST 1 JUGAR NIVEL
  Nivel antes de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 100
  Turno: 0
  Longitud lista de vampiros: 0
  Longitud lista de spawning: 4
  Nivel despues de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 101
  Turno: 1
  Longitud lista de vampiros: 1
  Longitud lista de spawning: 3
  */
  cout << endl << endl;  

  cout << "TEST 2 JUGAR NIVEL" << endl;
  cout << "Nivel antes de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;
  nivelTest.pasarTurno();
  juegoTest.jugarNivel(nivelTest,0);
  cout << "Nivel despues de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;

  /*
  Salida del segundo test:
  TEST 2 JUGAR NIVEL
  Nivel antes de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 101
  Turno: 1
  Longitud lista de vampiros: 1
  Longitud lista de spawning: 3
  Nivel despues de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 102
  Turno: 2
  Longitud lista de vampiros: 2
  Longitud lista de spawning: 2
  */
  cout << endl << endl;

  cout << "TEST 3 JUGAR NIVEL" << endl;
  cout << "Nivel antes de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;
  nivelTest.pasarTurno();
  juegoTest.jugarNivel(nivelTest,0);
  cout << "Nivel despues de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;

  /*
  Salida del tercer test:
  TEST 3 JUGAR NIVEL
  Nivel antes de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 102
  Turno: 2
  Longitud lista de vampiros: 2
  Longitud lista de spawning: 2
  Nivel despues de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 103
  Turno: 3
  Longitud lista de vampiros: 3
  Longitud lista de spawning: 1
  */
  cout << endl << endl;

  cout << "TEST 4 JUGAR NIVEL" << endl;
  cout << "Nivel antes de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;
  nivelTest.pasarTurno();
  juegoTest.jugarNivel(nivelTest,0);
  cout << "Nivel despues de usar la funcion: " << endl;
  cout << "Ancho: " << juegoTest.nivelesJ().at(0).anchoN() << endl;
  cout << "Alto: " << juegoTest.nivelesJ().at(0).altoN() << endl;
  cout << "Soles: " << juegoTest.nivelesJ().at(0).solesN() << endl;
  cout << "Turno: " << juegoTest.nivelesJ().at(0).turnoN() << endl;
  cout << "Longitud lista de vampiros: " << juegoTest.nivelesJ().at(0).vampirosN().size() << endl;
  cout << "Longitud lista de spawning: " << juegoTest.nivelesJ().at(0).spawningN().size() << endl;

  /*
  Salida del cuarto test:
  TEST 4 JUGAR NIVEL
  Nivel antes de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 103
  Turno: 3
  Longitud lista de vampiros: 3
  Longitud lista de spawning: 1
  Nivel despues de usar la funcion: 
  Ancho: 9
  Alto: 9
  Soles: 104
  Turno: 4
  Longitud lista de vampiros: 4
  Longitud lista de spawning: 0
  */
  cout << endl << endl;



  //  TESTS GUARDAR JUEGO

    //Test 1: guardo juego sin flores, con vampiros, sin niveles

  cout << "TEST 1 GUARDAR JUEGO" << endl;
  Juego juegoTest1(floresVacio, vampirosJuego);
  Juego juegoTestTemp1;

  ofstream ost1 ("TestGuardarJuego1_2");

  if (ost1.is_open()) {
	  juegoTest1.Guardar(ost1);
	  ost1.close();
  }

  ifstream ist1("TestGuardarJuego1_2");
  if (ist1.is_open()) {
	  juegoTestTemp1.Cargar(ist1);
	  ist1.close();
  }

  cout << "Se guardó el juego: " << endl;
  juegoTestTemp1.Mostrar(cout);

  /* Salida del primer test:

  	TEST 1 GUARDAR JUEGO
  	Se guardó el juego:
  	JUEGO:

  	** Flores del JUEGO **

  	** Vampiros del JUEGO **

  	INFO. DEL VAMPIRO:
  	Vida del Vampiro: 10
  	Cuanto Pega el Vampiro: 10
  	Clase del Vampiro: Caminante


  	INFO. DEL VAMPIRO:
  	Vida del Vampiro: 12
  	Cuanto Pega el Vampiro: 12
  	Clase del Vampiro: Caminante


  	INFO. DEL VAMPIRO:
  	Vida del Vampiro: 15
  	Cuanto Pega el Vampiro: 15
  	Clase del Vampiro: Desviado


  	** Niveles del JUEGO **

  	*/
  cout << endl << endl;

  //Test 2: guardo juego sin inicializar, sobreescribiendo el archivo del primer test


  cout << "TEST 2 GUARDAR JUEGO" << endl;
  Juego juegoTest2;
  Juego juegoTestTemp2;

  ofstream ost2 ("TestGuardarJuego1_2");
  if (ost2.is_open()) {
	  juegoTest2.Guardar(ost2);
	  ost2.close();
  }

  ifstream ist2("TestGuardarJuego1_2");
  if (ist2.is_open()) {
	  juegoTestTemp2.Cargar(ist2);
	  ist2.close();
  }

  cout << "Se guardó el juego: " << endl;
  juegoTestTemp2.Mostrar(cout);


  /*  Salida del segundo test:

  	TEST 2 GUARDAR JUEGO
  	Se guardó el juego:
  	JUEGO:

  	** Flores del JUEGO **

  	** Vampiros del JUEGO **

  	** Niveles del JUEGO **
  */

  cout << endl << endl;

  // Test 3: guardo un juego sin flores, sin vampiros, con niveles. El último nivel se construye con spawning vacío

  cout << "TEST 3 GUARDAR JUEGO" << endl;
  Juego juegoTest3(floresVacio, vampirosVacio);
  Juego juegoTestTemp3;
  juegoTest3.agregarNivel(n1, 0);
  juegoTest3.agregarNivel(n5, 1);

  ofstream ost3("TestGuardarJuego3");
  if (ost3.is_open()) {
	  juegoTest3.Guardar(ost3);
	  ost3.close();
  }

  ifstream ist3("TestGuardarJuego3");
  if (ist3.is_open()) {
	  juegoTestTemp3.Cargar(ist3);
	  ist3.close();
  }

  if(juegoTestTemp3.nivelesJ().size() == 2 && juegoTestTemp3.floresJ().size() == 0 &&
		  juegoTestTemp3.vampirosJ().size() == 0){
	  cout << "El juego se guardó y cargo correctamente." << endl;
  } else {
	  cout << "El juego no es el correcto" << endl;
  }


  /*
  Salida del tercer test:
  TEST 3 GUARDAR JUEGO
  El juego se guardó y cargo correctamente.
  */
  // El spawning no es vacío, ya que el constructor de nivel crea un vampiro "generico"
  cout << endl << endl;


  // Test 4: uso para guardar el juego juegoTest del principio con 3 vampiros, 3 flores y 5 niveles
  cout << "TEST 4 GUARDAR JUEGO" << endl;
  Juego juegoTestTemp4;
  
  ofstream ost4("TestGuardarJuego4");
    if(ost4.is_open()) {
      juegoTest.Guardar(ost4);
      ost4.close();
  }

  ifstream is11("TestGuardarJuego4");
  if(is11.is_open()) {
    juegoTestTemp4.Cargar(is11);
    is11.close();
  }

  if(juegoTestTemp4.nivelesJ().size() == 5 && juegoTestTemp4.floresJ().size() == 3 &&
      juegoTestTemp4.vampirosJ().size() == 3){
      cout << "El juego se guardó y cargo correctamente." << endl;
    } else {
      cout << "El juego no es el correcto" << endl;
  }

  /*
  Salida del cuarto test:
  TEST 4 GUARDAR JUEGO
  El juego se guardó y cargo correctamente.
  */
  cout << endl << endl;


  //  TESTS ESTOS SALE FACIL
  
  vector<Nivel> nivelesFaciles;
  /*
  Test 1:
  Pruebo juegoTest con la funcion, deberia devolver un vector con el nivel nivelTest que 
  quedo de la funcion jugarNivel, ya es el que tiene mas soles.
  */

  nivelesFaciles = juegoTest.estosSaleFacil();

  cout << "TEST 1 ESTOS SALE FACIL" << endl;
  cout << "Longitud de la lista de niveles faciles: " << nivelesFaciles.size() << endl;

  if(nivelesFaciles.at(0).anchoN() == 9 && nivelesFaciles.at(0).altoN() == 9 && 
    nivelesFaciles.at(0).solesN() == 104){
    cout << "Nivel correcto en la lista" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  /*
  Salida del primer test:

  TEST 1 ESTOS SALE FACIL
  Longitud de la lista de niveles faciles: 1
  Nivel correcto en la lista
  */
  cout << endl << endl;

  /*
  Test 2:
  Cargo un juego con niveles y vampiros para hacer el proximo test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 2 niveles, ambos
  con 100 de soles y una flor cada uno. La funcion deberia devolver los 2 niveles.
  Nivel en posicion 0: ancho = 12, alto = 12, turno = 3, soles = 100.
  Nivel en posicion 1: ancho = 9, alto = 9, turno = 2, soles = 100
  */
  ifstream is("TestEstosSaleFacil2");

  if(is.is_open()){
    juegoTest.Cargar(is);
    is.close();
  }

  nivelesFaciles = juegoTest.estosSaleFacil();

  cout << "TEST 2 ESTOS SALE FACIL" << endl;
  cout << "Longitud de la lista de niveles faciles: " << nivelesFaciles.size() << endl;

  if(nivelesFaciles.at(0).anchoN() == 12 && nivelesFaciles.at(0).altoN() == 12 && 
    nivelesFaciles.at(0).solesN() == 100 && nivelesFaciles.at(0).turnoN() == 3){
    cout << "Nivel correcto" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  if(nivelesFaciles.at(1).anchoN() == 9 && nivelesFaciles.at(1).altoN() == 9 && 
    nivelesFaciles.at(1).solesN() == 100 && nivelesFaciles.at(1).turnoN() == 2){
    cout << "Nivel correcto" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  /*
  Salida del segundo test:

  TEST 2 ESTOS SALE FACIL
  Longitud de la lista de niveles faciles: 2
  Nivel correcto
  Nivel correcto
  */
  cout << endl << endl;

  /*
  Test 3:
  Cargo un juego con niveles y vampiros para hacer el proximo test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 3 niveles.
  Nivel en posicion 0: ancho = 12, alto = 12, turno = 3, soles = 100, cantidad flores = 1.
  Nivel en posicion 1: ancho = 9, alto = 9, turno = 2, soles = 100, cantidad flores = 1.
  Nivel en posicion 2: ancho = 10, alto = 10, turno = 6, soles = 100, cantidad flores = 2.
  Deberia devolver el nivel de la posicion 2 por tener mas flores.
  */

  ifstream is2("TestEstosSaleFacil3");

  if(is2.is_open()){
    juegoTest.Cargar(is2);
    is2.close();
  }

  nivelesFaciles = juegoTest.estosSaleFacil();

  cout << "TEST 3 ESTOS SALE FACIL" << endl;
  cout << "Longitud de la lista de niveles faciles: " << nivelesFaciles.size() << endl;

  if(nivelesFaciles.at(0).anchoN() == 10 && nivelesFaciles.at(0).altoN() == 10 && 
    nivelesFaciles.at(0).solesN() == 100 && nivelesFaciles.at(0).turnoN() == 6){
    cout << "Nivel correcto" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  /*
  Salida del tercer test:

  TEST 3 ESTOS SALE FACIL
  Longitud de la lista de niveles faciles: 1
  Nivel correcto
  */
  cout << endl << endl;

  /*
  Test 4:
  Cargo un juego con niveles y vampiros para hacer el proximo test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 4 niveles.
  Nivel en posicion 0: ancho = 12, alto = 12, turno = 3, soles = 100, cantidad flores = 1.
  Nivel en posicion 1: ancho = 9, alto = 9, turno = 2, soles = 100, cantidad flores = 1.
  Nivel en posicion 2: ancho = 10, alto = 10, turno = 6, soles = 100, cantidad flores = 2.
  Nivel en posicion 3: ancho = 8, alto = 8, turno = 1, soles = 100, cantidad flores = 2.
  Deberia devolver los ultimos dos niveles por tener la misma cantidad de soles y mayor
  cantidad de flores.
  */

  ifstream is3("TestEstosSaleFacil4");

  if(is3.is_open()){
    juegoTest.Cargar(is3);
    is3.close();
  }

  nivelesFaciles = juegoTest.estosSaleFacil();

  cout << "TEST 4 ESTOS SALE FACIL" << endl;
  cout << "Longitud de la lista de niveles faciles: " << nivelesFaciles.size() << endl;

  if(nivelesFaciles.at(0).anchoN() == 10 && nivelesFaciles.at(0).altoN() == 10 && 
    nivelesFaciles.at(0).solesN() == 100 && nivelesFaciles.at(0).turnoN() == 6){
    cout << "Nivel correcto" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  if(nivelesFaciles.at(1).anchoN() == 8 && nivelesFaciles.at(1).altoN() == 8 && 
    nivelesFaciles.at(1).solesN() == 100 && nivelesFaciles.at(1).turnoN() == 1){
    cout << "Nivel correcto" << endl;
  } else {
    cout << "No es el nivel correcto" << endl;
  }

  /*
  Salida del cuarto test:

  TEST 4 ESTOS SALE FACIL
  Longitud de la lista de niveles faciles: 2
  Nivel correcto
  Nivel correcto
  */
  cout << endl << endl;

  
  // TESTS ALTO CHEAT

  /*
  Test 1:
  Cargo un juego con niveles y vampiros para hacer el test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 1 nivel.
  El nivel posee un vampiro con 10 de vida.
  Deberia la vida ponerse a la mitad cuando aplico el test.
  */

  ifstream is4("TestAltoCheat1");

  if(is4.is_open()){
    juegoTest.Cargar(is4);
    is4.close();
  }

  cout << "TEST 1 ALTO CHEAT" << endl;
  juegoTest.altoCheat(0);
  
  if(juegoTest.nivelesJ().at(0).vampirosN().at(0).vida == 5){
    cout << "Cumple con el test!" << endl;
  } else {
    cout << "No cumple con el test." << endl;
  }

  /*
  Salida del primer test:

  TEST 1 ALTO CHEAT
  Cumple con el test!
  */
  cout << endl << endl;

  /*
  Test 2:
  Cargo un juego con niveles y vampiros para hacer el test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 2 niveles.
  Aplico la funcion altoCheat en el segundo nivel.
  El segundo nivel posee 2 vampiros, uno con 12 de vida y el otro con 15 de vida.
  Deberia la vida de ambos ponerse a la mitad (parte entera).
  */

  ifstream is5("TestAltoCheat2");

  if(is5.is_open()){
    juegoTest.Cargar(is5);
    is5.close();
  }

  cout << "TEST 2 ALTO CHEAT" << endl;
  juegoTest.altoCheat(1);

  if(juegoTest.nivelesJ().at(1).vampirosN().at(0).vida == 6 &&
    juegoTest.nivelesJ().at(1).vampirosN().at(1).vida == 7){
    cout << "Cumple con el test!" << endl;
  } else {
    cout << "No cumple con el test." << endl;
  }

  /*
  Salida del segundo test:

  TEST 2 ALTO CHEAT
  Cumple con el test!
  */
  cout << endl << endl;

  /*
  Test 3:
  Cargo un juego con niveles y vampiros para hacer el test.
  El juego posee un vector con las mismas flores y los mismos vampiros y 1 nivel.
  El nivel posee 3 vampiros, con vidas 12, 15 y 8.
  Deberia la vida de los tres ponerse a la mitad (parte entera).
  */

  ifstream is6("TestAltoCheat3");

  if(is6.is_open()){
    juegoTest.Cargar(is6);
    is6.close();
  }

  cout << "TEST 3 ALTO CHEAT" << endl;
  juegoTest.altoCheat(0);

  if(juegoTest.nivelesJ().at(0).vampirosN().at(0).vida == 6 &&
    juegoTest.nivelesJ().at(0).vampirosN().at(1).vida == 7 &&
    juegoTest.nivelesJ().at(0).vampirosN().at(2).vida == 4){
    cout << "Cumple con el test!" << endl;
  } else {
    cout << "No cumple con el test." << endl;
  }

  /*
  Salida del tercer test:

  TEST 3 ALTO CHEAT
  Cumple con el test!
  */
  cout << endl << endl;

  /*
  Test 4:
  Utilizo el juego cargado anterior pero esta vez aplico la funcion altoCheat en un nivel que no
  existe.
  La vida de los vampiros no deberia modificarse.
  */

  cout << "TEST 4 ALTO CHEAT" << endl;
  juegoTest.altoCheat(2);
  
  if(juegoTest.nivelesJ().at(0).vampirosN().at(0).vida == 6 &&
    juegoTest.nivelesJ().at(0).vampirosN().at(1).vida == 7 &&
    juegoTest.nivelesJ().at(0).vampirosN().at(2).vida == 4){
    cout << "Cumple con el test!" << endl;
  } else {
    cout << "No cumple con el test." << endl;
  }

  /*
  Salida del cuarto test:

  TEST 4 ALTO CHEAT
  Cumple con el test!
  */
  cout << endl << endl;


  // TESTS MUY DE EXACTAS

  /*
  Test 1
  Cargo un juego que posee 2 niveles sin vampiros en el juego y sin vampiros en la lista
  de spawning, ambos con una flor.
  Los dos niveles deberian ser considerados ganados y entrarian en el rango de fibonacci.
  1 1 2
  */

  ifstream is7("TestMuyDeExactas1");

  if(is7.is_open()){
    juegoTest.Cargar(is7);
    is7.close();
  }

  cout << "TEST 1 MUY DE EXACTAS" << endl; 
  if(juegoTest.muyDeExactas()){
    cout << "Cumple!" << endl;
  } else{
    cout << "No cumple." << endl;
  }

  /*
  Salida del primer test:

  TEST 1 MUY DE EXACTAS
  Cumple!
  */
  cout << endl << endl;

  /*
  Test 2
  Cargo un juego que posee 4 niveles sin vampiros en el juego y sin vampiros en la lista
  de spawning, todos con una flor.
  Los 4 niveles deberian ser considerados ganados y por las posiciones no entrarian en el 
  rango de fibonacci.
  1 1 2 3 5
  */

  ifstream is8("TestMuyDeExactas2");

  if(is8.is_open()){
    juegoTest.Cargar(is8);
    is8.close();
  }

  cout << "TEST 2 MUY DE EXACTAS" << endl; 
  if(!juegoTest.muyDeExactas()){
    cout << "Cumple!" << endl;
  } else{
    cout << "No cumple." << endl;
  }

  /*
  Salida del segundo test:

  TEST 2 MUY DE EXACTAS
  Cumple!
  */
  cout << endl << endl; 

  /*
  Test 3
  Cargo un juego que posee 5 niveles.
  El primer nivel sin vampiros en espera ni en spawning.
  El segundo nivel sin vampiros en espera ni en spawning.
  El tercer nivel sin vampiros en espera ni en spawning.
  El cuarto nivel con vampiros en espera y en spawning.
  El quinto nivel sin vampiros en espera ni en spawning.
  Los niveles sin vampiros deberian ser considerados como ganados y entran en el rango
  de fibonacci.
  1 1 2 3 5
  */

  ifstream is9("TestMuyDeExactas3");

  if(is9.is_open()){
    juegoTest.Cargar(is9);
    is9.close();
  }

  cout << "TEST 3 MUY DE EXACTAS" << endl; 
  if(juegoTest.muyDeExactas()){
    cout << "Cumple!" << endl;
  } else{
    cout << "No cumple." << endl;
  }

  /*
  Salida del tercer test:

  TEST 3 MUY DE EXACTAS
  Cumple!
  */
  cout << endl << endl;

  /*
  Test 4
  Cargo un juego que posee 6 niveles.
  Solo el cuarto nivel con vampiros en espera y en spawning.
  Los niveles sin vampiros deberian ser considerados como ganados y no entran en el rango
  de fibonacci.
  1 1 2 3 5 8
  */

  ifstream is10("TestMuyDeExactas4");

  if(is10.is_open()){
    juegoTest.Cargar(is10);
    is10.close();
  }

  cout << "TEST 4 MUY DE EXACTAS" << endl; 
  if(!juegoTest.muyDeExactas()){
    cout << "Cumple!" << endl;
  } else {
    cout << "No cumple." << endl;
  }

  /*
  Salida del cuarto test:

  TEST 4 MUY DE EXACTAS
  Cumple!
  */
  cout << endl;
}
