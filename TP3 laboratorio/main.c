#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"
#include "genericas.h"

int main()
{
    int option;
    LinkedList* listEmployees = ll_newLinkedList();
    int lastId = 0;
    /**
    *AGREGAR LA OPCION SALIR DE LOS MENU
    *MEJORAR ESTILO DE LISTADO
    *MEJORAR INTERACCION CON EL USUARIO
    *ARREGLAR EL SORT: CUANDO ELIJO SORT BY SALARY O BY HR WORKED, NO ORDENA POR DICHOS CAMPOS
    **/
    do
    {
        if(gen_mainMenu(&option))
        {
            switch(option)
            {
            case 1:
                lastId = controller_loadFromText("data.csv", listEmployees);
                if(lastId > 0)
                {
                    printf("Cargado modo TXT con exito!");
                }
                break;
            case 2:
                lastId = controller_loadFromBinary("dataBin.csv", listEmployees);
                if(lastId > 0)
                {
                    printf("Cargado modo BIN con exito!");
                }
                break;
            case 3:
                lastId = controller_addEmployee(listEmployees, lastId);
                if(lastId > 0)
                {
                    printf("Cargado con exito!");
                }
                break;
            case 4:
                printf("Modificar empleados");
                if(controller_editEmployee(listEmployees) == 1)
                {
                    printf("Modificado con exito!");
                }
                break;
            case 5:
                printf("Menu de bajas");
                if(!controller_ListEmployee(listEmployees) && controller_removeEmployee(listEmployees) > 0)
                {
                    printf("Borrado con exito!");
                }
                break;
            case 6:
                if(!controller_ListEmployee(listEmployees))
                {
                    printf("Listado exitoso!");
                }
                break;
            case 7:
                if(!controller_sortEmployee(listEmployees))
                {
                    printf("Ordenamiento exitoso!");
                }
                break;
            case 8:
                if(!controller_saveAsText("data.csv", listEmployees))
                {
                    printf("Guardado TXT exitoso!");
                }
                break;
            case 9:
                if(!controller_saveAsBinary("dataBin.csv", listEmployees))
                {
                    printf("Guardado BIN exitoso!");
                }
                break;
            }
            system("pause");
            system("cls");
        }
    }
    while(option != 10);


    return 0;
}
