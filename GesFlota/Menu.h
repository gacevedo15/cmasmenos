/****************************************************************************
* Cabecera: Menu                                                            *
*                                                                           *
* Contiene estructuras de datos necesarias para la gestion                  *
* de los diferentes tipos de Menus.                                         *
*****************************************************************************/

#pragma once
#include "GestionBuque.h"

/*** Estructura de dato: TipoMenu ***
 *** Contiene las funciones que mostrarán los distintos tipos de Menu, los cuales llamarán a las funciones necesarias ***
 *** para la gestión de la Flota ***/
typedef struct TipoMenu{
  
  void MenuInit();

  void MenuPrincipal();

  void MenuEditarPuerto();
  void MenuEditarBuque();
  void MenuEstadoBuques();
  void MenuOperarBuque();
  void MenuResumenMensualBuque();

  private:
    char opcion, idBuque, temp;
    int idPuerto;
    TipoNombre nombre;
    TipoPuerto tipo;
    TipoFecha fecha;
    GestionBuque gestion;
};
