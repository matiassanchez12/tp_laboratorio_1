#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Puntero al nombre del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] puntero a fileP es NULL o el puntero a la lista es NULL, [< 0] ultimo Id caso contrario.
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int lastId;
    FILE* fileP = fopen(path,"r");
    if(fileP != NULL && pArrayListEmployee != NULL)
    {
        lastId = parser_EmployeeFromText(fileP, pArrayListEmployee);
        if(lastId > 0)
        {
            retorno = lastId;
        }
    }
    return retorno;
}
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char* Puntero al nombre del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] puntero a fileP es NULL o el puntero a la lista es NULL, [< 0] ultimo Id caso contrario.
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int lastId;
    FILE* fileP = fopen(path,"rb");
    if(fileP != NULL && pArrayListEmployee != NULL)
    {
        lastId = parser_EmployeeFromBinary(fileP, pArrayListEmployee);
        if(lastId > 0)
        {
            retorno = lastId;
        }
    }
    return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char* Puntero al nombre del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \param lastId int Ultimo id de la lista enlazada
 * \return int [-1] si pArrayListEmployee es NULL, [0] Proceso cancelado(Intentos agotados), [ < 0] Ultimo Id caso de exito.
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int lastId)
{
    int retorno = -1;
    Employee auxEmployee;
    Employee* pAuxEmployee;
    system("cls");
    printf("------------------------------");
    printf("\n|Seccion de alta a un empleado|\n");
    printf("------------------------------\n\n- A continuacion ingrese los datos del empleado..\n\n");
    if(pArrayListEmployee != NULL)
    {
        retorno = 0;
        if(utn_getString(auxEmployee.name,NAME_LEN,"->Nombre: ", "Error. Solo letras.\n", 3)
                && utn_getNumberFloat(&auxEmployee.salary, "->Salario: ", "Error, solo numeros.\n", 0, 10000000, 3)
                && utn_getNumber(&auxEmployee.hoursWorked, "->Horas trabajadas: ", "Error, solo numeros.\n", 0, 10000000, 3))
        {
            auxEmployee.id = lastId + 1;
            pAuxEmployee = employee_newParametersBin(auxEmployee.id, auxEmployee.name,auxEmployee.hoursWorked,auxEmployee.salary);
            if(pAuxEmployee != NULL)
            {
                if(!ll_add(pArrayListEmployee, pAuxEmployee))
                {
                    retorno = auxEmployee.id;
                }
            }
        }
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si pArrayListEmployee es NULL o Intentos agotados , [0] Proceso cancelado, [ < 0] Modificado con exito.
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pEmployeeAux;
    int lengthArray;
    int i;
    int idEmployee;
    int idUsser;
    lengthArray = ll_len(pArrayListEmployee);
    printf("\n\n[?] Que empleado desea modificar ? \n");
    if(pArrayListEmployee != NULL && utn_getNumber(&idUsser, "\nIngresar el ID: ", "Error, ingresar solo numeros.",0,200000, 5))
    {
        for(i = 0; i < lengthArray; i++)
        {
            pEmployeeAux = ll_get(pArrayListEmployee, i);
            if(pEmployeeAux != NULL)
            {
                if(!employee_getId(pEmployeeAux, &idEmployee) && idEmployee == idUsser)
                {
                    retorno = 0;
                    printf("\n----------------------");
                    printf("\n|Empleado encontrado!|\n");
                    printf("----------------------\n");
                    if(!employee_modifyEmployee(pEmployeeAux))
                    {
                        retorno = 1;
                        break;
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si pArrayListEmployee es NULL, [0] Proceso cancelado, [ < 0] Eliminado con exito.
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pEmployeeAux;
    char confirm;
    int lengthArray;
    int i;
    int idEmployee;
    int idUsser;
    lengthArray = ll_len(pArrayListEmployee);
    if(pArrayListEmployee != NULL)
    {
        printf("\n[?] Que empleado desea dar de baja ? \n");
        if( utn_getNumber(&idUsser, "\n- Ingresar el ID: ", "Error, ingresar solo numeros.",0,200000, 5))
        {
            for(i = 0; i < lengthArray; i++)
            {
                pEmployeeAux = ll_get(pArrayListEmployee, i);
                if(pEmployeeAux != NULL)
                {
                    if(!employee_getId(pEmployeeAux, &idEmployee) && idEmployee == idUsser)
                    {
                        retorno = 0;
                        printf("----------------------\n|Empleado encontrado!|\n----------------------");
                        printf("\nSeguro desea eliminar al empleado con ID ' %d ' ? [s] o [n].\n", idEmployee);
                        if(utn_getOnlyTwoChars(&confirm, "\nSeleccione una opcion: ", "Error, solo [s] o [n].", 's', 'n', 3) &&
                                confirm == 's' && !ll_remove(pArrayListEmployee, i))
                        {
                            retorno = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return retorno;
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si pArrayListEmployee es NULL, [0] Listado mostrado con exito.
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    system("cls");
    int retorno = -1;
    int lenArray;
    int i;
    Employee* pAuxEmployee;
    lenArray = ll_len(pArrayListEmployee);
    if(pArrayListEmployee != NULL)
    {
        printf("\n\t\t   ************************\n\t\t   **--------------------**");
        printf("\n\t\t   **|Lista de empleados|**\n");
        printf("\t\t   **--------------------**\n\t\t   ************************\n");
        printf("  ---------------------------------------------------------\n");
        printf("  | ID   |\tNOMBRE\t     |HORAS TRABAJADAS|\t  SALARIO |\n");
        for(i=0; i<lenArray; i++)
        {
            pAuxEmployee = (Employee*) ll_get(pArrayListEmployee, i);
            if(pAuxEmployee != NULL && !employee_printArray(pAuxEmployee, lenArray))
            {
                retorno = 0;
            }
        }
        printf("  ---------------------------------------------------------\n");
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si pArrayListEmployee es NULL o Intentos agotados al ingresar una opcion, [0] Listado ordenado con exito.
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int order;
    int (*pFunctionCriterio)(void*, void*);
    system("cls");
    printf("--------------------------");
    printf("\n|Seccion de ordenamientos|\n");
    printf("--------------------------\n\n");
    printf("Seleccionar el tipo de orden del listado:\n[1] Orden ascendente\n[0] Orden descendente\n");
    if(pArrayListEmployee != NULL && utn_getNumber(&order, "\n- Ingresar una opcion: ", "Error, solo [1] o [0].", 0, 1, 3))
    {
        pFunctionCriterio = employee_optionCompareForSort();
        printf("\n --------------------------------------------------");
        printf("\n |Ordenando el listado.. solo tomara unos segundos|\n");
        printf(" --------------------------------------------------\n");
        if(!ll_sort(pArrayListEmployee, pFunctionCriterio, order) && pFunctionCriterio != NULL)
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char* Puntero al nombre del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] puntero al nombre del archivo es NULL o el puntero a la lista es NULL, [ 0] se guardo con exito.
 *
 */

int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int i;
    int lenArray;
    FILE* fileP;
    Employee employeeAux;
    Employee* pEmployeeAux;
    lenArray = ll_len(pArrayListEmployee);
    if(path != NULL && pArrayListEmployee != NULL)
    {
        fileP = fopen(path,"w");
        if(fileP != NULL)
        {
            retorno = 0;
            fprintf(fileP,"id,nombre,horasTrabajadas,salary\n");
            for(i=0; i<lenArray; i++)
            {
                pEmployeeAux = ll_get(pArrayListEmployee, i);
                if(pEmployeeAux != NULL)
                {
                    if(!employee_getHoursWorked(pEmployeeAux, &employeeAux.hoursWorked) &&
                            !employee_getId(pEmployeeAux, &employeeAux.id) &&
                            !employee_getName(pEmployeeAux, employeeAux.name) &&
                            !employee_getSalary(pEmployeeAux, &employeeAux.salary))
                    {
                        fprintf(fileP,"%d,%s,%d,%f\n",employeeAux.id, employeeAux.name, employeeAux.hoursWorked, employeeAux.salary);
                    }
                }
            }
            fclose(fileP);
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char* Puntero al nombre del archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] puntero al nombre del archivo es NULL o el puntero a la lista es NULL, [ 0] se guardo con exito.
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    int i;
    int lenArray;

    Employee* pAuxEmployee;
    FILE* fileP;
    lenArray = ll_len(pArrayListEmployee);
    if(pArrayListEmployee != NULL && path != NULL)
    {
        fileP = fopen(path,"wb");
        if(fileP != NULL)
        {
            retorno=0;
            for(i=0; i<lenArray; i++)
            {
                pAuxEmployee = (Employee*) ll_get(pArrayListEmployee, i);
                if(pAuxEmployee != NULL)
                {
                    fwrite(pAuxEmployee,sizeof(Employee),1,fileP);
                }
            }
            fclose(fileP);
        }
    }
    return retorno;
}
