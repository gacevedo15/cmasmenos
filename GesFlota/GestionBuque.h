/****************************************************************************
* Cabecera: GestionBuque                                                    *
*                                                                           *
*  Contiene estructuras de datos necesarias para la gestion                 *
*  de la flota de buques.                                                   *
*****************************************************************************/

#pragma once
#include <string.h>
#include "CalendarioMes.h"

/*** Constantes que estableceran los limites de los vectores ***/
const int MAX_PUERTOS = 10;
const int MAX_BUQUES = 5;
const int MAX_NOMBRE = 21;
const int MAX_ID = 10;
const int MAX_OPERACIONES = 31;

/*** Vector de tipo char para almacenar cadena de caracteres con nombres ***/
typedef char TipoNombre[MAX_NOMBRE];

/*** Enums que contienen el tipo de producto y el tipo de puerto ***/
typedef enum TipoPuerto{noEsPuerto,yacimiento,refineria,deposito};
typedef enum TipoProducto{vacio,crudo,fuel,gasoil,gasolina};

/*** Estructura de datos: Puerto ***/
typedef struct Puerto{
  int id;
  TipoNombre nombre;
  TipoPuerto ubicacion;
};

/*** Estructura de datos: Operacion ***/
typedef struct TipoOperacion{
    int id, duracionCarga, duracionTraslado, duracionDescarga;
    TipoFecha fechaComienzoOperacion, fechaFinOperacion;
    TipoProducto productoCargado, productoDescargado;
    Puerto puertoInicio;
    Puerto puertoDestino;
};

/*** Estructura de datos: Buque ***/
typedef struct Buque{
  char id;
  TipoNombre nombre;
  TipoFecha fechaUltimaOperacion,fechaFinUltimaOperacion;
  TipoProducto productoActual;
  Puerto puertoActual;
  TipoOperacion Operaciones[MAX_OPERACIONES];
};

/*** Estructura de datos: GestionBuque (Contiene las funciones para operar con los buques y/o puertos ***
 *** y vectores de tipo Buque, Puerto y TipoOperacionesMensuales para almacenar una lista de dichos elementos) ***/
typedef struct GestionBuque{
    
   void Init();

   void EditarPuerto(int id,TipoNombre nombre,TipoPuerto tipo);
   void EstadoPuertos();
   bool PuertoDisponible(int id);

   void EditarBuque(char id,TipoNombre nombre,TipoFecha fecha, int idPuerto);
   void EstadoBuques();

   bool FechaPosterior(int id, TipoFecha fecha);

   void OperarBuque(int id, TipoFecha fecha, char & opcion);
   void CargarBuque(int id,bool & buqueCargado);
   void TrasladarBuque(int id,bool & buqueTrasladado);
   void PosibleDestino(int id,bool & esPuertoDisponible);
   void DescargarBuque(int id,bool & buqueDescargado);
   
   void ResumenOperacion(int id,bool buqueCargado,bool buqueTrasladado,bool buqueDescargado);
   void GuardarOperacion(int id,bool buqueCargado,bool buqueTrasladado,bool buqueDescargado);
   
   void PrintarCalendarioBuque(int id, TipoFecha fecha);
   int OperacionesEnMes(int id, TipoFecha fecha);
   

   private:
        int contadorOperaciones;
        Buque Buques[MAX_BUQUES];
        Puerto Puertos[MAX_PUERTOS];
        Puerto PuertosDisponibles[MAX_PUERTOS];
        TipoOperacionesMensuales listaOperacionesMensuales[MAX_OPERACIONES];
};