/*
 * Informes.c
 *
 *  Created on: 17 oct. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Informes.h"
#include "Salon.h"
#include "Arcade.h"
#include "Juegos.h"
#include "UTN_Ingreso.h"
#include "UTN_Calculadora.h"
#define REINTENTOS 5
#define VERDADERO 1
#define FALSO 0
#define LIBRE 1
#define OCUPADO 0
#define LIBRE 1
#define OCUPADO 0
#define MONO 0
#define ESTEREO 1
#define SHOPPING 1
#define LOCAL 0
#define MIN_LISTA 1
#define MAX_LISTA 2
#define MIN_SALON 1
#define MAX_SALON 100
#define TAM_INDICE 100
#define TAM_NOMBRE_JUEGO 63

/* Brief: la funcion se encarga de contar la cantidad de arcades que posee un salón específico mediante su ID recibida por parámetro.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 * Param IDSalon: numero de ID del salón que se desea contar.
 */

int contadorDeArcadesPorIDSalon(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades,int tamanioArcades,int IDSalon){
	int contador = 0;
	int indiceSalon;
	for(int i = 0;i<tamanioArcades;i++){
		if(listaArcades[i].estado == OCUPADO){
			salon_encontrarEspacioPorID(listaSalones, tamanioSalones, IDSalon, &indiceSalon);
			if(listaSalones[indiceSalon].IDSalon == listaArcades[i].IDSalon){
				contador++;
			}
		}
	}
	return contador;
}

/* Brief: la funcion se encarga de contar la cantidad de fichas total que tienen entre todos los arcades.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 * Param indiceSalon: índice del salón que se desea contar.
 */

int acumuladorDeFichasTotalesDeUnSalon(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades,int tamanioArcades,int indiceSalon){
	int acumuladorFichas = 0;
	for(int i = 0; i<tamanioArcades;i++){
		if(listaArcades[i].estado == OCUPADO){
			if(listaArcades[i].IDSalon == listaSalones[indiceSalon].IDSalon){
				acumuladorFichas += listaArcades[i].capacidadMaximaDeFichas;
			}
		}
	}
	return acumuladorFichas;
}

/* Brief: la funcion se encarga de imprimir por pantalla aquellos salones que tengan más de 4 arcades.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_salonesConMasDeCuatroArcades(Salon* listaSalones, int tamanioSalones,Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	printf("\t A) LISTADO DE SALONES QUE TIENEN MÁS DE 4 JUEGOS\n");
	for(int i = 0;i<tamanioSalones;i++){
		if(listaSalones[i].estado == OCUPADO){
			if(contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades,tamanioArcades,listaSalones[i].IDSalon) > 4){
				printf("\t-------------------------------------ID: %d-------------------------------------\n" ,listaSalones[i].IDSalon);
				printf("\tNombre: %s\n" ,listaSalones[i].nombreDelSalon);
				printf("\tDirección: %s\n" ,listaSalones[i].direccionDelSalon);
				switch(listaSalones[i].tipoDeSalon){
					case SHOPPING:
						printf("\tTipo: SHOPPING\n");
						break;
					case LOCAL:
						printf("\tTipo: LOCAL\n");
						break;
				}
				retorno = VERDADERO;
			}
		}
	}
	if(retorno == FALSO){
		printf("\tNo hay salones con más de cuatro arcades para mostrar.\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir por pantalla aquellos arcades que seán para más de dos jugadores.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_listadoDeArcadesConMasDeDosJugadores(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	printf("\t B) LISTADO DE ARCADES CON MÁS DE DOS JUGADORES\n");
	for(int i = 0;i<tamanioArcades;i++){
		if(listaArcades[i].estado == OCUPADO){
			if(listaArcades[i].cantidadDeJugadores > 2){
				printf("\t-------------------------------------ID: %d-------------------------------------\n" ,listaArcades[i].IDArcade);
				printf("\tCantidad de jugadores: %d\n" ,listaArcades[i].cantidadDeJugadores);
				printf("\tNombre del juego: %s\n" ,listaArcades[i].nombreDelJuego);
				for(int x = 0;x<tamanioSalones;x++){
					if(listaArcades[i].IDSalon == listaSalones[x].IDSalon){
						printf("\tNombre del salon: %s\n" ,listaSalones[x].nombreDelSalon);
						retorno = VERDADERO;
						break;
					}
				}
			}
		}
	}
	if(retorno == FALSO){
		printf("\tNo hay arcades con más de dos jugadores para mostrar.\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir por pantalla los datos de un salón específico mediante la ID ingresada por el usuario.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_imprimirDatosDeSalonPorID(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	int IDIngresada;
	int indice;
	printf("\t C) IMPRIMIR SALONES POR ID CON CANTIDAD DE ARCADES\n");
	if(UTN_ingresoIntReintentosMinMax(&IDIngresada, "Ingrese la ID del salon: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_SALON, MAX_SALON, REINTENTOS) == VERDADERO){
		if(salon_encontrarEspacioPorID(listaSalones, tamanioSalones, IDIngresada, &indice) == VERDADERO){
			printf("\tNombre: %s\n" ,listaSalones[indice].nombreDelSalon);
			printf("\tDirección: %s\n" ,listaSalones[indice].direccionDelSalon);
			switch(listaSalones[indice].tipoDeSalon){
				case SHOPPING:
					printf("\tTipo: SHOPPING\n");
					break;
				case LOCAL:
					printf("\tTipo: LOCAL\n");
					break;
			}
			printf("\tCantidad de arcades que posee: %d\n" ,contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, IDIngresada));
			retorno = VERDADERO;
		}else{
			printf("\tNo se ha podido encontrar la ID ingresada, vuelva al menú e intentelo nuevamente.\n");
		}
	}else{
		printf("\tHubo un error en el ingreso de ID, vuelva al menú e intentelo nuevamente\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir por pantalla los datos de un salon con sus respectivos arcades.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_imprimirArcadeDeSalonPorID(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	int IDIngresada;
	int indice;
	printf("\t D) IMPRIMIR ARCADES POR ID DE SALON\n");
	if(UTN_ingresoIntReintentosMinMax(&IDIngresada, "Ingrese la ID del salon: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_SALON, MAX_SALON, REINTENTOS) == VERDADERO){
		if(salon_encontrarEspacioPorID(listaSalones, tamanioSalones, IDIngresada, &indice) == VERDADERO){
			printf("DATOS DEL SALON\n");
			printf("\tNombre: %s\n" ,listaSalones[indice].nombreDelSalon);
			switch(listaSalones[indice].tipoDeSalon){
				case SHOPPING:
					printf("\tTipo: SHOPPING\n");
					break;
				case LOCAL:
					printf("\tTipo: LOCAL\n");
					break;
			}
			printf("ARCADES QUE POSEE\n");
			for(int i = 0;i<tamanioArcades;i++){
				if(listaArcades[i].estado == OCUPADO){
					if(listaArcades[i].IDSalon == listaSalones[indice].IDSalon){
						printf("\t-------------------------------------ID: %d-------------------------------------\n" ,listaArcades[i].IDArcade);
						printf("\tNacionalidad: %s\n" ,listaArcades[i].nacionalidadArcade);
						printf("\tNombre del juego: %s\n",listaArcades[i].nombreDelJuego);
						printf("\tCantidad de jugadores: %d\n" ,listaArcades[i].cantidadDeJugadores);
						printf("\tCapacidad de fichas: %d\n" ,listaArcades[i].capacidadMaximaDeFichas);
						switch(listaArcades[i].tipoDeSonidad){
							case MONO:
								printf("\tTipo: MONO\n");
								break;
							case ESTEREO:
								printf("\tTipo: ESTEREO\n");
								break;
						}
						printf("\tID salon: %d\n" ,listaArcades[i].IDSalon);
						printf("\t--------------------------------------------------------------------------------\n");
						retorno = VERDADERO;
					}
				}
			}
		}else{
			printf("\tNo se ha podido encontrar la ID ingresada, vuelva al menú e intentelo nuevamente.\n");
		}
	}else{
		printf("\tHubo un error en el ingreso de ID, vuelva al menú e intentelo nuevamente\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir por pantalla el salón o salones, en caso de que tengán la misma cantidad, con mayor cantidad de arcades.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_imprimirSalonConMayorCantidadDeArcades(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	int banderaSalonConMayorCantidadDeArcades = VERDADERO;
	int indiceSalonConMayorCantidadDeArcades;
	int numeroMayorDeArcades;
	int banderaSalonesConMismaCantidadDeArcades;
	int indicesConCantidadDeArcadesIguales[TAM_INDICE];
	int indice = 0;
	int contadorDeIngresosIguales = 0;
	printf("\tE) MOSTRAR SALON/ES CON MAYOR CANTIDAD DE ARCADES\n");
	for(int i = 0;i<tamanioSalones;i++){
		if(listaSalones[i].estado == OCUPADO){
			if(banderaSalonConMayorCantidadDeArcades == VERDADERO){
				indiceSalonConMayorCantidadDeArcades = i;
				numeroMayorDeArcades = contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, listaSalones[i].IDSalon);
				banderaSalonConMayorCantidadDeArcades = FALSO;
			}else{
				if(contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, listaSalones[i].IDSalon) > numeroMayorDeArcades){
					indiceSalonConMayorCantidadDeArcades = i;
					numeroMayorDeArcades = contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, listaSalones[i].IDSalon);
				}
				if(contadorDeArcadesPorIDSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, listaSalones[i].IDSalon) == numeroMayorDeArcades){
					banderaSalonesConMismaCantidadDeArcades = VERDADERO;
					indicesConCantidadDeArcadesIguales[indice] = i;
					indice++;
					contadorDeIngresosIguales++;
				}
			}
		}
	}

	printf("\tID Salón: %d\n" ,listaSalones[indiceSalonConMayorCantidadDeArcades].IDSalon);
	printf("\tNombre: %s\n" ,listaSalones[indiceSalonConMayorCantidadDeArcades].nombreDelSalon);
	printf("\tDirección: %s\n" ,listaSalones[indiceSalonConMayorCantidadDeArcades].direccionDelSalon);
	switch(listaSalones[indiceSalonConMayorCantidadDeArcades].tipoDeSalon){
		case SHOPPING:
			printf("\tTipo: SHOPPING\n");
			break;
		case LOCAL:
			printf("\tTipo: LOCAL\n");
			break;
	}
	printf("\tCantidad de arcades que posee: %d\n" ,numeroMayorDeArcades);
	if(banderaSalonesConMismaCantidadDeArcades == VERDADERO){
		for(int y = 0;y<contadorDeIngresosIguales;y++){
			printf("\t------------------------------------------------------------------------------------------------\n");
			printf("\tID Salón: %d\n" ,listaSalones[indicesConCantidadDeArcadesIguales[y]].IDSalon);
			printf("\tNombre: %s\n" ,listaSalones[indicesConCantidadDeArcadesIguales[y]].nombreDelSalon);
			printf("\tDirección: %s\n" ,listaSalones[indicesConCantidadDeArcadesIguales[y]].direccionDelSalon);
			switch(listaSalones[indicesConCantidadDeArcadesIguales[y]].tipoDeSalon){
				case SHOPPING:
					printf("\tTipo: SHOPPING\n");
					break;
				case LOCAL:
					printf("\tTipo: LOCAL\n");
					break;
			}
			printf("\tCantidad de arcades que posee: %d\n" ,numeroMayorDeArcades);
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de calcular e imprimir el dinero total que podría hacer el salón multiplicando el precio de ficha, ingresado por el usuario, con la cantidad de fichas totales del salón.
 * Param listaSalones: lista de salones
 * Param tamanioSalones: tamaño del array salones
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_calcularDineroTotalDeUnSalon(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	int indice;
	int IDIngresada;
	float precioPorFicha;
	float resultado;
	printf("\tF) DINERO TOTAL QUE PODRÍA HACER UN SALÓN\n");
	if(UTN_ingresoIntReintentosMinMax(&IDIngresada, "Ingrese la ID del salon: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", MIN_SALON, MAX_SALON, REINTENTOS) == VERDADERO){
		if(salon_encontrarEspacioPorID(listaSalones, tamanioSalones, IDIngresada, &indice) == VERDADERO){
			if(UTN_ingresoFloatReintentos(&precioPorFicha, "Ingrese el precio por ficha: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS) == VERDADERO){
				resultado = multiplicacionDeNumeros(precioPorFicha,acumuladorDeFichasTotalesDeUnSalon(listaSalones, tamanioSalones, listaArcades, tamanioArcades, indice));
			}else{
				printf("\tHubo un problema en el ingreso del precio, vuelva al menú e intentelo nuevamente\n");
			}
		}else{
			printf("\tNo se ha podido encontrar la ID ingresada, vuelva al menú e intentelo nuevamente.\n");
		}
	}else{
		printf("\tHubo un problema en el ingreso del ID, vuelva al menú e intentelo nuevamente\n");
	}
	printf("\tMonto total que podría hacer el salón: %f\n" ,resultado);
	return retorno;
}

/* Brief: la funcion se encarga de mostrar por pantalla los arcades que contengan el nombre del juego ingresado por el usuario.
 * Param listaArcades: lista de arcades
 * Param tamanioArcades: tamaño del array arcades
 */

int informes_mostrarListaDeArcadesQueContienenElJuegoIngresado(Arcade* listaArcades, int tamanioArcades){
	int retorno = FALSO;
	char auxiliarNombre[TAM_NOMBRE_JUEGO];
	int contadorArcades = 0;
	printf("\tG) MOSTRAR ARCADES QUE TENGAN EL NOMBRE DE JUEGO INGRESADO\n");
	if(UTN_ingresoTextoReintentos(auxiliarNombre, TAM_NOMBRE_JUEGO, "Ingrese el nombre del juego que desea buscar: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS) == VERDADERO){
		for(int i = 0;i<tamanioArcades;i++){
			if(listaArcades[i].estado == OCUPADO){
				if(strcmp(listaArcades[i].nombreDelJuego,auxiliarNombre) == 0){
					contadorArcades++;
					retorno = VERDADERO;
				}
			}
		}
	}else{
		printf("\tHubo un problema en el ingreso del nombre, vuelva al menú e intentelo nuevamente\n");
	}
	printf("Cantidad de arcades que tienen el juego '%s' : %d\n" ,auxiliarNombre,contadorArcades);
	return retorno;
}






















