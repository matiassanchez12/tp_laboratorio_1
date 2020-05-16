#include "ArrayEmployees.h"
/** \brief Inicializa el array de empleados poniendo a todos los elementos del array, isEmpty = 1.
 *
 * \param list Employee* Lista de empleados.
 * \param len int Tamaño maximo de Empleados.
 * \return int 1 si se inicilizo con exito, caso contrario 0.
 *
 */
int initEmployees(Employee* list, int len)
{
    int ret = 0;
    int i;
    if(list != NULL && len > 0)
    {
        ret = 1;
        for(i = 0; i<len; i++)
        {
            list[i].isEmpty = 1;
        }
    }
    return ret;
}

/** \brief Busca un empleado por id para verificar existencia.
 *
 * \param list Employee* Lista de empleados.
 * \param len int Tamaño maximo de la lista de empleados.
 * \param id int Id por el cual se va a identificar al empleado.
 * \return int Devuelve el index del empleado (espacio que ocupa en el array) y -1 si no existe el Id.
 *
 */
int findEmployeeById(Employee* list, int len,int id)
{
    int ret = -1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i = 0; i < len; i ++)
        {
            if(list[i].id == id && list[i].isEmpty == 0)
            {
                ret = i;
            }
        }
    }
    return ret;
}

/** \brief Busca el primer espacio libre del array y lo devuelve en caso positivo.
 *
 * \param list Employee* Listado de empleados.
 * \param len int Tamaño total del listado.
 * \return int Devuelve el Index del array vacio, caso contrario, -1: no se encontro espacio vacio.
 *
 */
int findIndexEmpty(Employee* list, int len)
{
    int ret = -1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == 1)
            {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

/** \brief Toma los datos de un empleado para cargarlos en el array.
 *
 * \param list Employee* Listado de empleados.
 * \param len int Tamaño maximo del listado.
 * \param id int* Id del empleado, es autoincremental.
 * \param name[] char Nombre del empleado.
 * \param lastName[] char Apellido del empleado.
 * \param salary float Salario del empleado.
 * \param sector int Sector del empleado.
 * \return int 1 se cargo el empleado correctamente, caso contrario 0.
 *
 */
int addEmployee(Employee* list, int len, int* id, char name[],char lastName[],float salary, int sector)
{
    int ret = 0;
    int index;
    index = findIndexEmpty(list, len);
    if(list != NULL && len > 0 && index < len && index >= 0)
    {
        strcpy(list[index].name, name);
        strcpy(list[index].lastName, lastName);
        list[index].salary = salary;
        list[index].sector = sector;
        list[index].isEmpty = 0;
        list[index].id = *id;
        *id = *id + 1;
        ret = 1;
    }
    return ret;
}

/** \brief Se elimina a un empleado del array.
 *
 * \param list Employee* Lista de empleados.
 * \param len int Tamaño maximo del array.
 * \param id int Id del empleado que se desea a eliminar.
 * \return int Devuelve 1 si se pudo eliminar con exito, caso contrario 0.
 *
 */
int removeEmployee(Employee* list, int len, int id)
{
    int ret = 0;
    int index;
    char confirm;
    index = findEmployeeById(list, len, id);
    if(index >= 0 && list[index].isEmpty != 1)
    {
        printf("\nSeguro desea eliminar el empleado? [s] o [n]\n");
        if(utn_getOnlyTwoChars(&confirm, "Ingresar una opcion: ", "Ingrese solo (s / n).", 's', 'n', 2)
                && confirm == 's')
        {
            list[index].isEmpty = 1;
            ret = 1;
        }
    }
    else
    {
        printf("\nNo se pudo encontrar el ID. Vuelva a intentarlo.");
    }
    return ret;
}

/** \brief Ordena alfabeticamente un array, con dos tipos de orden distintos.
 *
 * \param list Employee* lista de Empleados.
 * \param len int Tamaño maximo de la lista de Empleados.
 * \param order int Orden que se quiere ordenar [0] ascendente y [1] descendente.
 * \return int Devuelve 1 si el ordenamiento fue exitoso, caso contrario 0.
 *
 */
int sortEmployees(Employee* list, int len, int order)
{
    int ret = 0;
    int flag;
    int i;
    Employee auxEmployee;
    int auxiliarCmp;
    int auxiliarCmp2;
    if(list != NULL && len > 0)
    {
        do
        {
            flag = 0;
            for(i=0; i<len-1; i++)
            {
                if(list[i].isEmpty == 1 || list[i+1].isEmpty == 1)
                {
                    continue;
                }
                auxiliarCmp = strcmp(list[i].lastName,list[i+1].lastName);
                auxiliarCmp2 = strcmp(TXT_SECTORS[list[i].sector], TXT_SECTORS[list[i+1].sector]);
                switch(order)
                {
                case 1:
                    if(auxiliarCmp > 0 ||
                            (auxiliarCmp == 0 && auxiliarCmp2 > 0))
                    {
                        flag = 1;
                        ret = 1;
                        auxEmployee = list[i];
                        list[i] = list[i+1];
                        list[i+1] = auxEmployee;;
                    }
                    break;
                case 0:
                    if(auxiliarCmp < 0 ||
                            (auxiliarCmp == 0 && auxiliarCmp2 < 0))
                    {
                        flag = 1;
                        ret = 1;
                        auxEmployee = list[i];
                        list[i] = list[i+1];
                        list[i+1] = auxEmployee;
                    }
                    break;
                }
            }
            len--;
        }while(flag);
    }

    if(ret == 0)
    {
        printf("\nError : No se pudo realizar el ordenamiento. Debe cargar varios empleados para esta operacion.\n");
    }

    return ret;
}

/** \brief Imprime el listado de empleados con todos sus datos.
 *
 * \param list Employee* Lista de empleados.
 * \param len int Tamaño maximo de empleados.
 * \return int Devuelve 1 en caso de listar los empleados con exito, caso contrario 0.
 *
 */
int printEmployees(Employee* list, int len)
{
    int ret = 0;
    int i;
    if(list != NULL && len > 0)
    {
        printf("\n                          >> Lista de empleados <<                             \n\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("|ID\t\t SECTOR\t\t  SALARIO\t\tNOMBRE\t\tAPELLIDO|\n--------------------------------------------------------------------------------");
        for(i=0; i<len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                ret = 1;
                printf("\n|%2d\t %15s\t %.2f\t%15s\t%15s |",list[i].id, TXT_SECTORS[list[i].sector],list[i].salary,list[i].name, list[i].lastName);
            }
        }
        printf("\n--------------------------------------------------------------------------------\n\n");
    }

    return ret;
}

