/****************************************************************************
* Cabecera: CalendarioMes                                                   *
*                                                                           *
* Contiene estructuras de datos necesarias para la gestion                  *
* del calendario.                                                           *
*****************************************************************************/

#pragma once
#include <stdio.h>
#include <ctype.h>

/*** Estructura de datos: TipoOperacionesMensuales ***
 *** Contiene las variables necesarias para almacenar las operaciones realizadas de un buque durante un mes ***
 *** y poder printarlas en el calendario ***/
typedef struct TipoOperacionesMensuales{
    int id, duracionCarga, duracionTraslado, duracionDescarga;
    int diaComienzoOperacion, mesComienzoOperacion, annoComienzoOperacion;
    int diaFinOperacion, mesFinOperacion, annoFinOperacion;
    
    int duracionTotal();
};

/*** Estructura de datos: TipoFecha ***
 *** Contiene las variables y funciones necesarias para operar con el calendario***/
typedef struct TipoFecha{
    int dia, mes, anno;

    bool bisiesto(int anno);
    int SumarDias(int dia, int num);
    int DiaDeLaSemana(int mes, int anno);

    bool FechaCorrecta();
    
    void PrintarFecha(TipoFecha fecha);
    void PrintarMesString(int mes);
    
    void PrintarCalendario(int cantOperaciones, TipoOperacionesMensuales listaOperaciones[], TipoFecha fecha);
    
    int DiasDelMes(int mes,int anno);
};






