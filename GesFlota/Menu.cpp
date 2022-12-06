/*****************************************************************************
* M�dulo: Menu                                                               *
*                                                                            *
*  Contiene el desarrollo de las estructuras de datos y funciones necesarias *
*  para la gesti�n de los diferentes tipos de Menus.                         *
*****************************************************************************/

#include "Menu.h"

/*** Menu para inicializar los arrays de puertos y buques ***/
void TipoMenu::MenuInit(){
  gestion.Init();
}

/*** Menu principal ***/
void TipoMenu::MenuPrincipal(){
  do{
      printf("GesFlota: Gestion de Movimientos de una Flota\n\n");
      printf("    Editar Puerto           (Pulsar P)\n");
      printf("    Editar Buque            (Pulsar B)\n");
      printf("    Estado Buque            (Pulsar E)\n");
      printf("    Operar Buques           (Pulsar O)\n");
      printf("    Resumen Mensual Buque   (Pulsar R)\n");
      printf("    Salir                   (Pulsar S)\n\n");
      printf("Teclear una opcion valida (P|B|E|O|R|S)? ");
      scanf(" %c",&opcion);
      fflush(stdin);
      switch(toupper(opcion)){
        case 'P':
          MenuEditarPuerto();
          opcion='N';
          break;
        case 'B':
          MenuEditarBuque();
          opcion='N';
          break;
        case 'E':
          MenuEstadoBuques();
          opcion='N';
          break;
        case 'O':
          MenuOperarBuque();
          opcion='N';
          break;
        case 'R':
          MenuResumenMensualBuque();
          break;
        case 'S':
          printf("\nSaliendo de Gesflota...\n");
          break;
        default:
          printf("\nERROR: Por favor, introduzca una opcion valida\n\n");
      }
  }while(toupper(opcion)!='S');
}

/*** Menu para editar el Puerto ***/
void TipoMenu::MenuEditarPuerto(){
  char aux;         //Variable auxiliar para evaluar el tipo de puerto
  opcion=' ';       //almacenamos un espacio en blanco a opcion para operar con él
  do{
      do{
        printf("Editar Puerto:\n\n");
        printf("    Identificador (numero entre 1 y 10)? ");
        scanf("%d",&idPuerto);
        fflush(stdin);
          /*** Evaluamos si idPuerto se encuentra entre los valores permitidos, en caso de que no, printamos mensaje de error ***
           *** y pedimos introducir id nuevamente ***/
          if(idPuerto<1||idPuerto>10){
              printf("\nERROR: El Identificador no es correcto\n\n");
              opcion='N';
              continue;
          }
        printf("    Nombre (entre 1 y 20 caracteres)? ");
        /*** Pedimos el nombre del puerto y pasando como parámetro [^\n] al scanf indicamos que deje de leer solamente cuando ***
         *** haya un salto de línea, de esta manera almacenaremos un nombre con espacios en blanco ***/
        scanf(" %[^\n]s",&nombre);
        fflush(stdin);
          /*** Evaluamos si el nombre introducido contiene entre 1 y 20 caracteres en caso de que no, printamos mensaje de error ***
           *** y pedimos comenzar nuevamente desde el id ***/
          if(strlen(nombre)>20){
            printf("\nERROR: El nombre: '%s' debe contener entre 1 y 20 caracteres, pero contiene %d caracteres\n\n", nombre,strlen(nombre));
            opcion='N';
            continue;
          }

        /*** Almacenamos en la variable temporal el contenido del buffer, para así, limpiarlo ***/
        scanf("%c",&temp);

        /*** Pedimos elegir el tipo de puerto ***/
        printf("    Tipo (Y-Yacimiento, R-Refineria, D-Deposito)? ");
        scanf("%c",&aux);
        fflush(stdin);

          /*** Evaluamos que el caracter seleccionado sea uno de los permitidos, en caso de se elija una opcion incorrecta ***
           *** printamos mensaje de error y pedimos comenzar nuevamente desde el id ***/
          switch(toupper(aux)){
            case 'Y':
            case 'R':
            case 'D':
              break;
            default:
              printf("\nERROR: Tipo de puerto incorrecto, debe elegir entre (Y-Yacimiento, R-Refineria, D-Deposito)\n\n");
              opcion='N';
              continue;
          }
        printf("\n\nIMPORTANTE: Esta opcion borra los datos anteriores.\n");
        printf("Son correctos los nuevos datos (S/N)? ");
        scanf(" %c",&opcion);
          /*** En caso de que el usuario presione S, editamos el puerto seleccionado y en caso de que presione cualquier ***
           *** otra tecla, pedimos que introduzca los datos nuevamente ***/
          switch(toupper(opcion)){
            case 'S':
              /*** Printamos por pantalla el puerto seleccionado con los datos añadidos/actualizados ***/
              switch(toupper(aux)){
                case 'Y':
                  gestion.EditarPuerto(idPuerto,nombre,yacimiento);
                  printf("\nPuerto anadido/actualizado:\nId: %d\nNombre: %s\nTipo: Yacimiento\n\n",idPuerto,nombre);
                  break;
                case 'R':
                  gestion.EditarPuerto(idPuerto,nombre,refineria);
                  printf("\nPuerto anadido/actualizado:\nId: %d\nNombre: %s\nTipo: Refineria\nanadido/actualizado\n\n",idPuerto,nombre);
                  break;
                case 'D':
                  gestion.EditarPuerto(idPuerto,nombre,deposito);
                  printf("\nPuerto anadido/actualizado:\nId: %d\nNombre: %s\nTipo: Deposito\nanadido/actualizado\n\n",idPuerto,nombre);
                  break;
              }
              break;
            default:
              printf("\nPor favor, introduzca los datos nuevamente\n\n");
              continue;
          }
      }while(toupper(opcion)!='S');
  }while(toupper(opcion)!='S');
}

/*** Menu para editar el Buque ***/
void TipoMenu::MenuEditarBuque(){
  do{
      do{
        opcion='N';
        printf("Editar Buque:\n\n");
        printf("       Identificador (letra entre A y E)? ");
        scanf(" %c",&idBuque);
        fflush(stdin);
        /*** Evaluamos que el Id sea correcto, en caso contrario, lo pedimos nuevamente ***/
          switch(toupper(idBuque)){
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
              break;
            default:
              printf("\nERROR: Id introducido no es correcto, por favor, introduzca el Id correcto:\n\n");
              continue;
          }
        /*** Pedimos el nombre del buque y pasando como parámetro [^\n] al scanf indicamos que deje de leer solamente cuando ***
         *** haya un salto de línea, de esta manera almacenaremos un nombre con espacios en blanco ***/
        printf("       Nombre (entre 1 y 20 caracteres)? ");
        scanf(" %[^\n]s",&nombre);
        fflush(stdin);
          /*** Evaluamos si el nombre introducido contiene entre 1 y 20 caracteres en caso de que no, printamos mensaje de error ***
           *** y pedimos comenzar nuevamente desde el id ***/
          if(strlen(nombre)>20){
            printf("El nombre: '%s' debe contener entre 1 y 20 caracteres, pero contiene %d caracteres\n", nombre,strlen(nombre));
            opcion='N';
            continue;
          }

        /*** Almacenamos en la variable temporal el contenido del buffer, para así, limpiarlo ***/
        scanf("%c",&temp);

        /*** Solicitamos la fecha de inicio del buque y la almacenamos en la variable de TipoFecha ***/
        printf("       Fecha inicio: Dia? ");
        scanf(" %d",&fecha.dia);
        fflush(stdin);
        printf("       Fecha inicio: Mes? ");
        scanf(" %d",&fecha.mes);
        fflush(stdin);
        printf("       Fecha inicio: Anno? ");
        scanf(" %d",&fecha.anno);
        fflush(stdin);
          /*** Evaluamos que la fecha introducida sea correcta mediante la funcion FechaCorrecta() del struct TipoFecha ***
           *** En caso de que no sea correcta la fecha, pedimos comenzar nuevamente desde el id ***
           *** Consideramos correctas las fechas comprendidas entre 01/01/2023 y 31/12/2999 y que sea una fecha válida ***/
          if(!(fecha.FechaCorrecta())){
            opcion='N';
            continue;
          }

        /*** Printamos los puertos disponibles para la ubicacion inicial del buque, para ello se llama a la funcion ***
         *** EstadoPuertos() del struct GestionBuque ***/
        printf("       Puertos posibles para la ubicacion inicial del buque:\n");
        gestion.EstadoPuertos();
        printf("       Identificador de puerto inicio? ");

        /*** Pedimos que seleccione el id de uno de los puertos disponibles ***/
        scanf(" %d",&idPuerto);
        fflush(stdin);

          /*** Con la funcion PuertoDisponible(id) del struct GestionBuque se evaluará si el id seleccionado ***
           *** esta disponible, en caso de que no, pedimos comenzar nuevamente desde el id. De esta manera nos ***
           *** aseguramos de que solo se pueda introducir uno de los Ids de puertos disponibles en la lista ***/
          if(!(gestion.PuertoDisponible(idPuerto))){
            printf("El Identificador del puerto %d no esta en la lista\n",idPuerto);
            opcion='N';
            continue;
          }

        printf("\n\nIMPORTANTE: Esta opcion borra los datos anteriores.\n");
        printf("Son correctos los nuevos datos (S/N)? ");
        scanf(" %c",&opcion);
          /*** En caso de que el usuario presione S, editamos el buque seleccionado y en caso de que presione cualquier ***
           *** otra tecla, pedimos que introduzca los datos nuevamente ***/
          switch(toupper(opcion)){
            case 'S':
              /*** Llamamos a la función EditarBuque(idBuque,nombre,fecha,idPuerto) del struct GestionBuque para editar el
               *** buque con los nuevos datos ***/
              gestion.EditarBuque(idBuque,nombre,fecha,idPuerto);
              printf("Buque actualizado\n");
              break;
            default:
              printf("Por favor, introduce los datos nuevamente\n");
              continue;
          }
      }while(toupper(opcion)!='S');
  }while(toupper(opcion)!='S');
  opcion='N';
}

/*** Menu para mostrar la lista de buques y su estado ***/
void TipoMenu::MenuEstadoBuques(){
  gestion.EstadoBuques();
}

/*** Menu para Operar con los Buques ***/
void TipoMenu::MenuOperarBuque(){
  int id;           //Variable auxiliar para cambiar el id del Buque a int;
  do{
      do{
        opcion='N';
        printf("Operar Buque:\n\n");
        printf("       Fecha comienzo operacion: Dia? ");
        scanf(" %d",&fecha.dia);
        fflush(stdin);
        printf("       Fecha comienzo operacion: Mes? ");
        scanf(" %d",&fecha.mes);
        fflush(stdin);
        printf("       Fecha comienzo operacion: Anno? ");
        scanf(" %d",&fecha.anno);
        fflush(stdin);
          /*** Evaluamos que la fecha introducida sea correcta mediante la funcion FechaCorrecta() del struct TipoFecha ***
           *** En caso de que no sea correcta la fecha, mostramos mensaje de error y pedimos introducirla nuevamente ***
           *** Consideramos correctas las fechas comprendidas entre 01/01/2023 y 31/12/2999 y que sea una fecha válida ***/
          if(!(fecha.FechaCorrecta())){
            opcion='N';
            printf("\nERROR: La fecha introducida no es correcta\n\n");
            continue;
          }
        printf("       Identificador del Buque (letra entre A y E)? ");
        scanf(" %c",&idBuque);
        fflush(stdin);
          /*** Evaluamos que el Id sea correcto introducido sea correcto y, en caso de serlo, almacenaremos en la variable ***
           *** auxiliar "id" su valor correspondiente del 0 al 4, para posteriormente operar con el buque correspondiente ***/
          switch(toupper(idBuque)){
            case 'A':
              id=0;
              break;
            case 'B':
              id=1;
              break;
            case 'C':
              id=2;
              break;
            case 'D':
              id=3;
              break;
            case 'E':
              id=4;
              break;
            default:
              printf("\nERROR: Id introducido no es correcto, por favor, introduzca el Id correcto:\n\n");
              opcion='N';
              continue;
          }
          /*** Operamos con el buque seleccionado llamando a la función OperarBuque(id,fecha,opcion) del struct GestionBuque ***/
          gestion.OperarBuque(id,fecha,opcion);
          opcion='S';
      }while(toupper(opcion)!='S');
  }while(toupper(opcion)!='S');
  opcion='N';
}

/*** Menú para printar el calendario con las operaciones realizadas del buque ***/
void TipoMenu::MenuResumenMensualBuque(){
  int id;           //Variable auxiliar para cambiar el id del Buque a int;
  do{
        opcion='N';
        printf("Resumen mensual Buque:\n\n");
        printf("       Identificador Buque? ");
        scanf(" %c",&idBuque);
        fflush(stdin);
        /*** Evaluamos que el Id sea correcto ***/
          switch(toupper(idBuque)){
            case 'A':
                id=0;
                break;
            case 'B':
                id=1;
                break;
            case 'C':
                id=2;
                break;
            case 'D':
                id=3;
                break;
            case 'E':
                id=4;
                break;
            default:
              printf("\nERROR: Id introducido no es correcto, por favor, introduzca el Id correcto:\n\n");
              continue;
          }

        /*** Pedimos el mes y año del calendario ***/
        printf("       Seleccion Mes? ");
        scanf(" %d",&fecha.mes);
        fflush(stdin);
        printf("       Seleccion Anno? ");
        scanf(" %d",&fecha.anno);
        fflush(stdin);
        /*** Como solo solicitamos mes y año, pero para evaluar si la fecha es correcta, necesitamos también un día, ***
         *** indicamos que el día es 1 ***/
        fecha.dia=1;
          /*** Evaluamos que la fecha introducida sea correcta, con la función FechaCorrecta del struct TipoFecha, ***
           *** en caso de que no sea correcta, pedimos comenzar nuevamente desde el id ***/
          if(!(fecha.FechaCorrecta())){
            printf("La fecha introducida no es correcta\n");
            opcion='N';
            continue;
          }

        /*** Printamos calendario llamando a la funcion PrintarCalendarioBuque(id,fecha) del struct GestionBuque ***/
        gestion.PrintarCalendarioBuque(id,fecha);

        /*** Preguntamos si se desea consultar otro mes, en caso de que no, salimos al MenuPrincipal ***/
        printf("\nMostrar otro mes (S/N)? ");
        scanf(" %c",&opcion);
        fflush(stdin);

        switch(toupper(opcion)){
            case 'S':
                opcion='N';
                break;
            case 'N':
                opcion='S';
                break;
            default:
                printf("\nERROR (Opcion introducida no es valida)\n\n");
        }
  }while(toupper(opcion)!='S');
  opcion='N';
}










