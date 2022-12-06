/*****************************************************************************
* Módulo: CalendarioMes                                                      *
*                                                                            *
*  Contiene el desarrollo de las estructuras de datos y funciones necesarias *
*  para la gestión del calendario.                                           *
*****************************************************************************/

#include "CalendarioMes.h"
#include "GestionBuque.h"

/*<=============== Funciones correspondientes a la Estructura de datos: TipoOperacionesMensuales ===============>*/
/*** Función para devolver la duración total en días de una operación ***/
int TipoOperacionesMensuales::duracionTotal(){
    return duracionCarga+duracionTraslado+duracionDescarga;
}

/*<=============== Funciones correspondientes a la Estructura de datos: TipoFecha ===============>*/
/*** Función para devolver si un anno es bisiesto ***
 *** Parámetro de entrada: año a evaluar ***/
bool TipoFecha::bisiesto(int anno){
  return((anno%4==0)&&(anno%100!=0))||(anno%400==0);
}

/*** Función para sumar días de la semana cíclicamente ***
 *** Parámetros de entrada: dia de referencia y num por el que se incrementa la fecha ***/
int TipoFecha::SumarDias(int dia,int num){
  const int DiasSemana=7;
	int aux;
  aux=(dia+num)%DiasSemana;
  return aux;
}

/*** Función para calcular el día de la semana que corresponde a una fecha ***
 *** Parámetros de entrada: mes y año de referencia ***/
int TipoFecha::DiaDeLaSemana(int mes,int anno){
	   int IncDias;						                          // Incremento en días de la semana
	   int IncAnnos; 						                      // Incremento en días por años enteros
	   int IncBisiesto; 					                      // Incremento en días por años bisiestos

	   /*** Constantes para indicar la fecha de referencia ***/
	   const int DiaReferencia=1;
	   const int MesReferencia=1;
	   const int AnnoReferencia=1601;

       /*** Inicializamos el incremento en dias por años enteros y por bisiestos ***/
	   IncAnnos=anno-AnnoReferencia;
	   IncBisiesto=0;

       /*** En dependencia del mes, se incrementará x días de la semana ***/
	   switch(mes){
          case 1:
          case 10:
            IncDias = 0;
            break;
          case 2:
          case 3:
          case 11:
            IncDias = 3;
            break;
          case 4:
          case 7:
            IncDias = 6;
            break;
          case 5:
            IncDias = 1;
            break;
          case 6:
            IncDias = 4;
            break;
          case 8:
            IncDias = 2;
            break;
          case 9:
          case 12:
            IncDias = 5;
            break;
     }

    /*** Añadimos 1 día por cada año bisiesto ***/
    for(int i=AnnoReferencia+1;i<anno;i++) {
      if(bisiesto(i)){
        IncBisiesto++;
      }
    }

    /*** Añadimos 1 día si la fecha cae en un ano bisiesto despues del día 29 de febrero ***/
    if((bisiesto(anno))&&(mes>2)){
      IncDias++;
    }

    /*** Sumamos el incremento total de días ***/
    IncDias=IncDias+IncAnnos+IncBisiesto-1;

    /***Devolvemos el resultado de la función SumarDias pasándole con parámetros "DiaReferencia" e "IncDias" ***/
    return SumarDias(DiaReferencia, IncDias);
}

/*** Función para comprobar si la fecha introducida es correcta
 *** Consideramos correctas las fechas comprendidas entre 01/01/2023 y 31/12/2999 y que sea una fecha válida ***/
bool TipoFecha::FechaCorrecta(){
  if(anno>=2023&&anno<3000){
    if(mes>=1&&mes<=12){
        switch(mes){
              case 1:
              case 3:
              case 5:
              case 7:
              case 8:
              case 10:
              case 12:
                if(dia>=1&&dia<=31){
                  return true;
                }else{
                  printf("\nERROR: La Fecha: %d/%d/%d es incorrecta\n",dia,mes,anno);
                  return false;
                }
                break;
              case 4:
              case 6:
              case 9:
              case 11:
                if(dia>=1&&dia<=30){
                  return true;
                }else{
                  printf("\nERROR: La Fecha: %d/%d/%d es incorrecta\n",dia,mes,anno);
                  return false;
                }
                break;
              case 2:
                if(anno%4==0&&anno%100!=0||anno%400==0){
                  if(dia>=1&&dia<=29){
                    return true;
                  }else{
                    printf("\nERROR: La Fecha: %d/%d/%d es incorrecta\n",dia,mes,anno);
                    return false;
                  }
                }else{
                  if(dia>=1&&dia<=28){
                    return true;
                  }else{
                    printf("\nERROR: La Fecha: %d/%d/%d es incorrecta\n",dia,mes,anno);
                    return false;
                  }
                }
                break;
        }
    }else{
      printf("\nERROR: La Fecha: %d/%d/%d es incorrecta\n",dia,mes,anno);
      return false;
    }
  }else{
    printf("\nERROR: El anno debe estar comprendido entre 2023 y 2999\n");
    return false;
  }
}

/*** Función para calcular el número de días que tiene el mes ***
 *** Parámetros de entrada: mes y año de la fecha ***/
int TipoFecha::DiasDelMes(int mes, int anno){
  switch(mes){
    case 2:
      if(bisiesto(anno)){
        return 29;
      }else{
        return 28;
      };
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
      break;
    default:
      return 31;
  }
}

/*** Función para imprimir la fecha formato dd/mm/aaaa ***
 *** Parámetro de entrada: Variable TipoFecha ***/
void TipoFecha::PrintarFecha(TipoFecha fecha){
  if(fecha.dia<10){
    printf("0%d/",fecha.dia);
  }else{
    printf("%d/",fecha.dia);
  }
  if(fecha.mes<10){
    printf("0%d/",fecha.mes);
  }else{
    printf("%d/",fecha.mes);
  }
  printf("%d",fecha.anno);
}

/*** Función para printar el mes tipo String ***
 *** Parámetro de entrada: mes ***/
void TipoFecha::PrintarMesString(int mes){
    switch(mes){
        case 1:
            printf("\n                    Enero     ");
            break;
        case 2:
            printf("\n                    Febrero   ");
            break;
        case 3:
            printf("\n                    Marzo     ");
            break;
        case 4:
            printf("\n                    Abril     ");
            break;
        case 5:
            printf("\n                    Mayo      ");
            break;
        case 6:
            printf("\n                    Junio     ");
            break;
        case 7:
            printf("\n                    Julio     ");
            break;
        case 8:
            printf("\n                    Agosto    ");
            break;
        case 9:
            printf("\n                    Septiembre");
            break;
        case 10:
            printf("\n                    Octubre   ");
            break;
        case 11:
            printf("\n                    Noviembre ");
            break;
        case 12:
            printf("\n                    Diciembre ");
            break;
    }
}

/*** Función para imprimir el calendario ***
 *** Parámetros de entrada: La cantOperaciones del mes, el array de TipoOperacionesMensuales que contiene las operaciones ***
 *** del buque durante el mes seleccionado y una variable TipoFecha ***/
void TipoFecha::PrintarCalendario(int cantOperaciones, TipoOperacionesMensuales listaOperaciones[], TipoFecha fecha){
  int numOperaciones;                                                       //Variable auxiliar para recorrer los elementos del array de Operaciones
  int cargasTotales, trasladosTotales, descargasTotales, paradoTotales;     //Variables auxiliares que almacenarán el total de días de carga/traslado/descarga/parado
  int PrimerDia;                                                            //Variable para almacenar la posicion del día 1 del mes
  int contadorTraslado;                                                     //Variable auxiliar con el contador de traslados realizados en el mes
  int aux;                                                                  //Variable auxiliar con el contador de posiciones del calendario

  numOperaciones = 0;
  contadorTraslado = 1;
  aux=0;

  /*** Inicializamos la variable PrimerDia, almacenando en ella el DiaDeLaSemana del mes/año seleccionado ***/
  PrimerDia = DiaDeLaSemana(mes,anno);

  /*** Inicializamos los totales a 0 ***/
  cargasTotales = 0;
  trasladosTotales = 0;
  descargasTotales = 0;
  paradoTotales = 0;

  /*** Printamos el mes y el año ***/
  PrintarMesString(mes);
  printf("%17d\n",anno);

  /*** Printamos la inicial de los días de la semana y el formato del calendario ***/
  printf("                    ___________________________\n                    L   M   X   J   V  | S   D \n");
  printf("                                       |\n                    ");

  /*** Imprimimos espacios en blanco de principio del mes ***/
  for(int i=PrimerDia;i>=1;i--){
    /*** Imprimimos la barra que separa el fin de semana ***/
		if(aux%7==5){
			printf("| ");
		}
		/*** Imprimimos espacios en blanco entre campos si no es lunes o viernes ***/
		if(aux%7!=0&&aux%7!=5){
            printf(" ");
		}
		printf("   ");
		aux++;
	}

    /*** Imprimimos los días del mes ***/
	for(int i=0;i<DiasDelMes(fecha.mes,fecha.anno);i++){

    	if(aux!=0){
    	    /*** Saltamos de semana (\n) en caso de que sea necesario ***/
    	    if(aux%7==0){
    		    printf("\n                    ");
    		}
    	}

    	/*** Imprimimos la barra que separa el fin de semana ***/
        if(aux%7==5){
    		printf("| ");
    	}

    	/*** Imprimimos espacios en blanco entre campos si no es lunes o viernes ***/
    	if(aux%7!=0&&aux%7!=5){
            printf(" ");
    	}

        /*** Evaluamos el caso en el que se seleccione Enero y la fecha comienzo de la operación sea diciembre del año anterior ***/
        if((listaOperaciones[numOperaciones].annoComienzoOperacion<fecha.anno)&&(listaOperaciones[numOperaciones].annoFinOperacion==fecha.anno)){

            /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
             *** menor o igual que la duración total de la operación, comenzaremos a evaluar las diferentes ***
             *** opciones para printar "C","T#","D" o el día del mes ***/
            if(((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionTotal())){

                /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                 *** menor o igual que la duración de la carga de la operación, printaremos "C" y se sumará ***
                 *** en 1 la variable cargasTotales ***/
                if(((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionCarga)){
                    printf(" C ");
                    cargasTotales++;
                }

                /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                 *** mayor que la duración de la carga y menor o igual que la duración de la carga + traslado, ***
                 *** printaremos "T" con el valor de contadorTraslado y se sumará en 1 la variable trasladosTotales ***/
                if(((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))>(listaOperaciones[numOperaciones].duracionCarga)&&((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionCarga+listaOperaciones[numOperaciones].duracionTraslado)){
                    printf("T%d ",contadorTraslado);
                    trasladosTotales++;
                }

                /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                 *** mayor que la duración de la carga + traslado y menor o igual que la duracion total de la ***
                 *** operación, printaremos "D" y se sumará en 1 la variable descargasTotales ***/
                if(((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))>(listaOperaciones[numOperaciones].duracionCarga+listaOperaciones[numOperaciones].duracionTraslado)&&((i+1)+((DiasDelMes(12,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionTotal())){
                    printf(" D ");
                    descargasTotales++;
                }
            }else{

                /*** Printamos el día del mes y se suma en 1 la variable paradoTotales***/
                printf("%2d ",i+1);
                paradoTotales++;

                /*** En el caso de que en la operación tengamos un traslado, sumaremos en 1 la variable contadorTraslado ***/
                if((listaOperaciones[numOperaciones].duracionTraslado)>0){
                    contadorTraslado++;
                }

                /*** En el caso de que el dia a evaluar sea igual al día de fin de la operación + 1, sumaremos en 1 la ***
                 *** variable numOperaciones para pasar a evaluar la siguiente operación ***/
                if((i+1)==(listaOperaciones[numOperaciones].diaFinOperacion+1)){
                    numOperaciones++;
                }
            }

        /*** Evaluamos el caso en el que la operación completa esté dentro del año seleccionado ***/
        }else if((listaOperaciones[numOperaciones].annoComienzoOperacion)==(fecha.anno)&&(listaOperaciones[numOperaciones].annoFinOperacion)==(fecha.anno)){

            /*** Evaluamos el caso en el que la fecha de inicio de operación sea anterior al mes seleccionado ***/
            if((listaOperaciones[numOperaciones].mesComienzoOperacion)<(fecha.mes)&&(listaOperaciones[numOperaciones].mesFinOperacion)==(fecha.mes)){

                /*** Si el dia a evaluar es menor o igual que el dia de fin de la operación, pasamos a evaluar ***
                 *** los posibles casos para printar "C","T#","D" o el día del mes***/
                if((i+1)<=(listaOperaciones[numOperaciones].diaFinOperacion)){

                    /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                     *** menor o igual que la duración de la carga, printaremos "C" y se sumará en 1 la ***
                     *** variable cargasTotales ***/
                    if(((i+1)+((DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionCarga)){
                        printf(" C ");
                        cargasTotales++;
                    }

                    /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                     *** mayor que la duración de la carga y menor o igual que la duración de la carga + traslado, ***
                     *** printaremos "T" con el valor de contadorTraslado y se sumará en 1 la variable trasladosTotales ***/
                    if(((i+1)+((DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))>(listaOperaciones[numOperaciones].duracionCarga)&&((i+1)+((DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=((listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado))){
                        printf("T%d ",contadorTraslado);
                        trasladosTotales++;
                    }

                    /*** Si el dia a evaluar + ((Dias Del Mes de Diciembre+1) - dia comienzo de la operacion) es ***
                     *** mayor que la duración de la carga + traslado y menor o igual que la duracion total de la ***
                     *** operación, printaremos "D" y se sumará en 1 la variable descargasTotales ***/
                    if(((i+1)+((DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))>((listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado))&&((i+1)+((DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)+1)-listaOperaciones[numOperaciones].diaComienzoOperacion))<=(listaOperaciones[numOperaciones].duracionTotal())){
                        printf(" D ");
                        descargasTotales++;
                    }
                }else{

                    /*** Printamos el día del mes y se suma en 1 la variable paradoTotales***/
                    printf("%2d ",i+1);
                    paradoTotales++;

                    /*** En el caso de que en la operación tengamos un traslado, sumaremos en 1 la variable contadorTraslado ***/
                    if((listaOperaciones[numOperaciones].duracionTraslado)>0){
                        contadorTraslado++;
                    }

                    /*** En el caso de que el dia a evaluar sea igual al día de fin de la operación + 1, sumaremos en 1 la ***
                     *** variable numOperaciones para pasar a evaluar la siguiente operación ***/
                    if((i+1)==((listaOperaciones[numOperaciones].diaFinOperacion)+1)){
                        numOperaciones++;
                    }
                }

            /*** Evaluamos el caso en el que la operación completa esté dentro del mes seleccionado ***/
            }else if(((listaOperaciones[numOperaciones].mesComienzoOperacion)==(fecha.mes))&&((listaOperaciones[numOperaciones].mesFinOperacion)==(fecha.mes))){

                    /*** Si el dia a evaluar es menor que el día de comienzo de la operación printamos el día del mes ***
                     *** y se suma en 1 la variable paradoTotales ***/
                    if((i+1)<(listaOperaciones[numOperaciones].diaComienzoOperacion)){
                        printf("%2d ",i+1);
                        paradoTotales++;

                    /*** Si el dia a evaluar está comprendido entre las fechas de comienzo y fin de la operación,
                     *** procedemos a evaluar los posibles casos para printar "C","T#","D" ***/
                    }else if(((i+1)>=(listaOperaciones[numOperaciones].diaComienzoOperacion))&&((i+1)<=(listaOperaciones[numOperaciones].diaFinOperacion))){

                            /*** Si el dia a evaluar es menor a la suma del dia de comienzo con la duración de la carga, ***
                             *** printamos "C" y se sumará en 1 la variable cargasTotales ***/
                            if(((i+1)<((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)))&&((listaOperaciones[numOperaciones].duracionCarga)>0)){
                                printf(" C ");
                                cargasTotales++;
                            }

                            /*** Si el dia a evaluar es menor a la suma del dia de comienzo, la duración de la carga y ***
                             *** la duración del traslado y a la misma vez es mayor o igual que la suma del dia de comienzo ***
                             *** con la duración de la carga printamos "T#" con el contador de traslados y se sumará en 1 la ***
                             *** variable trasladosTotales ***/
                            if(((i+1)<((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado)))&&((i+1)>=((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)))&&((listaOperaciones[numOperaciones].duracionTraslado)>0)){
                                printf("T%d ",contadorTraslado);
                                trasladosTotales++;
                            }

                            /*** Si el dia a evaluar es menor o igual que el dia de fin de operación y a la misma vez es mayor ***
                             *** o igual que la suma de la carga con el traslado, printaremos "D" y se sumará en 1 la variable ***
                             *** descargasTotales ***/
                            if(((i+1)<=(listaOperaciones[numOperaciones].diaFinOperacion))&&((i+1)>=((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado)))&&((listaOperaciones[numOperaciones].duracionDescarga)>0)){
                                printf(" D ");
                                descargasTotales++;
                            }

                    /*** En el caso de que el dia a evaluar sea igual al día de fin de la operación + 1, printaremos el dia del mes, ***
                     *** sumaremos en 1 la variable paradoTotales y la variable de numOperaciones ***/
                    }else if((i+1)==((listaOperaciones[numOperaciones].diaFinOperacion)+1)){
                        printf("%2d ",i+1);
                        paradoTotales++;

                        /*** Si hay traslado en esa operación, sumaremos 1 a la variable contadorTraslado***/
                        if((listaOperaciones[numOperaciones].duracionTraslado)>0){
                            contadorTraslado++;
                        }
                        numOperaciones++;
                    }

            /*** Evaluamos el caso en el que la fecha de fin de operación sea posterior al mes seleccionado ***/
            }else if(((listaOperaciones[numOperaciones].mesComienzoOperacion)==(fecha.mes))&&((listaOperaciones[numOperaciones].mesFinOperacion)>(fecha.mes))){

                /*** Si el dia a evaluar es menor que el dia de comienzo de la operación, printaremos ***
                 *** el dia del mes y sumaremos en 1 el valor de la variable paradoTotales ***/
                if((i+1)<(listaOperaciones[numOperaciones].diaComienzoOperacion)){
                    printf("%2d ",i+1);
                    paradoTotales++;

                /*** Si el dia a evaluar es mayor o igual al dia de comienzo de la operación, procedemos ***
                 *** a evaluar los posibles casos para printar "C","T#","D" ***/
                }else if((i+1)>=(listaOperaciones[numOperaciones].diaComienzoOperacion)){

                    /*** Si el dia a evaluar es menor que la suma del dia de comienzo con la duración de la ***
                     *** carga, printaremos "C" y sumaremos en 1 el valor de la variable cargasTotales ***/
                    if((i+1)<((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga))&&((listaOperaciones[numOperaciones].duracionCarga)>0)){
                        printf(" C ");
                        cargasTotales++;
                    }

                    /*** Si el dia a evaluar es menor que la suma del dia de comienzo, la duración de la carga ***
                     *** y del traslado y, al mismo tiempo, es mayor o igual que la suma del dia de comienzo con ***
                     *** la duración de la carga, printaremos "T#" con el contador de traslados y sumaremos en 1 ***
                     *** el valor de la variable cargasTotales ***/
                    if(((i+1)<((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado)))&&((i+1)>=((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)))&&((listaOperaciones[numOperaciones].duracionTraslado)>0)){
                        printf("T%d ",contadorTraslado);
                        trasladosTotales++;
                    }

                    /*** Si el dia a evaluar es menor o igual al último día del mes y, al mismo tiempo, es mayor o ***
                     *** igual que la suma del dia de comienzo, la duración de la carga y del traslado, printaremos ***
                     *** "D" y sumaremos en 1 el valor de la variable descargasTotales ***/
                    if(((i+1)<=(DiasDelMes(listaOperaciones[numOperaciones].mesComienzoOperacion,listaOperaciones[numOperaciones].annoComienzoOperacion)))&&((i+1)>=((listaOperaciones[numOperaciones].diaComienzoOperacion)+(listaOperaciones[numOperaciones].duracionCarga)+(listaOperaciones[numOperaciones].duracionTraslado)))&&((listaOperaciones[numOperaciones].duracionDescarga)>0)){
                        printf(" D ");
                        descargasTotales++;
                    }
                }
            }else{

               /*** Printamos el día del mes y se suma en 1 la variable paradoTotales***/
               printf("%2d ",i+1);
               paradoTotales++;
            }
        }else{

            /*** Printamos el día del mes y se suma en 1 la variable paradoTotales***/
            printf("%2d ",i+1);
            paradoTotales++;
        }
    	aux++;
    }

	/*** Printamos los totales ***/
	printf("\n\nTiempo de cargas(C): %d dias", cargasTotales);
    printf("\nTiempo de traslados(T#): %d dias",trasladosTotales);
    printf("\nTiempo de descargas(D): %d dias", descargasTotales);
    printf("\nTiempo de parada: %d dias", paradoTotales);

    numOperaciones = 0;
	while(aux%7!=0){
	  /*** Imprimimos la barra que separa el fin de semana ***/
		if(aux%7==5){
		  printf(" ");
		}
		/*** Imprimimos espacios en blanco entre campos si no es lunes o viernes ***/
		if(aux%7!=0&&aux%7!=5){
			printf(" ");
		}
		printf("   ");
		aux++;
	}
	printf ("\n");
}
