/*
 * Salon.h
 *
 *  Created on: 16 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef SALON_H_
#define SALON_H_

#define TAM_DATOS_SALON 100


typedef struct{
	int IDSalon;
	char nombreDelSalon[TAM_DATOS_SALON];
	char direccionDelSalon[TAM_DATOS_SALON];
	int tipoDeSalon;
	int estado;
}Salon;

int salon_verificarID(Salon* listaSalones, int tam, int ID);
void salon_mostrarSalonesCargados(Salon* listaSalones,int tam);
int salon_cargarSalones(Salon* listaSalones, int tam);
int salon_bajaSalon(Salon* listaSalones, int tam, int* pIndiceBaja);
int salon_inicializarSalones(Salon* listaSalones,int tam);
int salon_encontrarEspacioPorID(Salon* listaSalones, int tam, int ID, int* pEspacio);

#endif /* SALON_H_ */
