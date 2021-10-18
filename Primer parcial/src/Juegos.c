/*
 * Juegos.c
 *
 *  Created on: 17 oct. 2021
 *      Author: Juli�n Zubini
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Juegos.h"
#include "UTN_Ingreso.h"
#define REINTENTOS 5
#define VERDADERO 1
#define FALSO 0
#define LIBRE 1
#define OCUPADO 0

/* Brief: la funcion se encarga de inicializar la variable "estado" de todas las posiciones del array Juegos en LIBRE
 * Param listaJuegos: lista de juegos
 * Param tam: tama�o del array
 */

int juegos_inicializarJuegos(Juegos* listaJuegos,int tam){
	int retorno;
	if(listaJuegos != NULL || tam > 0){
		for(int i = 0; i < tam;i++){
			listaJuegos[i].estado = LIBRE;
		}
		retorno = VERDADERO;
	}else{
		retorno = FALSO;
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir todos los juegos cargados en el sistema
 * Param listaJuegos: lista de juegos
 * Param tam: tama�o del array
 */

void juegos_mostrarJuegosCargados(Juegos* listaJuegos,int tam){
	printf("--------------------------------Juegos cargados--------------------------------\n");
	for(int i = 0;i<tam;i++){
		if(listaJuegos[i].estado == OCUPADO){
			printf("\t-%s\n" ,listaJuegos[i].nombreDelJuego);
		}
	}
}

/* Brief: la funcion se encarga de encontrar un �ndice libre donde podamos cargar datos
 * Param listaJuegos: lista de juegos
 * Param tam: tama�o del array
 * Param *pEspacioLibre: puntero a la direcci�n de memoria donde vamos a almacenar ese �ndice.
 */

int juegos_encontrarEspacioLibre(Juegos* listaJuegos,int tam, int* pEspacioLibre){
	int retorno = VERDADERO;
	if(listaJuegos == NULL && tam < 0){
		retorno = FALSO;
	}else{
		for(int i = 0;i < tam; i++){
			if(listaJuegos[i].estado == LIBRE){
				*pEspacioLibre = i;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar validar que el nombre que se recibe por par�metro no se encuentre cargado en la lista
 * Param listaJuegos: lista de juegos
 * Param tam: tama�o del array
 * Param nombreDelJuego: dato con el nombre del juego.
 */

int juegos_validarNombresRepetidos(Juegos* listaJuegos,int tam,char* nombreDelJuego){
	int retorno = FALSO;
	for(int i = 0;i<tam;i++){
		if(strcmp(listaJuegos[i].nombreDelJuego,nombreDelJuego) == 0){
			retorno = VERDADERO;
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de cargar el dato "nombreDelJuego" en el array siempre y cuando las validaciones se�n correctas.
 * Param listaJuegos: lista de juegos
 * Param tam: tama�o del array
 * Param nombreDelJuego: dato con el nombre del juego.
 */

int juegos_cargarJuegos(Juegos* listaJuegos,int tam,char* nombreDelJuego){
	int retorno = FALSO;
	int espacioLibre;
	juegos_encontrarEspacioLibre(listaJuegos, tam,&espacioLibre);
	if(juegos_validarNombresRepetidos(listaJuegos, tam, nombreDelJuego) == FALSO){
		strcpy(listaJuegos[espacioLibre].nombreDelJuego,nombreDelJuego);
		listaJuegos[espacioLibre].estado = OCUPADO;
		retorno = VERDADERO;
	}
	return retorno;
}
















