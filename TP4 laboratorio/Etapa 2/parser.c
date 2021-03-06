#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Toma uno a uno los datos de los empleados
 *
 * \param pFile FILE* Puntero a un archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si puntero a archivo o puntero a la lista son NULL, caso contrario retorna el ultimo ID
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pAuxEmployee;
    char auxId[200];
    char auxName[200];
    char auxHorasTrabajadas[200];
    char auxSalary[200];
    int lastId;
    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxName,auxHorasTrabajadas,auxSalary);
        do
        {
            if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxName,auxHorasTrabajadas,auxSalary)==4)
            {
                pAuxEmployee = employee_newParameters(auxId,auxName,auxHorasTrabajadas,auxSalary);
                if(pAuxEmployee != NULL)
                {
                    if(!ll_add(pArrayListEmployee, pAuxEmployee))
                    {
                        lastId = pAuxEmployee->id;
                        retorno = lastId;
                    }
                }
            }
            else
            {
                break;
            }
        }
        while(feof(pFile)==0);

        fclose(pFile);
    }
    return retorno;
}

/** \brief Toma uno a uno los datos de los empleados
 *
 * \param pFile FILE* Puntero a un archivo
 * \param pArrayListEmployee LinkedList* Puntero a la lista enlazada
 * \return int [-1] si puntero a archivo o puntero a la lista son NULL, caso contrario retorna el ultimo ID
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    Employee* pAuxEmployee;
    int lastId;
    if(pArrayListEmployee != NULL && pFile != NULL)
    {
        do
        {
            pAuxEmployee = employee_new();
            if(fread(pAuxEmployee,sizeof(Employee),1, pFile) == 1)
            {
                if(pAuxEmployee != NULL)
                {
                    if(!ll_add(pArrayListEmployee, pAuxEmployee))
                    {
                    lastId = pAuxEmployee->id;
                    retorno = lastId;
                    }
                }
            }
            else
            {
                break;
            }
        }
        while(feof(pFile)==0);
        fclose(pFile);
    }
    return retorno;
}

