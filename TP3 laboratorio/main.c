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
    int i = 1;
    int nodeIndex;
    Node* pNode = NULL;
    Node* nextNode = NULL;
    Node* retorno = NULL;
    Employee* auxEmployee;
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
                i = 1;
                utn_getNumber(&nodeIndex, "\nIngresar un index: ", "a", 0, 22222, 3);
                pNode = listEmployees->pFirstNode;
                do
                {
                    if(i == nodeIndex)
                    {
                        retorno = pNode;
                        auxEmployee = (Employee*)retorno->pElement;
                        employee_printArray(auxEmployee, 2);
                        break;
                    }
                    nextNode = pNode -> pNextNode;
                    pNode = nextNode;
                    i++;
                }
                while(nextNode != NULL);

                /*if(gen_checkLengthLinkedList(lengthLinkedList))
                {
                    system("cls");
                    printf("-------------------------------------------\n|Seccion para modificar datos de empleados|\n-------------------------------------------\n");
                    controller_ListEmployee(listEmployees);
                    gen_checkReturnWithSwitch(controller_editEmployee(listEmployees), "\t--------------------------------\n\t|Empleado modificado con exito!|\n\t--------------------------------\n\n", "\n- Operacion cancelada con exito!\n", "\n- No se encontro un empleado con ese ID!\n");
                }*/
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
                ll_deleteLinkedList(listEmployees);
                printf("\nSaliendo del programa.. Hasta luego!\n");
            }
            system("pause");
            system("cls");
        }
    }
    while(option != 10);
    return 0;
}
