#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno = -1;
    Employee* pAuxEmployee;
    char auxId[200];
    char auxNombre[200];
    char auxHorasTrabajadas[200];
    char auxSueldo[200];
    int lastId;
    char cabecera[200];
    if(pFile!=NULL && pArrayListEmployee!=NULL)
    {
        fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",cabecera,cabecera,cabecera,cabecera);
        do
        {
            if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",auxId,auxNombre,auxHorasTrabajadas,auxSueldo)==4)
            {
                pAuxEmployee = employee_newParametros(auxId,auxNombre,auxHorasTrabajadas,auxSueldo);
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

int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int retorno=-1;
    Employee* pAuxEmployee;
    Employee auxEmployee;
    int lastId;
    if(pArrayListEmployee != NULL && pFile != NULL)
    {
        do
        {
            if(fread(&auxEmployee,sizeof(Employee),1, pFile) == 1)
            {
                pAuxEmployee = employee_newParametrosBin(auxEmployee.id,auxEmployee.nombre,auxEmployee.horasTrabajadas,auxEmployee.sueldo);
                if(pAuxEmployee != NULL && !ll_add(pArrayListEmployee, pAuxEmployee))
                {
                    lastId = pAuxEmployee->id;
                    retorno = lastId;
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
