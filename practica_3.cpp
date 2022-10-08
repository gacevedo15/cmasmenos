/**************************************
    * NOMBRE: #Gustavo#
    * PRIMER APELLIDO: #Acevedo#
    * SEGUNDO APELLIDO: #Alfonso#
    * DNI: #52021927K#
    * EMAIL: #gacevedoalfonso@gmail.com#
    ***************************************/

/*=============================================================================================================
    Programa: Calendario

    Descripción: Programa que imprime la hoja del calendario del mes y año introducido entre los años 1601
                 y 3000
==============================================================================================================*/

/*=============================================================================================================
                                              DIRECTIVA DE COMPILACIÓN
==============================================================================================================*/
#include <stdio.h>

/*=============================================================================================================
                                                     TAD FECHA
==============================================================================================================*/
typedef struct TipoFecha{
    void IntroducirFecha();
    bool FechaCorrecta();
    void PrintarFecha();
    int DiasDelMes();

  private:
    int mes, anno;
};

/*=============================================================================================================
                                                SUBPROGRAMAS AUXILIARES
==============================================================================================================*/
/* Lista de nombres para los meses del año */
const int maxNombre=15;
typedef char TipoNombre[maxNombre];
typedef TipoNombre listaNombreMes[13];

listaNombreMes nombreMes = {"?",
                            "ENERO     ",
                            "FEBRERO   ",
                            "MARZO     ",
                            "ABRIL     ",
                            "MAYO      ",
                            "JUNIO     ",
                            "JULIO     ",
                            "AGOSTO    ",
                            "SEPTIEMBRE",
                            "OCTUBRE   ",
                            "NOVIEMBRE ",
                            "DICIEMBRE ",};

/* Devolver si un año es bisiesto */
bool bisiesto(int anno){
  return((anno%4==0)&&(anno%100!=0))||(anno%400==0);
}

/* Sumar días de la semana cíclicamente */
int SumarDias(int dia,int num){	                        /* dia de referencia y num por el que se incrementa la fecha */
  const int DiasSemana=7;
	int aux;
  aux=(dia+num)%DiasSemana;
  return aux;
}

/* Calcular el día de la semana que corresponde a una fecha */
int DiaDeLaSemana(int mes,int anno){
	   int IncDias;						                          /* Incremento en días de la semana */
	   int IncAnnos; 						                        /* Incremento en días por años enteros */
	   int IncBisiesto;						                      /* Incremento en días por años bisiestos */
	   const int AnnoReferencia=1601;
	   const int MesReferencia=1;
	   const int DiaReferencia=1;

	   IncAnnos=anno-AnnoReferencia;
	   IncBisiesto=0;

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

    /* Añadir 1 día por cada año bisiesto */
    for(int i=AnnoReferencia+1;i<anno;i++) {
      if(bisiesto(i)){
        IncBisiesto++;
      }
    }

    /* añadir un día si la fecha cae en un ano bisiesto despues del día 29 de febrero */
    if((bisiesto(anno))&&(mes>2)){
      IncDias++;
    }

    /* Sumamos el incremento total de días */
    IncDias=IncDias+IncAnnos+IncBisiesto-1;

    return SumarDias (DiaReferencia, IncDias);
}

/*=============================================================================================================
                                                FUNCIONES DEL TAD FECHA
==============================================================================================================*/
/*Función para introducir la fecha*/
void TipoFecha::IntroducirFecha(){
  printf("%cMes (1..12)? ",168);
  scanf("%d",&mes);
  printf("%cA%co (1601..3000)? ",168, 164);
  scanf("%d",&anno);
}

/*Función para comprobar si la fecha introducida es correcta*/
bool TipoFecha::FechaCorrecta(){
  if(mes>=1&&mes<=12){
    if(anno>=1601&&anno<=3000){
      return true;
    }
  }else{
    return false;
  }
}

/* Calcular el número de días que tiene el mes */
int TipoFecha::DiasDelMes(){
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

/*Función para imprimir la fecha*/
void TipoFecha::PrintarFecha(){
  int aux=0;                                        /* Variable auxiliar con el contador de posiciones del calendario */
  int PrimerDia;                                    /* Variable para almacenar la posición del día 1 del mes */
  PrimerDia = DiaDeLaSemana(mes,anno);

  printf("\n%s%17d\n",nombreMes[mes],anno);
  printf("===========================\nLU  MA  MI  JU  VI | SA  DO\n===========================\n");

  /* Imprimimos espacios en blanco de principio del mes */
  for(int i=PrimerDia;i>=1;i--){
    /* Imprimimos la barra que separa el fin de semana */
		if(aux%7==5){
			printf("| ");
		}
		/* Imprimimos espacios en blanco entre campos si no es lunes o viernes */
		if(aux%7!=0&&aux%7!=5){
      printf(" ");
		}
		printf(" . ");
		aux++;
	}

  /* Imprimimos los días del mes*/
	for(int i=0;i<DiasDelMes();i++){
	  if(aux!=0){
	    /* Saltamos de semana (\n) en caso de que sea necesario */
		  if(aux%7==0){
			  printf("\n");
		  }
	  }
	  /* Imprimimos la barra que separa el fin de semana */
    if(aux%7==5){
		  printf("| ");
	  }
	  /* Imprimimos espacios en blanco entre campos si no es lunes o viernes */
	  if(aux%7!=0&&aux%7!=5){
      printf(" ");
	  }
	  printf("%2d ",i+1);
	  aux++;
	}

	while(aux%7!=0){
	  /* Imprimimos la barra que separa el fin de semana */
		if(aux%7==5){
		  printf("| ");
		}
		/* Imprimimos espacios en blanco entre campos si no es lunes o viernes */
		if(aux%7!=0&&aux%7!=5){
			printf(" ");
		}
		printf(" . ");
		aux++;
	}
	printf ("\n");
}

/*=============================================================================================================
                                              PROGRAMA PRINCIPAL
==============================================================================================================*/
int main(){
  TipoFecha fecha;

  fecha.IntroducirFecha();

  if(fecha.FechaCorrecta()==true){
    fecha.PrintarFecha();
  }
}
