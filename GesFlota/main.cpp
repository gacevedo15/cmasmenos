/*=============================================================================================================
    Programa: GesFlota

    Descripcion: Programa para gestionar la movilidad de una flota de buques petroleros (GesFlota), para el
                 transporte de distintos productos (crudo, fuel, gasoil y gasolina) entre distintos puertos.
==============================================================================================================*/

#include "Menu.h"

int main(){
  
  /*Declaramos variable de tipo menu para operar con ella*/      
  TipoMenu menu;
  
  /*Inicializamos los valores*/
  menu.MenuInit();
  
  /*Llamamos al menu principal*/
  menu.MenuPrincipal();
  
}
