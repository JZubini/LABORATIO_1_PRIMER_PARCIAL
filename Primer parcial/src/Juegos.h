/*
 * Juegos.h
 *
 *  Created on: 17 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef JUEGOS_H_
#define JUEGOS_H_

#define TAM_NOMBRE_JUEGO 63

typedef struct{
	char nombreDelJuego[TAM_NOMBRE_JUEGO];
	int estado;
}Juegos;

int juegos_inicializarJuegos(Juegos* listaJuegos,int tam);
void juegos_mostrarJuegosCargados(Juegos* listaJuegos,int tam);
int juegos_cargarJuegos(Juegos* listaJuegos,int tam,char* nombreDelJuego);

#endif /* JUEGOS_H_ */
