#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"
#include "parser.h"
/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee, int lastId)
{
    int retorno = -1;
    Employee auxEmployee;
    Employee* pAuxEmployee;
    printf("\nALTA DE EMPLEADO\n");
    if(pArrayListEmployee != NULL)
    {
        retorno = 0;
        if(utn_getString(auxEmployee.nombre,NOMBRE_LEN,"Ingresar un nombre: ", "Error. Solo letras.\n", 3)
                && utn_getNumber(&auxEmployee.sueldo, "Ingresar sueldo: ", "Error, solo numeros.\n", 0, 10000000, 3)
                && utn_getNumber(&auxEmployee.horasTrabajadas, "Ingresar horas trabajadas: ", "Error, solo numeros.\n", 0, 10000, 3))
        {
            auxEmployee.id = lastId + 1;
            pAuxEmployee = employee_newParametrosBin(auxEmployee.id, auxEmployee.nombre,auxEmployee.horasTrabajadas,auxEmployee.sueldo);
            if(pAuxEmployee != NULL)
            {
                if(!ll_add(pArrayListEmployee, pAuxEmployee))
                {
                    retorno = auxEmployee.id;
                }
            }
        }
    }
    else
    {
        printf("\n* Atencion!: No se cargo la lista de empleados.\n* Para cargar la lista elija la opcion [1] para modo TXT o [2] para modo BIN del menu principal.\n\n");
    }
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pEmployeeAux;
    char confirm;
    int lengthArray;
    int i;
    int idEmployee;
    int idUsser;
    lengthArray = ll_len(pArrayListEmployee);
    printf("\n== Menu de modificaciones == ");
    if(pArrayListEmployee != NULL && lengthArray > 0 &&
            utn_getNumber(&idUsser, "\n\nIngresar el id del empleado: ", "Error, ingresar solo numeros.",0,200000, 5))
    {
        for(i = 0; i < lengthArray; i++)
        {
            pEmployeeAux = ll_get(pArrayListEmployee, i);
            if(pEmployeeAux != NULL)
            {
                if(!employee_getId(pEmployeeAux, &idEmployee) && idEmployee == idUsser)
                {
                    retorno = 0;
                    printf("\nEmpleado encontrado!");
                    if(!employee_modifyEmployee(pEmployeeAux))
                    {
                        printf("\n- Seguro desea modificar los datos del empleado de ID ' %d ' ? [s] o [n].\n", idEmployee);
                        if(utn_getOnlyTwoChars(&confirm, "\n Ingresar una opcion: ", "Error, solo [s] o [n].", 's', 'n', 3) &&
                                confirm == 's')
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

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
///-1 NO SE ENCONTRO AL EMPLEADO, 0 ENCONTRO AL EMPLEADO DEL ID, PERO LA ACCION FUE CANCELADA, 1 BORRADO EXITOSAMENTE

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
    if(pArrayListEmployee != NULL && lengthArray > 0 &&
            utn_getNumber(&idUsser, "Ingresar el id del empleado: ", "Error, ingresar solo numeros.",0,200000, 5))
    {
        for(i = 0; i < lengthArray; i++)
        {
            pEmployeeAux = ll_get(pArrayListEmployee, i);
            if(pEmployeeAux != NULL)
            {
                if(!employee_getId(pEmployeeAux, &idEmployee) && idEmployee == idUsser)
                {
                    retorno = 0;
                    printf("\nSeguro desea eliminar al empleado de ID ' %d ' ? [s] o [n].\n", idEmployee);
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
    ///COMPROBAR SI ES NECESARIO ESTE IF
    /*if(ll_len(pArrayListEmployee) == 0 && !ll_deleteLinkedList(pArrayListEmployee))
    {
        printf("El listado de empleado fue eliminado.");
    }*/
    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int lenArray;
    int i;
    Employee* pAuxEmployee;
    lenArray = ll_len(pArrayListEmployee);
    if(pArrayListEmployee != NULL && lenArray > 0)
    {
        printf("\n-----LISTA ALUMNOS-----\n");
        for(i=0; i<lenArray; i++)
        {
            pAuxEmployee = (Employee*) ll_get(pArrayListEmployee, i);
            if(pAuxEmployee != NULL && !employee_printArray(pAuxEmployee, lenArray))
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    int order;
    int (*pFunctionCriterio)(void*, void*);
    printf("Elija el tipo de orden del listado:\n[1] Indica orden ascendente\n[0] Indica orden descendente\n");
    if(pArrayListEmployee != NULL && utn_getNumber(&order, "\nIngresar una opcion: ", "Error, solo [1] o [0].", 0, 1, 3))
    {
       pFunctionCriterio = employee_optionCompareForSort();
        if(pFunctionCriterio != NULL && !ll_sort(pArrayListEmployee, pFunctionCriterio, order))
        {
            retorno = 0;
        }
    }
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
    if(path != NULL && pArrayListEmployee != NULL && lenArray > 0)
    {
        fileP = fopen(path,"w");
        if(fileP != NULL)
        {
            retorno = 0;
            fprintf(fileP,"id,nombre,horasTrabajadas,sueldo\n");
            for(i=0; i<lenArray; i++)
            {
                pEmployeeAux = ll_get(pArrayListEmployee, i);
                if(pEmployeeAux != NULL)
                {
                    if(!employee_getHorasTrabajadas(pEmployeeAux, &employeeAux.horasTrabajadas) &&
                            !employee_getId(pEmployeeAux, &employeeAux.id) &&
                            !employee_getNombre(pEmployeeAux, employeeAux.nombre) &&
                            !employee_getSueldo(pEmployeeAux, &employeeAux.sueldo))
                    {
                        fprintf(fileP,"%d,%s,%d,%d\n",employeeAux.id, employeeAux.nombre, employeeAux.horasTrabajadas, employeeAux.sueldo);
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
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
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
    if(pArrayListEmployee != NULL && path != NULL && lenArray > 0)
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
