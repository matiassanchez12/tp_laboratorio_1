#include <stdlib.h>
#include "Employee.h"
#include <string.h>
static int isString(char* str);

/** \brief Toma una palabra y verifica si posee solo letras
 *
 * \param str char* Un puntero a una palabra
 * \return int [0] Encontro caracteres que no son letras, [1] La palabra es solo letras.
 *
 */
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

/** \brief Recibe un puntero a un elemento tipo empleado y lo elimina utilizando la funcion Free
 *
 * \param this Employee* Puntero a un elemento de tipo empleado
 * \return int [-1] El puntero es NULL, [0] Eliminado con exito.
 *
 */
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

/** \brief Crea un espacio de memoria del tamaño de la estructura Employee
 *
 * \return Employee* El espacio de memoria encontrado.
 *
 */
Employee* employee_new()
{
    return (Employee*) malloc(sizeof(Employee));
}

/** \brief Crea un espacio de memoria para un empleado y le asigna valores para cada campos
 *
 * \param idStr char* Puntero a Id modo string
 * \param nameStr char* Puntero a Nombre
 * \param hoursWorkedStr char* Puntero a Horas trabajadas modo string
 * \param salaryStr char* Puntero a Salario modo string
 * \return Employee* El espacio de memoria donde esta el empleado recientemente construido
 *
 */
Employee* employee_newParameters(char* idStr,char* nameStr,char* hoursWorkedStr,char* salaryStr)
{
    Employee* this = NULL;
    this = employee_new();
    if(this != NULL && idStr != NULL && nameStr != NULL && hoursWorkedStr != NULL && salaryStr != NULL)
    {
        if(	employee_setName(this,nameStr) == -1 ||
                employee_setSalary(this,atof(salaryStr)) == -1 ||
                employee_setId(this,atoi(idStr)) == -1 ||
                employee_setHoursWorked(this, atoi(hoursWorkedStr)) == -1)
        {
            if(!employee_delete(this))
            {
                this = NULL;
            }
        }
    }
    return this;
}

/** \brief Crea un espacio de memoria para un empleado y le asigna valores para cada campos
 *
 * \param idStr char* Puntero a Id
 * \param nameStr char* Puntero a Nombre
 * \param hoursWorkedStr char* Puntero a Horas trabajadas
 * \param salaryStr char* Puntero a Salario
 * \return Employee* El espacio de memoria donde esta el empleado recientemente construido
 *
 */
Employee* employee_newParametersBin(int id,char* name,int hoursWorked,float salary)
{
    Employee* this = NULL;
    this = employee_new();
    if(this != NULL && name != NULL)
    {
        if(employee_setName(this,name) == -1 ||
                employee_setSalary(this,salary) == -1 ||
                employee_setId(this,id) == -1 ||
                employee_setHoursWorked(this, hoursWorked) == -1)
        {
            if(!employee_delete(this))
            {
                this = NULL;
            }
        }
    }
    return this;
}

/** \brief Alta Manual de un empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param salary float Salario del empleado
 * \param name char* Nombre del empleado
 * \param id int Id del empleado
 * \param hoursWorked int Horas trabajadas del empleado
 * \return int [-1] Puntero this es NULL o puntero a name es NULL, [0] Se creo un nuevo empleado con exitosamente.
 *
 */
int employee_add(Employee* this, float salary, char* name, int id, int hoursWorked)
{
    int retorno = -1;
    Employee* pAuxEmployee;
    if(this != NULL && name != NULL)
    {
        pAuxEmployee = employee_newParametersBin(id, name, hoursWorked, salary);
        if(pAuxEmployee != NULL)
        {
            retorno = 0;
            this = pAuxEmployee;
        }
    }
    return retorno;
}

/** \brief Modifica datos de un empleado
 *
 * \param this Employee* Puntero a un empleado
 * \return int [-1] puntero a this es NULL, [0] Modificacion de datos exitosa.
 *
 */
int employee_modifyEmployee(Employee* this)
{
    int retorno = -1;
    Employee auxEmployee;
    char confirm;
    int option;
    if(this != NULL)
    {
        printf("\n- Que dato desea modificar?\n[1] Nombre\n[2] Sueldo\n[3] Horas trabajadas\n[4] Volver al menu principal");
        if(utn_getNumber(&option, "\n\n Ingresar una opcion : ", "Error, solo numeros del 1 al 4.", 1, 4, 3))
        {
            switch(option)
            {
            case 1:
                if(utn_getString(auxEmployee.name,NAME_LEN,"Ingresar nuevo nombre: ", "Error. Solo letras.\n", 3))
                {
                    printf("\n- Seguro desea modificar los datos del empleado ? [s] o [n].\n");
                    if(utn_getOnlyTwoChars(&confirm, "\n Ingresar una opcion: ", "Error, solo [s] o [n].", 's', 'n', 3) &&
                            confirm == 's' && !employee_setName(this, auxEmployee.name))
                    {
                        retorno = 0;
                    }
                }
                break;
            case 2:
                if(utn_getNumberFloat(&auxEmployee.salary, "Ingresar nuevo salario: ", "Error, solo numeros.\n", 0, 10000000, 3))
                {
                    printf("\n- Seguro desea modificar los datos del empleado ? [s] o [n].\n");
                    if(utn_getOnlyTwoChars(&confirm, "\n Ingresar una opcion: ", "Error, solo [s] o [n].", 's', 'n', 3) &&
                            confirm == 's' && !employee_setSalary(this, auxEmployee.salary))
                    {
                        retorno = 0;
                    }
                }
                break;
            case 3:
                if(utn_getNumber(&auxEmployee.hoursWorked, "Ingresar nueva cantidad de horas trabajadas: ", "Error, solo numeros.\n", 0, 10000, 3))
                {
                    printf("\n- Seguro desea modificar los datos del empleado de ID ' %d ' ? [s] o [n].\n", this->id);
                    if(utn_getOnlyTwoChars(&confirm, "\n Ingresar una opcion: ", "Error, solo [s] o [n].", 's', 'n', 3) &&
                            confirm == 's' && !employee_setHoursWorked(this, auxEmployee.hoursWorked))
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

/** \brief Le otorga el nombre a un puntero de tipo empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param name char* Puntero a un nombre
 * \return int [-1] puntero a this o puntero a name son NULL, [0] Nombre seteado con exito.
 *
 */
int employee_setName(Employee* this,char* name)
{
    int retorno = -1;
    if(this != NULL && name != NULL)
    {
        if(isString(name))
        {
            retorno = 0;
            strcpy(this->name,name);
        }
    }
    return retorno;
}

/** \brief Toma el nombre de un puntero de tipo empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param name char* Puntero a un nombre
 * \return int [-1] puntero a this o puntero a name son NULL, [0] Nombre tomado con exito.
 *
 */
int employee_getName(Employee* this,char* name)
{
    int retorno = -1;
    if(this != NULL && name != NULL)
    {
        retorno = 0;
        strcpy(name,this->name);
    }
    return retorno;
}

/** \brief Le otorga el salario a un puntero de tipo empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param salary float* Salario que se va a setear
 * \return int [-1] puntero a this o salary < 0, [0] Salario seteado con exito.
 *
 */
int employee_setSalary(Employee* this,float salary)
{
    int retorno = -1;
    if(this != NULL && salary >= 0)
    {
        retorno = 0;
        this->salary = salary;
    }
    return retorno;
}

/** \brief Toma el salario a un puntero de tipo empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param salary float* Puntero al float donde se va a guardar el salario
 * \return int [-1] puntero a this o salary != NULL, [0] Salario tomado con exito.
 *
 */
int employee_getSalary(Employee* this,float* salary)
{
    int retorno = -1;
    if(this != NULL && salary != NULL)
    {
        retorno = 0;
        *salary = this->salary;
    }
    return retorno;
}

/** \brief Otorga el campo Id en un empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param id int Id que va a ser seteado
 * \return int [-1] This es NULL o Id < 0, [0] Id seteado con exito.
 *
 */
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

/** \brief Toma el campo Id de un empleado
 *
 * \param this Employee* Puntero a un empleado
 * \param id int Puntero con la direccion donde se guadara el id
 * \return int [-1] This es NULL o Id es NULL, [0] Id tomado con exito.
 *
 */
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

/** \brief Setea las horas trabajadas en un empleado
 *
 * \param this Employee* Puntero a un elemento de tipo empleado
 * \param hoursWorked int Horas trabajadas que van a ser seteadas
 * \return int [-1] this es NULL o hoursWorked < 0, [0] Horas trabajadas seteadas con exito.
 *
 */
int employee_setHoursWorked(Employee* this,int hoursWorked)
{
    int retorno = -1;
    if(this != NULL && hoursWorked >= 0)
    {
        retorno = 0;
        this->hoursWorked = hoursWorked;
    }
    return retorno;
}
/** \brief Toma las horas trabajadas de un empleado
 *
 * \param this Employee* Puntero a un elemento de tipo empleado
 * \param hoursWorked int Puntero a variable que guardara las horas trabajadas
 * \return int [-1] this es NULL o hoursWorked es NULL, [0] Horas trabajadas tomadas con exito.
 *
 */
int employee_getHoursWorked(Employee* this,int* hoursWorked)
{
    int retorno = -1;
    if(this != NULL && hoursWorked != NULL)
    {
        retorno = 0;
        *hoursWorked = this->hoursWorked;
    }
    return retorno;
}

/** \brief Pregunta cual criterio de ordenamiento desea el usuario
 *
 * \return void* Puntero a void de la funcion que ordena la lista
 *
 */
void* employee_optionCompareForSort(void)
{
    void* retorno;
    int (*pFunctionCompare)(void*, void*);
    int option;

    printf("\nSeleccionar el criterio de ordenamiento: \n[1] ID\n[2] name");
    if(utn_getNumber(&option, "\n\n- Ingresar una opcion: ", "Error. Fuera de rango.", 1, 2, 3))
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
        }
    }
    return retorno;
}

/** \brief Compara los nombres de dos empleados distintos
 *
 * \param employee1 void* puntero void a empleado 1
 * \param employee2 void* puntero void a empleado 2
 * \return int [-1] si el primero es menor que el segundo, [0] si los nombres son iguales [1] si el primero es mayor que el segundo
 *
 */
int employee_CompareByName(void* employee1, void* employee2)
{
    int retorno;
    char name[NAME_LEN];
    char name1[NAME_LEN];

    Employee* emp1 = (Employee*) employee1;
    Employee* emp2 = (Employee*) employee2;

    if(!employee_getName(emp1, name) && !employee_getName(emp2, name1))
    {
        retorno = strcmpi(name, name1);
    }
    return retorno;
}
/** \brief Compara los id de dos empleados distintos
 *
 * \param employee1 void* puntero void a empleado 1
 * \param employee2 void* puntero void a empleado 2
 * \return int [1] si el primero es mayor que el segundo, [0] si los nombres son iguales [-1] si el primero es mayor que el segundo
 *
 */
int employee_CompareById(void* employee1, void* employee2)
{
    int retorno = -1;
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

/** \brief Imprime el array en forma de listado
 *
 * \param this Employee* Puntero a un empleado
 * \param lenght int Tamaño del listado
 * \return int [-1] Puntero al listado de NULL [0] Listado mostrado con exito.
 *
 */
int employee_printArray(Employee* this,int lenght)
{
    int retorno=-1;
    int auxId;
    char auxName[NAME_LEN];
    int auxHoursWorked;
    float auxSalary;

    if(this != NULL)
    {
        if(!employee_getId(this, &auxId)
                && !employee_getName(this, auxName)
                && !employee_getHoursWorked(this, &auxHoursWorked)
                && !employee_getSalary(this, &auxSalary))
        {
            retorno = 0;
            printf("  ---------------------------------------------------------\n");
            printf("  | %4d |     %13s |     %8d   |  %.2f |\n", auxId,auxName,auxHoursWorked,auxSalary);
        }
    }
    return retorno;
}


