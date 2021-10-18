/*
 ============================================================================
 Name        : Arcade.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Salon.h"
#include "Arcade.h"
#define TAM_SALON 100
#define TAM_ARCADES 1000
#define TAM_JUEGOS 1000
int main(void) {
	setbuf(stdout,NULL);
	Salon listaDeSalones[TAM_SALON];
	Arcade listaDeArcades[TAM_ARCADES];
	Juegos listaDeJuegos[TAM_JUEGOS];
	salon_inicializarSalones(listaDeSalones,TAM_SALON);
	arcade_inicializarArcade(listaDeArcades, TAM_ARCADES);
	juegos_inicializarJuegos(listaDeJuegos, TAM_JUEGOS);
	menu(listaDeSalones,TAM_SALON,listaDeArcades,TAM_ARCADES,listaDeJuegos,TAM_JUEGOS);
	return EXIT_SUCCESS;
}
