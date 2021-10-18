/*
 * Arcade.h
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef ARCADE_H_
#define ARCADE_H_

#define TAM_DATOS 150
#define TAM_NOMBRE_JUEGO 63

typedef struct{
	int IDArcade;
	char nacionalidadArcade[TAM_DATOS];
	int tipoDeSonidad;
	int cantidadDeJugadores;
	int capacidadMaximaDeFichas;
	int IDSalon;
	char nombreDelJuego[TAM_NOMBRE_JUEGO];
	int estado;
}Arcade;

int arcade_anadirArcade(Arcade* listaArcade, int tam,char* nacionalidadArcade,int tipoDeSonidad, int capacidadMaximaDeFichas,int IDSalon, char* nombreDeJuego, int cantidadDeJugadores);
int arcade_inicializarArcade(Arcade* listaArcade,int tam);
void arcade_mostrarArcadeCargados(Arcade* listaArcade,int tam);
int arcade_encontrarEspacioPorID(Arcade* listaArcade, int tam, int ID, int* pEspacio);

#endif /* ARCADE_H_ */
