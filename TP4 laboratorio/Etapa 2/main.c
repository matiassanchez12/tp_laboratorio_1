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
    Employee* pAux;
    LinkedList* listEmployees2 = ll_newLinkedList();
    LinkedList* listEmployees = ll_newLinkedList();
    int lastId = 0;
    int lengthLinkedList;
    do
    {
        lengthLinkedList = ll_len(listEmployees);
        if(gen_mainMenu(&option))
        {
            switch(option)
            {
            case 1:
                lastId = controller_loadFromText("data.csv", listEmployees);
                gen_checkCorrectLoadedOfEmployees(lastId, "\t-------------------------------------\n\t|Listado tipo TXT cargado con exito!|\n\t-------------------------------------\n\n");
                break;
            case 2:
                lastId = controller_loadFromBinary("data.bin", listEmployees);
                gen_checkCorrectLoadedOfEmployees(lastId, "\t-------------------------------------\n\t|Listado tipo BIN cargado con exito!|\n\t-------------------------------------\n\n");
                break;
            case 3:
                lastId = controller_addEmployee(listEmployees, lastId);
                gen_checkCorrectAdd(lastId);
                break;
            case 4:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    system("cls");
                    printf("-------------------------------------------\n|Seccion para modificar datos de empleados|\n-------------------------------------------\n");
                    controller_ListEmployee(listEmployees);
                    gen_checkReturnWithSwitch(controller_editEmployee(listEmployees), "\t--------------------------------\n\t|Empleado modificado con exito!|\n\t--------------------------------\n\n", "\n- Operacion cancelada con exito!\n", "\n- No se encontro un empleado con ese ID!\n");
                }
                break;
            case 5:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    system("cls");
                    printf("--------------------------------------\n|Seccion para dar de baja un empleado|\n--------------------------------------\n");
                    controller_ListEmployee(listEmployees);
                    gen_checkReturnWithSwitch(controller_removeEmployee(listEmployees), "\t-----------------------------\n\t|Empleado borrado con exito!|\n\t-----------------------------\n\n", "\n- Operacion cancelada con exito!\n\n", "\n- No se encontro un empleado con ese ID!\n\n");
                }
                break;
            case 6:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    gen_checkReturnWithIf(controller_ListEmployee(listEmployees), "\t--------------------\n\t|Listado con exito!|\n\t--------------------\n\n", "Error.");
                }
                break;
            case 7:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    gen_checkReturnWithIf(controller_sortEmployee(listEmployees), "\t----------------------\n\t|Ordenado con exito!!|\n\t----------------------\n\n", "\n- Error. No hay datos suficientes para hacer el ordenamiento solicitado.\n\n");
                }
                break;
            case 8:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    gen_checkReturnWithIf(controller_saveAsText("data.csv", listEmployees), "\t---------------------------\n\t|Guardado modo TXT exitoso!|\n\t---------------------------\n\n", "\n- Error. No se encontraron datos.\n");
                }
                break;
            case 9:
                if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    gen_checkReturnWithIf(controller_saveAsBinary("data.bin", listEmployees), "\t---------------------------\n\t|Guardado modo BIN exitoso!|\n\t---------------------------\n\n", "\n- Error. No se encontraron datos.\n");
                }
                break;
            case 10:
                if(!controller_deleteAllEmployees(listEmployees))
                {
                    printf("\nLista de empleados borrada con exito!\n");
                }
                break;
            case 11:
                if(!controller_deleteLinkedList(listEmployees))
                {
                    printf("\nLista enlazada borrada con exito!\n");
                }
                break;
            case 12:
                if(!controller_verifyListEmpty(listEmployees))
                {
                    printf("\nLa lista contiene elementos..\n");
                }
                break;
            case 13:
                if(controller_insertEmployeInRequiredPosition(listEmployees, lastId))
                {
                    printf("Empleado cargado con exito!");
                }
                break;
            case 14:
                pAux = (Employee*) controller_deleteEmployeeAndGetHimElement(listEmployees);
                if(pAux != NULL)
                {
                    printf("\nElemento obtenido y empleado borrado con exito.\n");
                }
                break;
            case 15:
                if(!controller_verifyExistOfElement(listEmployees))
                {
                    printf("\nEl Id solicitado existe en la lista.\n");
                }
                break;
                case 16:
                if(ll_containsAll(listEmployees, listEmployees2) < 0)
                {
                    printf("\nLas 2 listas son identicas.\n");
                }
                else
                {
                    printf("\nLas listas son distintas\n");
                }
                break;
                case 17:
                listEmployees2 = controller_createCopieOfLinkedList(listEmployees);
                if(listEmployees2 != NULL )
                {
                    controller_ListEmployee(listEmployees2);
                    printf("\n Se copio la lista con exito.\n");
                }
                break;
                case 18:
                listEmployees2 = controller_createCloneOfLinkedList(listEmployees);
                if(listEmployees2 != NULL )
                {
                    controller_ListEmployee(listEmployees2);
                    printf("\n Se copio la lista con exito.\n");
                }
                break;
            case 19:
                printf("\nSaliendo del programa.. Hasta luego!\n");
                break;
            }
            system("pause");
            system("cls");
        }
    }
    while(option != 19);
    return 0;
}
