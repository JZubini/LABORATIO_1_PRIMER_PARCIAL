/*
 * Salon.c
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Salon.h"
#include "UTN_Ingreso.h"

#define REINTENTOS 5
#define FALSO 0
#define VERDADERO 1
#define SHOPPING 1
#define LOCAL 0
#define LIBRE 1
#define OCUPADO 0
#define MAX_TIPO_SALON 1
#define MIN_TIPO_SALON 0
#define MAX_SALONES 100
#define MIN_SALONES 1

/* Brief: a funcion se encarga de llevar un contador de ID's el cúal se va aumentando a medida que se ingresan arcades
 */

int salon_nuevaID(void){
	static int contador = 1;
	return contador++;
}

/* Brief: la funcion se encarga de inicializar la variable "estado" de todas las posiciones del array Salon en LIBRE
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 */

int salon_inicializarSalones(Salon* listaSalones,int tam){
	int retorno;
	if(listaSalones != NULL || tam > 0){
		for(int i = 0; i < tam;i++){
			listaSalones[i].estado = LIBRE;
		}
		retorno = VERDADERO;
	}else{
		retorno = FALSO;
	}
	return retorno;
}

/* Brief: la funcion se encarga de verificar que la ID recibida por parámetro existe en los datos ya cargados.
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 * Param ID: numero de ID a verificar.
 */

int salon_verificarID(Salon* listaSalones, int tam, int ID){
	int retorno = FALSO;
	if(tam > 0 && ID > 0){
		for(int i = 0;i<tam;i++){
			if(listaSalones[i].IDSalon == ID){
				retorno = VERDADERO;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de imprimir todos los salones cargados en el sistema
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 */

void salon_mostrarSalonesCargados(Salon* listaSalones,int tam){
	for(int i = 0;i<tam;i++){
		if(listaSalones[i].estado == OCUPADO){
			printf("-------------------------------------ID: %d-------------------------------------\n" ,listaSalones[i].IDSalon);
			printf("Nombre: %s\n" ,listaSalones[i].nombreDelSalon);
			printf("Dirección: %s\n" ,listaSalones[i].direccionDelSalon);
			switch(listaSalones[i].tipoDeSalon){
				case SHOPPING:
					printf("Tipo: SHOPPING\n");
					break;
				case LOCAL:
					printf("Tipo: LOCAL\n");
					break;
			}
			printf("--------------------------------------------------------------------------------\n");
		}
	}
}

/* Brief: la funcion se encarga de buscar el indice donde pertenece la ID recibida por parámetro y devolverla por puntero.
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 * Param ID: valor ID del indice que estamos buscando.
 * Param *pEspacio: puntero a la dirección de memoria donde vamos a almacenar ese índice.
 */

int salon_encontrarEspacioPorID(Salon* listaSalones, int tam, int ID, int* pEspacio){
	int i;
	int retorno = FALSO;
	if(tam > 0 && ID > 0){
		for(i = 0;i<tam;i++){
			if(listaSalones[i].IDSalon == ID){
				*pEspacio = i;
				retorno = VERDADERO;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar un índice libre donde podamos cargar datos
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 * Param *pEspacioLibre: puntero a la dirección de memoria donde vamos a almacenar ese índice.
 */

int salon_encontrarEspacioLibre(Salon* listaSalones, int tam, int* pEspacioLibre){
	int retorno = VERDADERO;
	if(listaSalones == NULL && tam < 0){
		retorno = FALSO;
	}else{
		for(int i = 0;i < tam; i++){
			if(listaSalones[i].estado == LIBRE){
				*pEspacioLibre = i;
				break;
			}
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga de encontrar cargar los datos recibidos por parámetro en el array de salones
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 * Param IDSalon: recibe el dato del IDSalon
 * Param nombreDelSalon: recibe el dato del nombre del salón
 * Param direccionDelSalon: recibe el dato del nombre del salón
 * Param tipoDeSalon: recibe el dato del tipo de salón.
 */

int salon_anadirSalon(Salon* listaSalones, int len,int IDSalon, char nombreDelSalon[TAM_DATOS_SALON], char direccionDelSalon[TAM_DATOS_SALON],int tipoDeSalon){
	int espacioLibre;
	int retorno = FALSO;
	if(salon_encontrarEspacioLibre(listaSalones, len,&espacioLibre) == VERDADERO){
		if(listaSalones != NULL && len > 0 && IDSalon >= 0 && nombreDelSalon != NULL && direccionDelSalon != NULL && tipoDeSalon > -1){
			listaSalones[espacioLibre].IDSalon = IDSalon;
			strcpy(listaSalones[espacioLibre].nombreDelSalon,nombreDelSalon);
			strcpy(listaSalones[espacioLibre].direccionDelSalon,direccionDelSalon);
			listaSalones[espacioLibre].tipoDeSalon = tipoDeSalon;
			listaSalones[espacioLibre].estado = OCUPADO;
			retorno = VERDADERO;
		}
	}else{
		printf("No hay más espacio disponible para nuevos contratos\n");
	}
	return retorno;
}

/* Brief: la funcion se encarga de solicitar los datos del arcade al usuario y verificar que el ingreso sea correcto.
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 */

int salon_cargarSalones(Salon* listaSalones, int tam){
	int auxiliarID;
	char auxiliarNombreDelSalon[TAM_DATOS_SALON];
	char auxiliarDireccionDelSalon[TAM_DATOS_SALON];
	int auxiliarTipoDeSalon;
	int estadoIngresoNombre;
	int estadoIngresoDireccion;
	int estadoIngresoTipo;
	int retorno;
	if(listaSalones != NULL && tam > 0){
		auxiliarID = salon_nuevaID();
		printf("------------------------ID salon: %d------------------------\n" ,auxiliarID);
		estadoIngresoNombre = UTN_ingresoTextoReintentos(auxiliarNombreDelSalon, tam, "Ingrese el nombre del salon: ", "ERROR, el dato ingresado es incorrecto, reingrese a continuacion: ", REINTENTOS);
		estadoIngresoDireccion = UTN_ingresoTextoReintentos(auxiliarDireccionDelSalon, tam, "Ingrese la direccion del salon: ", "ERROR, el dato ingresado es incorrecto, reingrese a continuacion: ", REINTENTOS);
		estadoIngresoTipo = UTN_ingresoIntReintentosMinMax(&auxiliarTipoDeSalon, "Ingrese el tipo de salon (1 - Shopping | 0 - LOCAL): ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ",MIN_TIPO_SALON,MAX_TIPO_SALON, REINTENTOS);
		if(estadoIngresoNombre == VERDADERO && estadoIngresoDireccion == VERDADERO && estadoIngresoTipo == VERDADERO){
			if(salon_anadirSalon(listaSalones, tam,auxiliarID,auxiliarNombreDelSalon,auxiliarDireccionDelSalon,auxiliarTipoDeSalon) == VERDADERO){
				printf("¡Éxito en la operación!\n");
				retorno = VERDADERO;
			}else{
				printf("Ha ocurrido un error inesperado en la carga de datos, vuelva al menu e intentelo de nuevo.\n");
				retorno = FALSO;
			}
		}else{
			printf("Hubo un error en el ingreso de datos, vuelva al menu e intentelo de nuevo.\n");
			retorno = FALSO;
		}
	}
	return retorno;
}

/* Brief: la funcion se encarga
 * Param listaSalones: lista de salones
 * Param tam: tamaño del array
 * Param pIndiceBaja: puntero a dirección de memoria donde vamos a almacenar el índice del salón para utilizarla en otra función.
 */

int salon_bajaSalon(Salon* listaSalones, int tam, int* pIndiceBaja){
	int espacioBaja;
	int IDSalonSeleccionado;
	int retorno = FALSO;
	salon_mostrarSalonesCargados(listaSalones, tam);
	if(UTN_ingresoIntReintentosMinMax(&IDSalonSeleccionado, "Ingrese la ID del salon que desea dar de baja: ", "ERROR, el valor ingresado es incorrecto, reingrese a continuacion: ", MIN_SALONES, MAX_SALONES, REINTENTOS) == VERDADERO){
		if(salon_encontrarEspacioPorID(listaSalones,tam,IDSalonSeleccionado,&espacioBaja) == VERDADERO){
			*pIndiceBaja = espacioBaja;
			listaSalones[espacioBaja].estado = LIBRE;
			retorno = VERDADERO;
		}else{
			printf("No sea ha podido encontrar el ID ingresado, por favor vuelva al menú e intentelo de nuevo.\n");
		}
	}else{
		printf("Ha ocurrido un error en el ingreso de datos, regrese al menú e intentelo nuevamente\n");
	}
	return retorno;
}

