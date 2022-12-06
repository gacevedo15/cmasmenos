/*****************************************************************************
* Modulo: GestionBuque                                                       *
*                                                                            *
*  Contiene el desarrollo de las estructuras de datos y funciones necesarias *
*  para la gestion de la flota de buques.                                    *
******************************************************************************/

#include "GestionBuque.h"

/*** Funcion para inicializar la lista de puertos y buques por defecto ***/
void GestionBuque::Init(){
  /*** Inicializamos los puertos, por defecto tendrán un id del 1 al 10, de nombre "PuertoSinNombre" y ubicacion "noEsPuerto" ***/
  for(int i=0;i<MAX_PUERTOS;i++){
      Puertos[i].id=i+1;
      strcpy(Puertos[i].nombre, "PuertoSinNombre");
      Puertos[i].ubicacion=noEsPuerto;
  }

  /*** Inicializamos los buques, por defecto tendrán un id de 'A' a 'E', de nombre "BuqueSinNombre", fechaUltimaOperacion y ***
   *** fechaFinUltimaOperacion serán 01/01/2020, productoActual estará "vacio" y el puerto actual tendrá id 0, nombre ***
   *** "PuertoSinNombre" y ubicación "noEsPuerto" ***/
  for(int i=0;i<MAX_BUQUES;i++){
      /*** Utilizamos switch case para asignar el id tipo char ***/
      switch(i){
        case 0:
          Buques[i].id='A';
          break;
        case 1:
          Buques[i].id='B';
          break;
        case 2:
          Buques[i].id='C';
          break;
        case 3:
          Buques[i].id='D';
          break;
        case 4:
          Buques[i].id='E';
          break;
      }

      strcpy(Buques[i].nombre, "BuqueSinNombre");

      Buques[i].fechaUltimaOperacion.dia=1;
      Buques[i].fechaUltimaOperacion.mes=1;
      Buques[i].fechaUltimaOperacion.anno=2020;

      Buques[i].fechaFinUltimaOperacion.dia=1;
      Buques[i].fechaFinUltimaOperacion.mes=1;
      Buques[i].fechaFinUltimaOperacion.anno=2020;

      Buques[i].productoActual=vacio;

      Buques[i].puertoActual.id=0;
      strcpy(Buques[i].puertoActual.nombre, "PuertoSinNombre");
      Buques[i].puertoActual.ubicacion=noEsPuerto;
  }

  /*** Inicializamos a 0 el contadorOperaciones, que se utilizará posteriormente para recorrer todas las operaciones que ***
   *** contenga un buque del vector de Buques ***/
  contadorOperaciones=0;
}

/*** Funcion para editar el puerto seleccionado ***/
void GestionBuque::EditarPuerto(int id,TipoNombre nombre,TipoPuerto tipo){
  strcpy(Puertos[id-1].nombre, nombre);
  Puertos[id-1].ubicacion=tipo;
}

/*** Funcion para printar el estado de los puertos disponibles ***/
void GestionBuque::EstadoPuertos(){
  for(int i=0;i<MAX_PUERTOS;i++){
      switch(Puertos[i].ubicacion){
        case yacimiento:
          printf("%16d - %-20s Tipo: Yacimiento\n",Puertos[i].id,Puertos[i].nombre);
          break;
        case refineria:
          printf("%16d - %-20s Tipo: Refineria\n",Puertos[i].id,Puertos[i].nombre);
          break;
        case deposito:
          printf("%16d - %-20s Tipo: Deposito\n",Puertos[i].id,Puertos[i].nombre);
          break;
      }
  }
}

/*** Fucnion para comprobar si el puerto seleccionado esta disponible ***/
bool GestionBuque::PuertoDisponible(int id){
  for(int i=0;i<MAX_PUERTOS;i++){
    if(Puertos[i].id==id){
      if(Puertos[i].ubicacion==noEsPuerto){
        return false;
      }else{
        return true;
      }
    }
  }
}

/*** Funcion para editar el buque seleccionado ***/
void GestionBuque::EditarBuque(char id,TipoNombre nombre,TipoFecha fecha, int idPuerto){
  int posBuques;            //Variable auxiliar para editar el buque del vector de Buques en la posicion de char id
  switch(toupper(id)){
    case 'A':
      posBuques=0;
      break;
    case 'B':
      posBuques=1;
      break;
    case 'C':
      posBuques=2;
      break;
    case 'D':
      posBuques=3;
      break;
    case 'E':
      posBuques=4;
      break;
  }
  strcpy(Buques[posBuques].nombre, nombre);
  Buques[posBuques].fechaUltimaOperacion.dia=fecha.dia;
  Buques[posBuques].fechaUltimaOperacion.mes=fecha.mes;
  Buques[posBuques].fechaUltimaOperacion.anno=fecha.anno;

  Buques[posBuques].fechaFinUltimaOperacion.dia=fecha.dia;
  Buques[posBuques].fechaFinUltimaOperacion.mes=fecha.mes;
  Buques[posBuques].fechaFinUltimaOperacion.anno=fecha.anno;

  Buques[posBuques].puertoActual.id=Puertos[idPuerto-1].id;
  strcpy(Buques[posBuques].puertoActual.nombre, Puertos[idPuerto-1].nombre);
  Buques[posBuques].puertoActual.ubicacion=Puertos[idPuerto-1].ubicacion;
}

/*** Funcion para printar el estado de los Buques ***/
void GestionBuque::EstadoBuques(){
  printf("           Estado Buques\n\n");
  printf("Id   Nombre               Puerto               Ultima Fecha      Carga\n\n");
  for(int i=0;i<MAX_BUQUES;i++){
    /*** Evaluamos que el buque se haya editado ya y que no contenga de nombre "BuqueSinNombre" ***/
    if((strcmp(Buques[i].nombre, "BuqueSinNombre"))!=0){
      printf("%c    %-20s %-20s ",Buques[i].id,Buques[i].nombre,Buques[i].puertoActual.nombre);

      /*** Con la función "PrintarFecha" printamos la fecha con formato dd/mm/aaaa ***/
      Buques[i].fechaUltimaOperacion.PrintarFecha(Buques[i].fechaUltimaOperacion);

      /*** Printamos el tipo de producto ***/
      switch(Buques[i].productoActual){
        case vacio:
          printf("        Vacio\n");
          break;
        case crudo:
          printf("        Crudo\n");
          break;
        case fuel:
          printf("        Fuel\n");
          break;
        case gasoil:
          printf("        Gasoil\n");
          break;
        case gasolina:
          printf("        Gaslina\n");
          break;
      }
    }
  }
  printf("\n");
}

/*** Funcion para asegurarnos de que las operaciones con los buques sean posteriores o iguales a su fecha de inicio ***/
bool GestionBuque::FechaPosterior(int id, TipoFecha fecha){
  if((fecha.anno)>(Buques[id].fechaFinUltimaOperacion.anno)){
    return true;
  }else if((fecha.anno)==(Buques[id].fechaFinUltimaOperacion.anno)){
    if((fecha.mes)<(Buques[id].fechaFinUltimaOperacion.mes)){
        return false;
    }else if((fecha.mes)==(Buques[id].fechaFinUltimaOperacion.mes)){
        if((fecha.dia)>=(Buques[id].fechaFinUltimaOperacion.dia)){
            return true;
        }else{
            return false;
        }
    }else{
        return true;
    }
  }else{
      return false;
  }
}

/*** Funcion para Operar con los buques ***/
void GestionBuque::OperarBuque(int id, TipoFecha fecha, char & opcion){
  bool buqueCargado,buqueTrasladado,buqueDescargado;        //Variables auxiliares que almacenarán para cada operación si el
                                                            //buque ha sido cargado/trasladado/descargado
  buqueCargado = false;
  buqueTrasladado= false;
  buqueDescargado= false;

  /*** Evaluamos que la fecha sea posterior a la fecha de finalización de la última operación ***/
  if(FechaPosterior(id,fecha)){

    /*** Evaluamos que el buque se haya editado ya y que no contenga de nombre "BuqueSinNombre" ***/
    if((strcmp(Buques[id].nombre, "BuqueSinNombre"))!=0){

      /*** Copiamos al array de operaciones en la posición actual los valores necesarios para comenzar a operar ***/
      /*** Copiamos el id ***/
      Buques[id].Operaciones[contadorOperaciones].id=contadorOperaciones+1;

      /*** Copiamos la fecha ***/
      Buques[id].Operaciones[contadorOperaciones].fechaComienzoOperacion=fecha;

      /*** Copiamos el producto ***/
      Buques[id].Operaciones[contadorOperaciones].productoCargado=Buques[id].productoActual;

      /*** Copiamos el puerto de inicio ***/
      Buques[id].Operaciones[contadorOperaciones].puertoInicio.id=Buques[id].puertoActual.id;
      strcpy(Buques[id].Operaciones[contadorOperaciones].puertoInicio.nombre, Buques[id].puertoActual.nombre);
      Buques[id].Operaciones[contadorOperaciones].puertoInicio.ubicacion=Buques[id].puertoActual.ubicacion;

      /*** Copiamos el puerto de destino ***/
      Buques[id].Operaciones[contadorOperaciones].puertoDestino.id=Buques[id].puertoActual.id;
      strcpy(Buques[id].Operaciones[contadorOperaciones].puertoDestino.nombre, Buques[id].puertoActual.nombre);
      Buques[id].Operaciones[contadorOperaciones].puertoDestino.ubicacion=Buques[id].puertoActual.ubicacion;

      /*** En dependencia del producto que contenga el buque, procederemos a llamar a las funciones que realizarán ***
       *** la carga/traslado/descarga ***/
      switch(Buques[id].productoActual){

        /*** Si está vacío, se podrá cargar y evaluar si es posible trasladar o descargar ***/
        case vacio:
          printf("\n       El buque %s esta vacio en %s\n",Buques[id].nombre,Buques[id].puertoActual.nombre);
          CargarBuque(id,buqueCargado);
          TrasladarBuque(id,buqueTrasladado);
          DescargarBuque(id,buqueDescargado);
          break;

        /*** Si está cargado de crudo, ya no se podrá realizar la carga, por lo que evaluaremos solo el traslado y la descarga ***/
        case crudo:
          printf("\n       El buque %s esta cargado de crudo en %s\n",Buques[id].nombre,Buques[id].puertoActual.nombre);
          buqueCargado=false;
          TrasladarBuque(id,buqueTrasladado);
          DescargarBuque(id,buqueDescargado);
          break;

        /*** Si está cargado de fuel, ya no se podrá realizar la carga, por lo que evaluaremos solo el traslado y la descarga ***/
        case fuel:
          printf("\n       El buque %s esta cargado de fuel en %s\n",Buques[id].nombre,Buques[id].puertoActual.nombre);
          buqueCargado=false;
          TrasladarBuque(id,buqueTrasladado);
          DescargarBuque(id,buqueDescargado);
          break;

        /*** Si está cargado de gasoil, ya no se podrá realizar la carga, por lo que evaluaremos solo el traslado y la descarga ***/
        case gasoil:
          printf("\n       El buque %s esta cargado de gasoil en %s\n",Buques[id].nombre,Buques[id].puertoActual.nombre);
          buqueCargado=false;
          TrasladarBuque(id,buqueTrasladado);
          DescargarBuque(id,buqueDescargado);
          break;

        /*** Si está cargado de gasolina, ya no se podrá realizar la carga, por lo que evaluaremos solo el traslado y la descarga ***/
        case gasolina:
          printf("\n       El buque %s esta cargado de gasolina en %s\n",Buques[id].nombre,Buques[id].puertoActual.nombre);
          buqueCargado=false;
          TrasladarBuque(id,buqueTrasladado);
          DescargarBuque(id,buqueDescargado);
          break;
      }

      /*** Una vez se haya terminado de realizar la operación deseada con el buque, mostraremos un resumen con la funcion ***
       *** ResumenOperacion(id,buqueCargado,buqueTrasladado,buqueDescargado) ***/
      ResumenOperacion(id,buqueCargado,buqueTrasladado,buqueDescargado);

      /*** Si se ha llevado a cabo al menos 1 de las 3 posibles operaciones (cargar/trasladar/descargar) preguntaremos si es ***
       *** correcta la operación, si es correcta, la guardaremos con la función "GuardarOperacion". Si no es correcta o ***
       *** si no se ha llevado a cabo ninguna de las operaciones, salimos al MenuPrincipal ***/
      if(buqueCargado||buqueTrasladado||buqueDescargado){
          printf("\nEs correcta la operacion (S/N)? ");
          scanf(" %c",&opcion);
          fflush(stdin);
          switch(toupper(opcion)){
              case 'S':
                GuardarOperacion(id,buqueCargado,buqueTrasladado,buqueDescargado);
                printf("       Operacion realizada con exito\n");
                break;
              default:
                Buques[id].fechaFinUltimaOperacion=fecha;
                opcion='N';
          }
      }else{
          printf("\n       No se ha realizado ninguna operacion con este buque\n\n");
      }
    }else{
      printf("\n       ERROR: El buque seleccionado no existe\n\n");
    }
  }else{
    printf("\n       ERROR: La fecha debe ser igual o posterior a la fecha de la ultima operacion del Buque: ");
    Buques[id].fechaFinUltimaOperacion.PrintarFecha(Buques[id].fechaFinUltimaOperacion);
    printf("\n\n");
  }
}

/*** Funcion para cargar el buque ***/
void GestionBuque::CargarBuque(int id, bool & buqueCargado){
  int dia;                     //Variable auxiliar para pedir la duración de la carga en dias
  int opcionProducto;          //Variable auxiliar para elegir producto refinado
  char opcion;

  /*** En dependencia de la ubicación del puerto actual se cargar de un producto u otro ***/
  switch(Buques[id].puertoActual.ubicacion){

    /*** En Yacimiento se puede cargar Crudo ***/
    case yacimiento:
      printf("       Se puede cargar: Crudo\n");
      printf("       Quiere realizar la carga(S/N) ");
      scanf(" %c",&opcion);
      fflush(stdin);
        switch(toupper(opcion)){
          case 'S':
            printf("       Duracion de la carga en dias? ");
            scanf(" %d",&dia);
            fflush(stdin);

            /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
             *** es de 20 días ***/
            if(dia>0&&dia<21){
                Buques[id].Operaciones[contadorOperaciones].productoCargado=crudo;
                Buques[id].Operaciones[contadorOperaciones].duracionCarga=dia;
                buqueCargado=true;
            }else{
                printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                buqueCargado=false;
            }
            break;
          default:
            printf("\n       El buque %s no ha sido cargado\n\n",Buques[id].nombre);
            buqueCargado=false;
        }
      break;

    /*** En Refineria y Deposito se puede cargar Fuel, Gasoil o Gasolina ***/
    case refineria:
    case deposito:
      printf("       Se puede cargar: Fuel, Gasoil o Gasolina\n");
      printf("       Quiere realizar la carga(S/N) ");
      scanf(" %c",&opcion);
      fflush(stdin);
        switch(toupper(opcion)){
          case 'S':
            printf("       Producto a cargar(1-Fuel, 2-Gasoil, 3-Gasolina)? ");
            scanf(" %d",&opcionProducto);
            fflush(stdin);
              /*** Nos aseguramos con switch case que solo sea elegida una de las opciones permitidas (del 1 al 3) ***/
              switch(opcionProducto){

                /*** Fuel ***/
                case 1:
                    printf("       Duracion de la carga en dias? ");
                    scanf(" %d",&dia);
                    fflush(stdin);

                    /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
                     *** es de 20 días ***/
                    if(dia>0&&dia<21){
                        Buques[id].Operaciones[contadorOperaciones].productoCargado=fuel;
                        Buques[id].Operaciones[contadorOperaciones].duracionCarga=dia;
                        buqueCargado=true;
                    }else{
                        printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                        buqueCargado=false;
                    }
                  break;

                /*** Gasoil ***/
                case 2:
                    printf("       Duracion de la carga en dias? ");
                    scanf(" %d",&dia);
                    fflush(stdin);

                    /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
                     *** es de 20 días ***/
                    if(dia>0&&dia<28){
                        Buques[id].Operaciones[contadorOperaciones].productoCargado=gasoil;
                        Buques[id].Operaciones[contadorOperaciones].duracionCarga=dia;
                        buqueCargado=true;
                    }else{
                        printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                        buqueCargado=false;
                    }
                  break;

                /*** Gasolina ***/
                case 3:
                    printf("       Duracion de la carga en dias? ");
                    scanf(" %d",&dia);
                    fflush(stdin);

                    /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
                     *** es de 20 días ***/
                    if(dia>0&&dia<28){
                        Buques[id].Operaciones[contadorOperaciones].productoCargado=gasolina;
                        Buques[id].Operaciones[contadorOperaciones].duracionCarga=dia;
                        buqueCargado=true;
                    }else{
                        printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                        buqueCargado=false;
                    }
                  break;
                default:
                  printf("\nERROR: Producto incorrecto\n");
                  buqueCargado=false;
              }
            break;
          default:
            printf("\nERROR: El buque %s no ha sido cargado\n",Buques[id].nombre);
            buqueCargado=false;
        }
      break;
  }
}

/*** Funcion para trasladar el buque ***/
void GestionBuque::TrasladarBuque(int id, bool & buqueTrasladado){
  int dia;                                      //Variable auxiliar para pedir la duración de la carga en dias
  int opcionProducto, opcionPuerto;             //Variables auxiliares donde almacenaremos la opción de producto y puerto elegido
  bool esPuertoDisponible;                      //Variable auxiliar para indicar si el puerto elegido está disponible
  char opcion;

  esPuertoDisponible=false;

    printf("\n       Quiere realizar el traslado(S/N) ");
    scanf(" %c",&opcion);
    fflush(stdin);
    if(toupper(opcion)=='S'){
      printf("       Puertos de posible destino del buque:\n");

      /*** Con la función PosibleDestino recorreremos todos los puertos y almacenaremos en el array de PuertosDisponibles ***
       *** los posibles puertos de destino a los que se puede trasladar el buque, teniendo en cuenta el tipo de carga y que ***
       *** y que no sea el mismo puerto de inicio ***/
      PosibleDestino(id,esPuertoDisponible);

      /*** En el caso de que hayan puertos disponibles pediremos el id y la duración del traslado en días ***/
      if(esPuertoDisponible){
          printf("       Identificador del puerto destino? ");
          scanf(" %d",&opcionPuerto);
          fflush(stdin);

          /*** Recorremos la lista de puertos disponibles para comprobar si el id introducido corresponde a alguno de ellos, ***
           *** en caso contrario, indicaremos que el puerto seleccionado no está disponible ***/
          for(int i=0;i<MAX_PUERTOS;i++){
              if(PuertosDisponibles[i].id==opcionPuerto){
                  printf("       Duracion del traslado en dias? ");
                  scanf(" %d",&dia);
                  fflush(stdin);

                  /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
                   *** es de 20 días ***/
                  if(dia>0&&dia<21){
                        Buques[id].Operaciones[contadorOperaciones].puertoDestino.id=PuertosDisponibles[i].id;
                        strcpy(Buques[id].Operaciones[contadorOperaciones].puertoDestino.nombre, PuertosDisponibles[i].nombre);
                        Buques[id].Operaciones[contadorOperaciones].puertoDestino.ubicacion=PuertosDisponibles[i].ubicacion;
                        Buques[id].Operaciones[contadorOperaciones].duracionTraslado=dia;
                        buqueTrasladado=true;
                  }else{
                        printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                        buqueTrasladado=false;
                  }
              }
          }
      }else{
          printf("\n       No hay puertos disponibles\n\n");
      }
    }else{
      printf("\n       Traslado no realizado\n\n");
    }
}

/*** Función para printar los posibles destinos de traslado del buque ***/
void GestionBuque::PosibleDestino(int id, bool & esPuertoDisponible){
    int contador=0;     //Variable auxiliar para almacenar en el array de PuertosDisponibles los puertos que puedan ser seleccionados

    /*** Recorremos todos los puertos ***/
    for(int i=0;i<MAX_PUERTOS;i++){

        /*** Para tener en cuenta si un puerto está disponible, la ubicación tiene que ser distinta a "noEsPuerto" y ***
         *** el id no puede ser el mismo que el id actual, puesto que no es posible trasladarse al mismo puerto en el ***
         *** que se encuentra ***/
        if(Puertos[i].ubicacion!=noEsPuerto&&(Buques[id].puertoActual.id!=Puertos[i].id)){

            /*** También hay que tener en cuenta que solo sea posible trasladar a un puerto donde sea posible realizar ***
             *** la descarga del producto que contenga el buque ***/
            switch(Buques[id].Operaciones[contadorOperaciones].productoCargado){

                /*** Si está vacío puede ir a cualquier puerto ***/
                case vacio:
                    switch(Puertos[i].ubicacion){
                        case yacimiento:
                            printf("%15d - %-20s Tipo: Yacimiento\n",Puertos[i].id,Puertos[i].nombre);
                            esPuertoDisponible=true;
                            PuertosDisponibles[contador].id=Puertos[i].id;
                            strcpy(PuertosDisponibles[contador].nombre, Puertos[i].nombre);
                            PuertosDisponibles[contador].ubicacion=Puertos[i].ubicacion;
                            contador++;
                            break;
                        case refineria:
                            printf("%15d - %-20s Tipo: Refineria\n",Puertos[i].id,Puertos[i].nombre);
                            esPuertoDisponible=true;
                            PuertosDisponibles[contador].id=Puertos[i].id;
                            strcpy(PuertosDisponibles[contador].nombre, Puertos[i].nombre);
                            PuertosDisponibles[contador].ubicacion=Puertos[i].ubicacion;
                            contador++;
                            break;
                        case deposito:
                            printf("%15d - %-20s Tipo: Deposito\n",Puertos[i].id,Puertos[i].nombre);
                            esPuertoDisponible=true;
                            PuertosDisponibles[contador].id=Puertos[i].id;
                            strcpy(PuertosDisponibles[contador].nombre, Puertos[i].nombre);
                            PuertosDisponibles[contador].ubicacion=Puertos[i].ubicacion;
                            contador++;
                            break;
                    }
                    break;

                /*** Si contiene crudo puede ir a cualquier Refinería ***/
                case crudo:
                    if(Puertos[i].ubicacion==refineria){
                        printf("%15d - %-20s Tipo: Refineria\n",Puertos[i].id,Puertos[i].nombre);
                        esPuertoDisponible=true;
                        PuertosDisponibles[contador].id=Puertos[i].id;
                        strcpy(PuertosDisponibles[contador].nombre, Puertos[i].nombre);
                        PuertosDisponibles[contador].ubicacion=Puertos[i].ubicacion;
                        contador++;
                    }
                    break;

                /*** Si contiene productos refinados (fuel, gasoil, gasolina) puede ir a cualquier Depósito ***/
                case fuel:
                case gasoil:
                case gasolina:
                    if(Puertos[i].ubicacion==deposito){
                        printf("%15d - %-20s Tipo: Deposito\n",Puertos[i].id,Puertos[i].nombre);
                        esPuertoDisponible=true;
                        PuertosDisponibles[contador].id=Puertos[i].id;
                        strcpy(PuertosDisponibles[contador].nombre, Puertos[i].nombre);
                        PuertosDisponibles[contador].ubicacion=Puertos[i].ubicacion;
                        contador++;
                    }
                    break;
            }
        }
    }
}

/*** Función para descargar el buque ***/
void GestionBuque::DescargarBuque(int id,bool & buqueDescargado){
    int dia;                        //Variable auxiliar para pedir la duración de la carga en dias
    char opcion;

    printf("\n       Quiere realizar la descarga (S/N)? ");
    scanf(" %c",&opcion);
    fflush(stdin);
    if(toupper(opcion)=='S'){

        /*** Para descargar el buque, nos tenemos que asegurar de que no esté vacío y que no se pueda realizar la descarga ***
         *** en el mismo puerto donde fue cargado ***/
        if((Buques[id].Operaciones[contadorOperaciones].productoCargado!=vacio)&&(Buques[id].Operaciones[contadorOperaciones].puertoInicio.id!=Buques[id].Operaciones[contadorOperaciones].puertoDestino.id)){
            printf("       Duracion de la descarga en dias? ");
            scanf(" %d",&dia);
            fflush(stdin);

            /*** Para el correcto funcionamiento establecemos que el máximo de días que puede estar cargando el buque ***
             *** es de 20 días ***/
            if(dia>0&&dia<21){
                Buques[id].Operaciones[contadorOperaciones].productoDescargado=vacio;
                Buques[id].Operaciones[contadorOperaciones].duracionDescarga=dia;
                buqueDescargado=true;
            }else{
                printf("\n       ERROR: Los dias deben estar comprendidos entre 1 y 20\n\n");
                buqueDescargado=false;
            }
        }else{
            if(Buques[id].Operaciones[contadorOperaciones].productoCargado==vacio){
                printf("\n       ERROR: No se puede realizar la descarga porque el buque esta vacio\n\n");
            }else{
                printf("\n       ERROR: No se puede realizar la descarga en el mismo puerto que se ha cargado\n\n");
            }
        }
    }else{
        printf("\n       Descarga no realizada\n\n");
    }
}

/*** Función para printar el resumen de la operación ***/
void GestionBuque::ResumenOperacion(int id,bool buqueCargado,bool buqueTrasladado,bool buqueDescargado){
    printf("              Resumen de la operacion:\n");
    printf("       Fecha comienzo: ");
    Buques[id].Operaciones[contadorOperaciones].fechaComienzoOperacion.PrintarFecha(Buques[id].Operaciones[contadorOperaciones].fechaComienzoOperacion);
    printf("\n");
    printf("       Puerto origen: %s\n",Buques[id].Operaciones[contadorOperaciones].puertoInicio.nombre);
    switch(Buques[id].Operaciones[contadorOperaciones].productoCargado){
        case vacio:
            printf("       Tipo de carga: Vacio\n");
            break;
        case crudo:
            printf("       Tipo de carga: Crudo\n");
            break;
        case fuel:
            printf("       Tipo de carga: Fuel\n");
            break;
        case gasoil:
            printf("       Tipo de carga: Gasoil\n");
            break;
        case gasolina:
            printf("       Tipo de carga: Gasolina\n");
            break;
    }

    /*** Se mostrará por pantalla la duración de la operación (carga/traslado/descarga) solo si se ha llevado a cabo la misma ***
     *** En el caso del traslado, también se mostrará el puerto de destino ***/
    if(buqueCargado){
        printf("       Duracion carga: %d dias\n",Buques[id].Operaciones[contadorOperaciones].duracionCarga);
    }
    if(buqueTrasladado){
        printf("       Puerto destino: %s\n",Buques[id].Operaciones[contadorOperaciones].puertoDestino.nombre);
        printf("       Duracion del traslado: %d dias\n",Buques[id].Operaciones[contadorOperaciones].duracionTraslado);
    }
    if(buqueDescargado){
        printf("       Duracion de la descarga: %d dias\n",Buques[id].Operaciones[contadorOperaciones].duracionDescarga);
    }
}

/*** Función para aplicar la operación en caso de ser correctos los datos ***/
void GestionBuque::GuardarOperacion(int id,bool buqueCargado,bool buqueTrasladado,bool buqueDescargado){
    int diaCarga, diaTraslado, diaDescarga;             //Variables auxiliares para almacenar la cantidad de dias de carga/traslado/descarga
    int diasDelMes;                                     //Varable auxiliar que contendrá la cantidad de días que tiene un mes del calendario

    TipoFecha inicioOperacion, finOperacion;            //Variables auxiliares de TipoFecha para guardar el inicio y fin de una operación

    /*** Inicializamos las variables inicioOperacion y finOperacion con la fecha de comienzo de la operación ***/
    inicioOperacion=Buques[id].Operaciones[contadorOperaciones].fechaComienzoOperacion;
    finOperacion=Buques[id].Operaciones[contadorOperaciones].fechaComienzoOperacion;

    /*** La fechaUltimaOperacion del Buque será la fecha de inicio de la operación actual ***/
    Buques[id].fechaUltimaOperacion=inicioOperacion;

    /*** Inicializamos la variable diasDelMes, la cual almacenará los días del mes en el cual se realiza la operación ***/
    diasDelMes=inicioOperacion.DiasDelMes(inicioOperacion.mes,inicioOperacion.anno);

    /*** Asignamos valor a la variable que almacena los dias de carga ***/
    if(buqueCargado){
        diaCarga=Buques[id].Operaciones[contadorOperaciones].duracionCarga;
    }else{
        diaCarga=0;
    }

    /*** Asignamos valor a la variable que almacena los dias de traslado y almacenamos como puerto actual del buque el puerto ***
     *** de destino de la operación, en caso de que se realice un traslado ***/
    if(buqueTrasladado){
        Buques[id].puertoActual.id=Buques[id].Operaciones[contadorOperaciones].puertoDestino.id;
        strcpy(Buques[id].puertoActual.nombre, Buques[id].Operaciones[contadorOperaciones].puertoDestino.nombre);
        Buques[id].puertoActual.ubicacion=Buques[id].Operaciones[contadorOperaciones].puertoDestino.ubicacion;
        diaTraslado=Buques[id].Operaciones[contadorOperaciones].duracionTraslado;
    }else{
        diaTraslado=0;
    }

    /*** Asignamos valor a la variable que almacena los dias de descarga y almacenamos en el buque el producto actual, para ello ***
     *** evaluamos si se realizó la descarga ***/
    if(buqueDescargado){
        Buques[id].productoActual=Buques[id].Operaciones[contadorOperaciones].productoDescargado;
        diaDescarga=Buques[id].Operaciones[contadorOperaciones].duracionDescarga;
    }else{
        Buques[id].productoActual=Buques[id].Operaciones[contadorOperaciones].productoCargado;
        diaDescarga=0;
    }

    /*** la fecha final de operación = inicio(-1) + dias de carga + dias de traslado + dias de descarga ***
     *** se le resta 1 debido a que en el mismo dia de inicio de la operación es cuando se realiza la ***
     *** carga/traslado/descarga ***/
    finOperacion.dia=inicioOperacion.dia-1+diaCarga+diaTraslado+diaDescarga;

    /*** Si la suma es superior a los dias que puede tener ese mes, el día será la diferencia de los mismos, el mes ***
     *** se incrementará en 1 y si el mes es superior a 12, pasa a ser 1 y el año se incrementa en 1 ****/
    if(finOperacion.dia>diasDelMes){
        finOperacion.dia=finOperacion.dia-diasDelMes;
        finOperacion.mes=finOperacion.mes+1;
        if(finOperacion.mes>12){
            finOperacion.mes=1;
            finOperacion.anno=finOperacion.anno+1;
        }
    }

    /*** Guardamos en el array de operaciones la fecha de finalización de la operación ***/
    Buques[id].Operaciones[contadorOperaciones].fechaFinOperacion=finOperacion;

    /*** Guardamos en el buque la fecha de finalización de la operación ***/
    Buques[id].fechaFinUltimaOperacion=finOperacion;

    /*** Si son correctos los datos y guardamos la oeración, aumentamos el contador que va guardando la posicion en el array de operaciones ***/
    contadorOperaciones++;
}

/*** Función para printar calendario con operaciones del buque ***/
void GestionBuque::PrintarCalendarioBuque(int id, TipoFecha fecha){
    int cantOperaciones;             //Variable auxiliar que contendrá la cantidad de Operaciones realizadas durante el mes seleccionado
    int contadorTraslados;           //Variable auxiliar que contendrá un contador de traslados realizados durante el mes seleccionado

    contadorTraslados=1;

    /*** Almacenamos la cantidad de operaciones realizadas en el mes seleccionado y a su vez, guardamos un ***
     *** array con dichas operaciones ***/
    cantOperaciones=OperacionesEnMes(id,fecha);

    printf("                     Resumen Buque: %s\n\n",Buques[id].nombre);

    /*** Printamos el calendario ***/
    fecha.PrintarCalendario(cantOperaciones, listaOperacionesMensuales, fecha);

    /*** Recorremos las operaciones realizadas durante el mes seleccionado y si hay traslado, los printaremos ***/
    for(int i=0;i<=contadorOperaciones;i++){
        if(fecha.anno==Buques[id].Operaciones[i].fechaComienzoOperacion.anno||fecha.anno==Buques[id].Operaciones[i].fechaFinOperacion.anno){
            if(fecha.mes==Buques[id].Operaciones[i].fechaComienzoOperacion.mes||fecha.mes==Buques[id].Operaciones[i].fechaFinOperacion.mes){

                /*** Printamos todos los traslados realizados durante el mes seleccionado ***/
                if(Buques[id].Operaciones[i].duracionTraslado>0){
                    printf("Traslado T%d: desde %s a %s con ",contadorTraslados,Buques[id].Operaciones[i].puertoInicio.nombre,Buques[id].Operaciones[i].puertoDestino.nombre);
                    switch(Buques[id].Operaciones[i].productoCargado){
                        case crudo:
                            printf("Crudo\n");
                            break;
                        case fuel:
                            printf("Fuel\n");
                            break;
                        case gasoil:
                            printf("Gasoil\n");
                            break;
                        case gasolina:
                            printf("Gasolina\n");
                            break;
                        case vacio:
                            printf("Vacio\n");
                            break;
                    }
                    contadorTraslados++;
                }
            }
        }
    }
}

/*** Función para comprobar si hay operaciones en el mes seleccionado ***/
int GestionBuque::OperacionesEnMes(int id, TipoFecha fecha){
    int cantOperacionesMes;             //Variable auxiliar para almacenar en listaOperacionesMensuales, las operaciones disponibles

    cantOperacionesMes=0;

    /*** Recorremos las operaciones disponibles del buque ***/
    for(int i=0;i<=contadorOperaciones;i++){

        /*** Si la operación está dentro del mes seleccionado, lo almacenaremos en listaOperacionesMensuales ***/
        if(fecha.anno==Buques[id].Operaciones[i].fechaComienzoOperacion.anno||fecha.anno==Buques[id].Operaciones[i].fechaFinOperacion.anno){
            if(fecha.mes==Buques[id].Operaciones[i].fechaComienzoOperacion.mes||fecha.mes==Buques[id].Operaciones[i].fechaFinOperacion.mes){

                /*** Copiamos el id ***/
                listaOperacionesMensuales[cantOperacionesMes].id=Buques[id].Operaciones[i].id;

                /*** Si ha sido cargado, almacenamos la duración de la misma ***/
                if(Buques[id].Operaciones[i].duracionCarga>0){
                    listaOperacionesMensuales[cantOperacionesMes].duracionCarga=Buques[id].Operaciones[i].duracionCarga;
                }else{
                    listaOperacionesMensuales[cantOperacionesMes].duracionCarga=0;
                }

                /*** Si ha sido trasladado, almacenamos la duración del mismo ***/
                if(Buques[id].Operaciones[i].duracionTraslado>0){
                    listaOperacionesMensuales[cantOperacionesMes].duracionTraslado=Buques[id].Operaciones[i].duracionTraslado;
                }else{
                    listaOperacionesMensuales[cantOperacionesMes].duracionTraslado=0;
                }

                /*** Si ha sido descargado, almacenamos la duración de la misma ***/
                if(Buques[id].Operaciones[i].duracionDescarga>0){
                    listaOperacionesMensuales[cantOperacionesMes].duracionDescarga=Buques[id].Operaciones[i].duracionDescarga;
                }else{
                    listaOperacionesMensuales[cantOperacionesMes].duracionDescarga=0;
                }

                /*** Almacenamos la fecha de comienzo de la operación ***/
                listaOperacionesMensuales[cantOperacionesMes].diaComienzoOperacion=Buques[id].Operaciones[i].fechaComienzoOperacion.dia;
                listaOperacionesMensuales[cantOperacionesMes].mesComienzoOperacion=Buques[id].Operaciones[i].fechaComienzoOperacion.mes;
                listaOperacionesMensuales[cantOperacionesMes].annoComienzoOperacion=Buques[id].Operaciones[i].fechaComienzoOperacion.anno;

                /*** Almacenamos la fecha de fin de la operación ***/
                listaOperacionesMensuales[cantOperacionesMes].diaFinOperacion=Buques[id].Operaciones[i].fechaFinOperacion.dia;
                listaOperacionesMensuales[cantOperacionesMes].mesFinOperacion=Buques[id].Operaciones[i].fechaFinOperacion.mes;
                listaOperacionesMensuales[cantOperacionesMes].annoFinOperacion=Buques[id].Operaciones[i].fechaFinOperacion.anno;

                /*** Aumentamos el contador de la cantidad de operaciones en el mes ***/
                cantOperacionesMes++;
            }
        }
    }

    /*** Devolvemos la cantidad de operaciones en el mes ***/
    return cantOperacionesMes;
}
