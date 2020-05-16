#include <stdio.h>
#include <stdlib.h>
#include "front.h"
#include "utn.h"

#define EMPLOYEE_QUANTITY 1000

int main()
{
    int ID = 0;
    int flag = 0;
    int option;
    Employee listEmployees[EMPLOYEE_QUANTITY];

    if(initEmployees(listEmployees, EMPLOYEE_QUANTITY))
    {
        //front_hardcodeEmployees(listEmployees, EMPLOYEE_QUANTITY);
        do
        {
            if(front_mainMenu(&option))
            {
                switch(option)
                {
                case 1:
                    front_checkReturnWithSwitch(front_add(listEmployees, EMPLOYEE_QUANTITY,&flag, &ID), "\n\n*Finalizado satisfactoriamente!\n", "\nEl proceso ha sido cancelado..\n", "\nError: no hay mas espacio..\n");
                    break;
                case 2:
                    if(flag != 1)
                    {
                      printf("\nError: No se cargaron empleados todavia. Para acceder ingrese empleados (OPCION 1).");
                      break;
                    }
                    front_checkReturnWithSwitch(front_modify(listEmployees,EMPLOYEE_QUANTITY), "\n\n*Finalizado satisfactoriamente!\n", "\nEl proceso ha sido cancelado..\n", "\nError: algo salio mal..  :( \n");
                    break;
                case 3:
                    if(flag != 1)
                    {
                      printf("\nError: No se cargaron empleados todavia. Para acceder ingrese empleados (OPCION 1).");
                      break;
                    }
                    front_checkReturnWithSwitch(front_remove(listEmployees,EMPLOYEE_QUANTITY), "\n\n*Finalizado satisfactoriamente!\n", "\nEl proceso ha sido cancelado..\n", "\nError: algo salio mal.. :( \n");
                    break;
                case 4:
                    if(flag != 1)
                    {
                      printf("\nError: No se cargaron empleados todavia. Para acceder ingrese empleados (OPCION 1).");
                      break;
                    }
                    front_checkReturnWithSwitch(front_menuPrint(listEmployees, EMPLOYEE_QUANTITY), "\n\n*Finalizado satisfactoriamente!\n", "\nEl proceso ha sido cancelado..\n", "\nError: algo salio mal.. :( \n");
                    break;
                case 5:
                    printf("\n\nSaliendo..Que tenga buen dia!\n\n");
                }
            }
            else
            {
                printf("\n\nIntentos agotados!El programa se cerrara.\n\n");
                break;
            }
            printf("\n\n");
            system("pause");
            system("cls");
        }while(option!=5);
    }
    else
    {
        printf("\n\nError. No se pudo iniciar el programa\n\n");
    }
    return 0;
}
