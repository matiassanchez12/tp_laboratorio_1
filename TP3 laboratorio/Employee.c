#include <stdlib.h>
#include "Employee.h"
#include <string.h>
static int isString(char* str);

static int isString(char* str)
{
    int ret = 1;
    int i=0;
    while(str[i] != '\0')
    {
        if((str[i] != ' ') && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z'))
        {
            ret = 0;
            break;
        }
        i++;
    }
    return ret;
}

int employee_delete(Employee* this)
{
    int retorno = -1;
    if(this != NULL)
    {
        retorno = 0;
        free(this);
    }
    return retorno;
}

Employee* employee_new()
{
    return (Employee*) malloc(sizeof(Employee));
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr)
{
    Employee* this = NULL;
    this = employee_new();
    if(this != NULL && idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL)
    {
        if(	employee_setNombre(this,nombreStr) == -1 ||
                employee_setSueldo(this,atoi(sueldoStr)) == -1 ||
                employee_setId(this,atoi(idStr)) == -1 ||
                employee_setHorasTrabajadas(this, atoi(horasTrabajadasStr)) == -1)
        {
            if(!employee_delete(this))
            {
                this = NULL;
            }
        }
    }
    return this;
}

Employee* employee_newParametrosBin(int id,char* nombre,int horasTrabajadas,int sueldo)
{
    Employee* this = NULL;
    this = employee_new();
    if(this != NULL && nombre != NULL)
    {
        if(employee_setNombre(this,nombre) == -1 ||
                employee_setSueldo(this,sueldo) == -1 ||
                employee_setId(this,id) == -1 ||
                employee_setHorasTrabajadas(this, horasTrabajadas) == -1)
        {
            if(!employee_delete(this))
            {
                this = NULL;
            }
        }
    }
    return this;
}

int employee_add(Employee* this, int salary, char* name, int id, int hoursWorked)
{
    int retorno = -1;
    Employee* pAuxEmployee;
    if(this != NULL && name != NULL)
    {
        pAuxEmployee = employee_newParametrosBin(id, name, hoursWorked, salary);
        if(pAuxEmployee != NULL)
        {
            retorno = 0;
            this = pAuxEmployee;
        }
    }
    return retorno;
}

int employee_modifyEmployee(Employee* this)
{
    int retorno = -1;
    Employee auxEmployee;
    int option;
    if(this != NULL)
    {
        printf("\n- Que dato desea modificar?\n[1] Nombre\n[2] Sueldo\n[3] Horas trabajadas\n[4] Volver al menu principal");
        if(utn_getNumber(&option, "\n\n Ingresar una opcion : ", "Error, solo numeros del 1 al 4.", 1, 4, 3))
        {
            switch(option)
            {
            case 1:
                if(utn_getString(auxEmployee.nombre,NOMBRE_LEN,"Ingresar un nombre: ", "Error. Solo letras.\n", 3))
                {
                    if(!employee_setNombre(this, auxEmployee.nombre))
                    {
                        retorno = 0;
                    }
                }
                break;
            case 2:
                if(utn_getNumber(&auxEmployee.sueldo, "Ingresar sueldo: ", "Error, solo numeros.\n", 0, 10000000, 3))
                {
                    if(!employee_setSueldo(this, auxEmployee.sueldo))
                    {
                        retorno = 0;
                    }
                }
                break;
            case 3:
                if(utn_getNumber(&auxEmployee.horasTrabajadas, "Ingresar horas trabajadas: ", "Error, solo numeros.\n", 0, 10000, 3))
                {
                    if(!employee_setHorasTrabajadas(this, auxEmployee.horasTrabajadas))
                    {
                        retorno = 0;
                    }
                }
                break;
            case 4:
                printf("Volviendo al menu principal..");
                break;
            }
        }
    }
    return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        if(isString(nombre))
        {
            retorno = 0;
            strcpy(this->nombre,nombre);
        }
    }
    return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
    int retorno = -1;
    if(this != NULL && nombre != NULL)
    {
        retorno = 0;
        strcpy(nombre,this->nombre);
    }
    return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo >= 0)
    {
        retorno = 0;
        this->sueldo = sueldo;
    }
    return retorno;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno = -1;
    if(this != NULL && sueldo != NULL)
    {
        retorno = 0;
        *sueldo = this->sueldo;
    }
    return retorno;
}

int employee_setId(Employee* this,int id)
{
    int retorno = -1;
    if(this != NULL && id >= 0)
    {
        retorno = 0;
        this->id = id;
    }
    return retorno;
}

int employee_getId(Employee* this,int* id)
{
    int retorno = -1;
    if(this != NULL && id != NULL)
    {
        retorno = 0;
        *id = this->id;
    }
    return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas >= 0)
    {
        retorno = 0;
        this->horasTrabajadas = horasTrabajadas;
    }
    return retorno;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno = -1;
    if(this != NULL && horasTrabajadas != NULL)
    {
        retorno = 0;
        *horasTrabajadas = this->horasTrabajadas;
    }
    return retorno;
}

void* employee_optionCompareForSort(void)
{
    void* retorno;
    int (*pFunctionCompare)(void*, void*);
    int option;

    printf("\nElija el criterio de ordenamiento: \n[1] ID\n[2] Nombre\n[3] Horas Trabajadas\n[4] Salario");
    if(utn_getNumber(&option, "\n\nIngresar una opcion: ", "Error. Fuera de rango.", 1, 4, 3))
    {
        switch(option)
        {
        case 1:
            pFunctionCompare = employee_CompareById;
            if(pFunctionCompare != NULL)
            {
                retorno = pFunctionCompare;
            }
            break;
        case 2:
            pFunctionCompare = employee_CompareByName;
            if(pFunctionCompare != NULL)
            {
                retorno = pFunctionCompare;
            }
            break;
        case 3:
            pFunctionCompare = employee_CompareBySalary;
            if(pFunctionCompare != NULL)
            {
                retorno = pFunctionCompare;
            }
            break;
        case 4:
            pFunctionCompare = employee_CompareByHoursWorked;
            if(pFunctionCompare != NULL)
            {
                retorno = pFunctionCompare;
            }
            break;
        }
    }
    return retorno;
}

int employee_CompareByName(void* employee1, void* employee2)
{
    int retorno;
    char name[NOMBRE_LEN];
    char name1[NOMBRE_LEN];

    Employee* emp1 = (Employee*) employee1;
    Employee* emp2 = (Employee*) employee2;

    if(!employee_getNombre(emp1, name) && !employee_getNombre(emp2, name1))
    {
        retorno = strcmpi(name, name1);
    }
    return retorno;
}

int employee_CompareById(void* employee1, void* employee2)
{
    int retorno;
    int id;
    int id1;
    Employee* emp1 = (Employee*) employee1;
    Employee* emp2 = (Employee*) employee2;
    if(!employee_getId(emp1, &id) && !employee_getId(emp2, &id1))
    {
        if(id > id1)
        {
            retorno = 1;
        }
        else
        {
            if(id < id1)
            {
                retorno = -1;
            }
            else
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}

int employee_CompareByHoursWorked(void* employee1, void* employee2)
{
    int retorno;
    int hoursWorked;
    int hoursWorked1;
    Employee* emp1 = (Employee*) employee1;
    Employee* emp2 = (Employee*) employee2;
    if(!employee_getHorasTrabajadas(emp1, &hoursWorked) && !employee_getHorasTrabajadas(emp2, &hoursWorked1))
    {
        if(hoursWorked > hoursWorked1)
        {
            retorno = 1;
        }
        else
        {
            if(hoursWorked < hoursWorked1)
            {
                retorno = -1;
            }
            else
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}

int employee_CompareBySalary(void* employee1, void* employee2)
{
    int retorno;
    int salary;
    int salary1;
    Employee* emp1 = (Employee*) employee1;
    Employee* emp2 = (Employee*) employee2;
    if(!employee_getSueldo(emp1, &salary) && !employee_getSueldo(emp2, &salary1))
    {
        if(salary > salary1)
        {
            retorno = 1;
        }
        else
        {
            if(salary < salary1)
            {
                retorno = -1;
            }
            else
            {
                retorno = 0;
            }
        }
    }
    return retorno;
}


int employee_printArray(Employee* this,int lenght)
{
    int retorno=-1;
    int auxId;
    char auxNombre[NOMBRE_LEN];
    int auxHorasTrabajadas;
    int auxSalario;

    if(this != NULL && lenght > 0)
    {
        if(!employee_getId(this, &auxId)
                && !employee_getNombre(this, auxNombre)
                && !employee_getHorasTrabajadas(this, &auxHorasTrabajadas)
                && !employee_getSueldo(this, &auxSalario))
        {
            retorno = 0;
            printf("ID: %d - Nombre: %s- Horas Trabajadas: %d - Sueldo: %d\n", auxId,auxNombre,auxHorasTrabajadas,auxSalario);
        }
    }
    return retorno;
}


