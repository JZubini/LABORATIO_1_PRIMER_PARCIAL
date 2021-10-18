/*
 * Informes.h
 *
 *  Created on: 17 oct. 2021
 *      Author: Julián Zubini
 */

#ifndef INFORMES_H_
#define INFORMES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Informes.h"
#include "Salon.h"
#include "Arcade.h"
#include "Juegos.h"

int informes_salonesConMasDeCuatroArcades(Salon* listaSalones, int tamanioSalones,Arcade* listaArcades, int tamanioArcades);
int informes_listadoDeArcadesConMasDeDosJugadores(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades);
int informes_imprimirDatosDeSalonPorID(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades);
int informes_imprimirArcadeDeSalonPorID(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades);
int informes_imprimirSalonConMayorCantidadDeArcades(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades);
int informes_calcularDineroTotalDeUnSalon(Salon* listaSalones, int tamanioSalones, Arcade* listaArcades, int tamanioArcades);
int informes_mostrarListaDeArcadesQueContienenElJuegoIngresado(Arcade* listaArcades, int tamanioArcades);

#endif /* INFORMES_H_ */
