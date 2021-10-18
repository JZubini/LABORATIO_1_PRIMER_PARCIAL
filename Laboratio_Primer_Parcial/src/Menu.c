/*
 * Menu.c
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Salon.h"
#include "Arcade.h"
#include "Juegos.h"
#include "Informes.h"
#include "UTN_Ingreso.h"
#define MIN_MENU 1
#define MAX_MENU 10
#define REINTENTOS 5
#define VERDADERO 1
#define FALSO 0
#define MIN_TIPO_SONIDAD 0
#define MAX_TIPO_SONIDAD 1
#define MIN_MOD_MENU 1
#define MAX_MOD_MENU 2
#define LIBRE 1
#define OCUPADO 0
#define MONO 0
#define ESTEREO 1
#define SHOPPING 1
#define LOCAL 0

/* Brief: la funcion se encarga de mostrar los datos completos de un arcade junto con sus respectivos datos del salón al que pertenece. (Ejercicio 6 Parcial)
 * Param listaSalones: lista de salones
 * Param tamanoSalon: tamaño del array salon
 * Param listaArcade: lista de arcades
 * Param tamanoArcade: tamaño del array arcade
 */

void datosCompletos(Salon* listaSalones , int tamanoSalon , Arcade* listaArcade , int tamanoArcade){
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("----------------------DATOS ARCADE----------------------\n");
	for(int i = 0;i<tamanoArcade;i++){
		if(listaArcade[i].estado == OCUPADO){
			printf("------------------------ID ARCADE: %d------------------------\n" ,listaArcade[i].IDArcade);
			printf("Nombre: %s\n" ,listaArcade[i].nacionalidadArcade);
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
		for(int x = 0;x<tamanoSalon;x++){
			if(listaSalones[x].estado == OCUPADO){
				if(listaSalones[x].IDSalon == listaArcade[i].IDSalon){
					printf("----------------------DATOS SALON----------------------\n");
					printf("------------------------ID SALON: %d------------------------\n" ,listaSalones[x].IDSalon);
					printf("Nombre: %s\n" ,listaSalones[x].nombreDelSalon);
					printf("Dirección: %s\n" ,listaSalones[x].direccionDelSalon);
					switch(listaSalones[x].tipoDeSalon){
						case SHOPPING:
							printf("Tipo: SHOPPING\n");
							break;
						case LOCAL:
							printf("Tipo: LOCAL\n");
							break;
					}
				}
			}
		}
	}
}

/* Brief: la funcion se encarga de dar de baja los arcades que pertenecen a un salón mediante el indice recibido por parámetro
 * Param listaSalones: lista de salones
 * Param tamanoSalon: tamaño del array salon
 * Param listaArcade: lista de arcades
 * Param tamanoArcade: tamaño del array arcade
 * Param indiceBaja: indice del salón que se dió de baja.
 */

int bajaArcadesDeUnSalon(Salon* listaSalones,int tamanioSalones, Arcade* listaArcades,int tamanioArcades, int indiceBaja){
	int retorno = FALSO;
	for(int i = 0;i<tamanioArcades;i++){
		if(listaArcades[i].estado == OCUPADO){
			if(listaSalones[indiceBaja].IDSalon == listaArcades[i].IDSalon){
				listaArcades[i].estado = LIBRE;
				retorno = VERDADERO;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de desplegar un menú que se repite hasta que el usuario desee salir del programa.
 * Param listaSalones: lista de salones
 * Param tamanoSalon: tamaño del array salon
 * Param listaArcade: lista de arcades
 * Param tamanoArcade: tamaño del array arcade
 * Param listaJuegos: lista de juegos
 * Param tamanoJuegos: tamaño del array juegos
 */

void menu(Salon* listaSalones , int tamanioSalon , Arcade* listaArcade , int tamanioArcade, Juegos* listaJuegos,int tamanoJuegos){
	int respuestaUsuarioMenu;
	int banderaAltaSalones;
	int banderaAltaArcades;
	char auxiliarNacionalidadArcade[TAM_DATOS];
	char auxiliarNombreDelJuego[TAM_NOMBRE_JUEGO];
	int auxiliarTipoDeSonidad;
	int auxiliarCantidadDeJugadores;
	int auxiliarCapacidadMaximaDeFichas;
	int auxiliarIDSalon;
	int estadoIngresoNacionalidad;
	int estadoIngresoNombreDelJuego;
	int estadoIngresoCantidadDeJugadores;
	int estadoIngresoTipoDeSonidad;
	int estadoIngresoCapacidadMaxima;
	int estadoIngresoIDSalon;
	int auxiliarIDModificar;
	int auxiliarEspacioModificar;
	int respuestaUsuarioMenuModificacion;
	int auxiliarNuevaCantidadDeJugadores;
	int auxiliarIDBaja;
	int indiceBaja;
	int auxiliarEspacioBaja;
	char auxiliarNuevoNombreJuego[TAM_NOMBRE_JUEGO];
	int respuestaUsuarioBaja;

	do{
		printf("-------------------------------------------------------------------------------------\n");
		printf("--------------------------------MENU PRINCIPAL---------------------------------------\n");
		printf("Bienvenido, seleccione una de las siguientes opciones: \n");
		printf("\t1-Alta de salon\n");
		printf("\t2-Baja de salon\n");
		printf("\t3-Imprimir salones\n");
		printf("\t4-Alta de arcade\n");
		printf("\t5-Modificar arcade\n");
		printf("\t6-Eliminar arcade\n");
		printf("\t7-Imprimir arcade\n");
		printf("\t8-Imprimir juegos\n");
		printf("\t9-Informes\n");
		printf("\t10-Salir\n");


		if(UTN_ingresoIntReintentosMinMax(&respuestaUsuarioMenu, "Ingrese una opcion del menu: ", "ERROR, el valor ingresado no coincide con las del menu, reingrese a continuacion: \n", MIN_MENU, MAX_MENU, REINTENTOS) == VERDADERO){
			switch(respuestaUsuarioMenu){
			case 1:
				salon_cargarSalones(listaSalones, tamanioSalon);
				banderaAltaSalones = VERDADERO;
				break;
			case 2:
				if(banderaAltaSalones == VERDADERO){
					if(salon_bajaSalon(listaSalones, tamanioSalon, &indiceBaja) == VERDADERO && bajaArcadesDeUnSalon(listaSalones, tamanioSalon, listaArcade, tamanioArcade, indiceBaja) == VERDADERO){
						printf("¡Éxito en la operacion!\n");
					}else{
						printf("Ha ocurrido un error inesperado en la baja del salón, vuelva al menú e intentelo nuevamente.");
					}
				}else{
					printf("Todavía no se ha hecho el alta de ningún salón, vuelva al menú e intentelo de nuevo.\n");
				}
				break;
			case 3:
				if(banderaAltaSalones == VERDADERO){
					salon_mostrarSalonesCargados(listaSalones, tamanioSalon);
				}else{
					printf("Todavía no se ha hecho el alta de ningún salón, vuelva al menú e intentelo de nuevo.\n");
				}
				break;
			case 4:
				estadoIngresoNacionalidad = UTN_ingresoTextoReintentos(auxiliarNacionalidadArcade, TAM_DATOS, "Ingrese la nacionalidad del arcade: ", "ERROR, el dato ingresado es incorrecto, reingrese a continuacion: ", REINTENTOS);
				estadoIngresoNombreDelJuego = UTN_ingresoTextoReintentos(auxiliarNombreDelJuego, TAM_NOMBRE_JUEGO, "Ingrese el nombre del juego que contiene: ", "ERROR, el dato ingresado es incorrecto, reingrese a continuacion: ", REINTENTOS);
				estadoIngresoCantidadDeJugadores = UTN_ingresoIntReintentos(&auxiliarCantidadDeJugadores,"Ingrese la cantidad de jugadores: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ", REINTENTOS);
				estadoIngresoTipoDeSonidad = UTN_ingresoIntReintentosMinMax(&auxiliarTipoDeSonidad, "Ingrese el tipo de sonidad (1 - ESTEREO | 0 - MONO): ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ",MIN_TIPO_SONIDAD,MAX_TIPO_SONIDAD, REINTENTOS);
				estadoIngresoCapacidadMaxima = UTN_ingresoIntReintentos(&auxiliarCapacidadMaximaDeFichas, "Ingrese la cantidad máxima de fichas: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ",REINTENTOS);
				estadoIngresoIDSalon = UTN_ingresoIntReintentos(&auxiliarIDSalon, "Ingrese la ID de salon al que pertenece: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ",REINTENTOS);
				if(estadoIngresoNacionalidad == VERDADERO && estadoIngresoNombreDelJuego == VERDADERO && estadoIngresoCantidadDeJugadores == VERDADERO && estadoIngresoTipoDeSonidad == VERDADERO && estadoIngresoCapacidadMaxima == VERDADERO && estadoIngresoIDSalon == VERDADERO){
					if(salon_verificarID(listaSalones, tamanioSalon, auxiliarIDSalon) == VERDADERO){
						if(arcade_anadirArcade(listaArcade, tamanioArcade,auxiliarNacionalidadArcade,auxiliarTipoDeSonidad,auxiliarCapacidadMaximaDeFichas,auxiliarIDSalon,auxiliarNombreDelJuego,auxiliarCantidadDeJugadores) == VERDADERO){
							printf("¡Éxito en la operación!\n");
							juegos_cargarJuegos(listaJuegos, tamanoJuegos, auxiliarNombreDelJuego);
							banderaAltaArcades = VERDADERO;
							break;
						}else{
							printf("Ha ocurrido un error inesperado en la carga de datos, vuelva al menu e intentelo de nuevo.\n");
							break;
						}
					}else{
						printf("ERROR, no se ha podido validar la ID de salón ingresada. Vuelva al menú e intentelo de nuevo.\n");
					}
				}else{
					printf("Hubo un error en el ingreso de datos, vuelva al menu e intentelo de nuevo.\n");
				}
				break;
			case 5:
				if(banderaAltaArcades == VERDADERO){
					arcade_mostrarArcadeCargados(listaArcade, tamanioArcade);
					if(UTN_ingresoIntReintentos(&auxiliarIDModificar, "Ingrese la ID del arcade que desea modificar: ", "ERROR, el valor es incorrecto, reingrese: ",REINTENTOS) == VERDADERO){
						if(arcade_encontrarEspacioPorID(listaArcade, tamanioArcade,auxiliarIDModificar ,&auxiliarEspacioModificar) == VERDADERO){
							printf("¿Que dato desea modificar?\n");
							printf("\t1-Cantidad de jugadores\n");
							printf("\t2-Juego que contiene\n");
							if(UTN_ingresoIntReintentosMinMax(&respuestaUsuarioMenuModificacion, "Ingrese su respuesta: ", "ERROR, el valor ingresado no coincide con alguna del menu, reingrese: ",MIN_MOD_MENU , MAX_MOD_MENU, REINTENTOS)){
								switch(respuestaUsuarioMenuModificacion){
								case 1:
									if(UTN_ingresoIntReintentos(&auxiliarNuevaCantidadDeJugadores, "Ingrese la nueva cantidad de jugadores: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS)){
										listaArcade[auxiliarEspacioModificar].cantidadDeJugadores = auxiliarNuevaCantidadDeJugadores;
										printf("¡Exito en la operacion!\n");
									}else{
										printf("Ha ocurrido un error ingresando la nueva cantidad, vuelva al menu e intentelo de nuevo.\n");
									}
									break;
								case 2:
									juegos_mostrarJuegosCargados(listaJuegos, tamanoJuegos);
									if(UTN_ingresoTextoReintentos(auxiliarNuevoNombreJuego,TAM_NOMBRE_JUEGO, "Ingrese el nuevo juego: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", REINTENTOS)){
										strcpy(listaArcade[auxiliarEspacioModificar].nombreDelJuego,auxiliarNuevoNombreJuego);
										juegos_cargarJuegos(listaJuegos, tamanoJuegos, auxiliarNuevoNombreJuego);
										printf("¡Exito en la operacion!\n");
									}else{
										printf("Ha ocurrido un error ingresando la nueva cantidad, vuelva al menu e intentelo de nuevo.\n");
									}
									break;
								}
							}else{
								printf("Hubo un error en la selección del menu, vuelva al menu e intentelo nuevamente\n");
							}
						}else{
							printf("No se ha encontrado la ID ingresada, vuelva al menu e intentelo nuevamente\n");
						}
					}else{
						printf("Demasiados intentos fallidos tratando de ingresar la ID, vuelva al menu e intentelo  nuevamente.\n");
					}
				}else{
					printf("Todavía no se ha hecho el alta de ningún arcade, vuelva al menú e intentelo de nuevo.\n");
				}
				break;
				case 6:
					if(banderaAltaArcades == VERDADERO){
						datosCompletos(listaSalones,tamanioSalon,listaArcade,tamanioArcade);
						if(UTN_ingresoIntReintentos(&auxiliarIDBaja, "Ingrese la ID del arcade que desea dar de baja: ", "ERROR, el valor es incorrecto, reingrese: ",REINTENTOS) == VERDADERO){
							if(arcade_encontrarEspacioPorID(listaArcade, tamanioArcade,auxiliarIDBaja ,&auxiliarEspacioBaja) == VERDADERO){
								printf("¿Esta seguro de que desea dar de baja la ID: %d? Esta acción no se puede deshacer. (1 - Confirmar | 2 - Cancelar)\n" ,listaArcade[auxiliarEspacioBaja].IDArcade);
								if(UTN_ingresoIntReintentosMinMax(&respuestaUsuarioBaja, "Ingrese su respuesta: ", "ERROR, el valor ingresado es incorrecto, reingrese: ", 1, 2, 5) == VERDADERO){
									switch(respuestaUsuarioBaja){
									case 1:
										listaArcade[auxiliarEspacioBaja].estado = LIBRE;
										listaArcade[auxiliarEspacioBaja].IDSalon = 0;
										printf("¡Exito en la operacion!\n");
										break;
									case 2:
										printf("Operacion cancelada.\n");
										break;
									}
								}else{
									printf("Hubo un error ingresando su respuesta, la operacion ha sido cancelada. Vuelva al menu e intentelo nuevamente\n");
								}

							}else{
								printf("No se ha encontrado la ID ingresada, vuelva al menu e intentelo nuevamente\n");
							}
						}else{
							printf("Demasiados intentos fallidos tratando de ingresar la ID, vuelva al menu e intentelo  nuevamente.\n");
						}
					}else{
						printf("Todavía no se ha hecho el alta de ningún arcade, vuelva al menú e intentelo de nuevo.\n");
					}
					break;
				case 7:
					arcade_mostrarArcadeCargados(listaArcade, tamanioArcade);
					break;
				case 8:
					juegos_mostrarJuegosCargados(listaJuegos, tamanoJuegos);
					break;
				case 9:
					// INFORME A
					informes_salonesConMasDeCuatroArcades(listaSalones,tamanioSalon,listaArcade,tamanioArcade);
					/* INFORME B*/
					informes_listadoDeArcadesConMasDeDosJugadores(listaSalones, tamanioSalon, listaArcade, tamanioArcade);
					/* INFORME C*/
					informes_imprimirDatosDeSalonPorID(listaSalones, tamanioSalon, listaArcade, tamanioArcade);
					/*INFORME D*/
					informes_imprimirArcadeDeSalonPorID(listaSalones, tamanioSalon, listaArcade, tamanioArcade);
					/*INFORME E - SOLUCIONAR PROBLEMA DE IGUALDAD*/
					informes_imprimirSalonConMayorCantidadDeArcades(listaSalones, tamanioSalon, listaArcade, tamanioArcade);
					/*INFORME F*/
					informes_calcularDineroTotalDeUnSalon(listaSalones, tamanioSalon, listaArcade, tamanioArcade);
					/*INFORME G*/
					informes_mostrarListaDeArcadesQueContienenElJuegoIngresado(listaArcade, tamanioArcade);
					break;
				case 10:
					printf("Fin del programa\n");
			}
		}
	}while(respuestaUsuarioMenu != 10);
}





