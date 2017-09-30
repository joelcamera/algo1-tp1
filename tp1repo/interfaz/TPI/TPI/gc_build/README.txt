Renombrar MakefileOSX a Makefile si se está compilando en OSX

-Instalacion:
	SDL2, SDL2_Image y SDL2_ttf

-Para linux usando apt, apt-get. Instalar los siguientes paquetes:
	build-essential
	libsdl2-dev
	libsdl2-image-dev
	libsdl2-ttf-dev

-Para OSX la libreria se encuentra en: https://www.libsdl.org/download-2.0.php


-Incluir los .cpp necesarios en OBJS del Makefile de la siguiente manera:

	OBJS = ../src/tp_src/Ejemplo.cpp