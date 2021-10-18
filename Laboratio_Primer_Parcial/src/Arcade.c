/*
 * Arcade.c
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arcade.h"
#include "UTN_Ingreso.h"
#define REINTENTOS 5
#define VERDADERO 1
#define FALSO 0
#define LIBRE 1
#define OCUPADO 0
#define MONO 0
#define ESTEREO 1
#define TAM_DATOS 150
#define TAM_NOMBRE_JUEGO 63
#define MIN_TIPO_SONIDAD 0
#define MAX_TIPO_SONIDAD 1

/* Brief: la funcion se encarga de llevar un contador de ID's el cúal se va aumentando a medida que se ingresan arcades
 */
int arcade_nuevaID(void){
	static int contador = 1;
	return contador++;
}

/* Brief: la funcion se encarga de inicializar la variable "estado" de todas las posiciones del array Arcade en LIBRE
 * Param listaArcade: lista de arcades
 * Param tam: tamaño del array
 */

int arcade_inicializarArcade(Arcade* listaArcade,int tam){
	int retorno;
	if(listaArcade != NULL || tam > 0){
		for(int i = 0; i < tam;i++){
			listaArcade[i].estado = LIBRE;
		}
		retorno = VERDADERO;
	}else{
		retorno = FALSO;
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir todos los arcades cargados en el sistema
 * Param listaArcade: lista de arcades
 * Param tam: tamaño del array
 */

void arcade_mostrarArcadeCargados(Arcade* listaArcade,int tam){
	for(int i = 0;i<tam;i++){
		if(listaArcade[i].estado == OCUPADO){
			printf("-------------------------------------ID: %d-------------------------------------\n" ,listaArcade[i].IDArcade);
			printf("Nombre: %s\n" ,listaArcade[i].nacionalidadArcade);
			printf("Cantidad de jugadores: %d\n" ,listaArcade[i].cantidadDeJugadores);
			printf("Capacidad de fichas: %d\n" ,listaArcade[i].capacidadMaximaDeFichas);
			switch(listaArcade[i].tipoDeSonidad){
				case MONO:
					printf("Tipo: MONO\n");
					break;
				case ESTEREO:
					printf("Tipo: ESTEREO\n");
					break;
			}
			printf("ID salon: %d\n" ,listaArcade[i].IDSalon);
			printf("Nombre del juego: %s\n",listaArcade[i].nombreDelJuego);
			printf("--------------------------------------------------------------------------------\n");
		}
	}
}

/* Brief: la funcion se encarga de buscar el indice donde pertenece la ID recibida por parámetro y devolvera por puntero
 * Param listaArcade: lista de arcades
 * Param tam: tamaño del array
 * Param ID: valor ID del indice que estamos buscando.
 * Param *pEspacio: puntero a la dirección de memoria donde vamos a almacenar ese índice.
 */

int arcade_encontrarEspacioPorID(Arcade* listaArcade, int tam, int ID, int* pEspacio){
	int i;
	int retorno = FALSO;
	if(tam > 0 && ID > -1 && pEspacio != NULL){
		for(i = 0;i<=tam;i++){
			if(listaArcade[i].IDArcade == ID){
				*pEspacio = i;
				retorno = VERDADERO;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar un índice libre donde podamos cargar datos
 * Param listaArcade: lista de arcades
 * Param tam: tamaño del array
 * Param *pEspacio: puntero a la dirección de memoria donde vamos a almacenar ese índice.
 */

int arcade_encontrarEspacioLibre(Arcade* listaArcade, int tam, int* pEspacioLibre){
	int retorno = VERDADERO;
	if(listaArcade == NULL && tam < 0){
		retorno = FALSO;
	}else{
		for(int i = 0;i < tam; i++){
			if(listaArcade[i].estado == LIBRE){
				*pEspacioLibre = i;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar cargar los datos recibidos por parámetro en el array de arcades
 * Param listaArcade: lista de arcades
 * Param tam: tamaño del array
 * Param nacionalidadArcade: recibe el dato de la nacionalidad del arcade.
 * Param tipoDeSonidad: recibe el dato del tipo de sonidad
 * Param capacidadMaximaDeFichas: recibe el dato de la capacidad máxima de fichas
 * Param IDSalon: recibe la ID del salón al que pertenece
 * Param nombreDelJuego: recibe el dato del nombre del juego
 * Param cantidadDeJugadores: recibe el dato de la cantidad de jugadores.
 */

int arcade_anadirArcade(Arcade* listaArcade, int tam,char* nacionalidadArcade,int tipoDeSonidad, int capacidadMaximaDeFichas,int IDSalon, char* nombreDeJuego,int cantidadDeJugadores){
	int espacioLibre;
	int retorno;
	if(arcade_encontrarEspacioLibre(listaArcade, tam,&espacioLibre) == VERDADERO){
		if(listaArcade != NULL && tam > 0 && IDSalon > 0 && nacionalidadArcade != NULL && nombreDeJuego != NULL && tipoDeSonidad > -1 && capacidadMaximaDeFichas > 0){
			listaArcade[espacioLibre].IDArcade = arcade_nuevaID();
			strcpy(listaArcade[espacioLibre].nacionalidadArcade,nacionalidadArcade);
			strcpy(listaArcade[espacioLibre].nombreDelJuego,nombreDeJuego);
			listaArcade[espacioLibre].tipoDeSonidad = tipoDeSonidad;
			listaArcade[espacioLibre].cantidadDeJugadores = cantidadDeJugadores;
			listaArcade[espacioLibre].capacidadMaximaDeFichas = capacidadMaximaDeFichas;
			listaArcade[espacioLibre].IDSalon = IDSalon;
			listaArcade[espacioLibre].estado = OCUPADO;
			retorno = VERDADERO;
		}else{
			puts("ACÁ ESTA EL PROBLEMA GIL");
		}
	}else{
		printf("No hay más espacio disponible para nuevos contratos\n");
		retorno = FALSO;
	}
	return retorno;
}





