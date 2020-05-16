#include "front.h"

static int acumSalaryes(Employee* list, int len, float* acum);
static int countEmployees(Employee* list, int len);
static int promSalarys(Employee* list, int len);

/** \brief Calcula el promedio total de salarios.
 *
 * \param list Employee* lista de Empleados.
 * \param len int tamaño maximo del array.
 * \return int 1 se pudo calcular el promedio, caso contrario 0.
 *
 */
static int promSalarys(Employee* list, int len)
{
    int ret = 0;
    int i;
    int countEmployee;
    float acumSalary;
    float prom;
    int countMaxSalary = 0;

    countEmployee = countEmployees(list, len);

    if(list != NULL && len > 0)
    {
        if(countEmployee != -1 && acumSalaryes(list, len, &acumSalary) != -1)
        {
            ret = 1;
            prom =  acumSalary / countEmployee;
            printf("\n=============================>> Informe solicitado <<================================\n");
            printf("\n> Total de la suma de todos los salarios: %.2f.", acumSalary);
            printf("\n\n> El promedio de los salarios totales es: %.2f.\n", prom);
            for(i = 0; i < len; i ++)
            {
                if(list[i].salary > prom)
                {
                    countMaxSalary ++;
                }
            }

            if(countMaxSalary > 0)
            {
                printf("\n> Cantidad de empleados que superan el promedio: %d.\n", countMaxSalary);
            }
            else
            {
                printf("\n> Atencion: No hay empleados que superen el salario promedio.\n");
            }
        }
        else
        {
            printf("\nError: No hay suficientes datos para esta operacion. ");
        }
    }


    return ret;
}
/** \brief Cuenta la cantidad total de empleados disponibles.
 *
 * \param list Employee* lista de Empleados.
 * \param len int Tamaño maximo del array.
 * \return int Devuelve la cantidad en caso de que hallan empleados cargados, caso contrario 0
 *
 */
static int countEmployees(Employee* list, int len)
{
    int ret = -1;
    int i;
    int count = 0;
    if(list != NULL && len > 0)
    {
        for(i = 0; i < len; i++)
        {

            if(list[i].isEmpty == 0)
            {
                count ++;
                ret = count;
            }
        }
    }
    return ret;
}

/** \brief Suma todos los salarios de los empleados disponibles.
 *
 * \param list Employee* listado de Empleados.
 * \param len int Tamaño maximo del array.
 * \param acum float* Puntero a una variable flotante donde se almacenara el valor de la sumatoria.
 * \return int Devuelve 0 en caso de que hallan empleados disponibles, -1 caso contrario.
 *
 */
static int acumSalaryes(Employee* list, int len, float* acum)
{
    int ret = -1;
    int i;
    if(list != NULL && len > 0)
    {
        for(i = 0; i < len; i++)
        {
            if(list[i].isEmpty == 0)
            {
                *acum = *acum + list[i].salary;
                ret = 0;
            }
        }
    }
    return ret;
}

/** \brief Despliega un menu con la opciones principales del programa.
 *
 * \param option int* Puntero a la variable opcion que determinara que accion se pondra en marcha.
 * \return int Devuelve 1 en caso de exito, caso contrario 0.
 *
 */
int front_mainMenu(int* option)
{
    int ret = 0;
    if(option != NULL)
    {
        printf(">> Bienvenido al menu ABM de empleados <<\n");
        printf("\n[1] ALTAS");
        printf("\n[2] MODIFICAR");
        printf("\n[3] BAJA");
        printf("\n[4] INFORMAR:");
        printf("\n ->1. Listado de los empleados ordenados alfabeticamente por Apellido y Sector.");
        printf("\n ->2. Total y promedio de los salarios, y cuantos empleados superan el salario promedio.");
        printf("\n[5] SALIR\n");
        if(utn_getNumber(option, "\nSeleccionar una opcion: ", "Error, fuera de rango.", 1, 5, 2))
        {
            ret = 1;
        }
    }
    return ret;
}

/** \brief Despliega un menu de informes que habilita distintas opciones.
 *
 * \param list Employee* Listado de empleados.
 * \param len int Tamaño maximo del array.
 * \return int Devuelve -1 caso de error, 0 se cancelo el proceso, 1 el proceso se finalizo con exito.
 *
 */
int front_menuPrint(Employee* list, int len)
{
    int ret = -1;
    int order;
    int option;
    system("cls");
    if(list != NULL && len > 0)
    {
        ret = 0;
        printf("*Aviso: para obtener los informes de forma correcta, se recomienda tener cargados por lo menos 3 empleados. Gracias :)\n");
        printf("----------------------------------------------------------------------------------------------------------------------\n");
        printf("\n>> Menu de informes\n");
        printf("\nQue datos desea mostrar?\n\n[1] Listado de los empleados ordenados alfabeticamente por Apellido y Sector");
        printf("\n[2] Total y promedio de los salarios, y cuantos empleados superan el salario promedio\n[3] Volver al menu principal\n\n");
        if(utn_getNumber(&option, "Ingresar una opcion (1 / 2 / 3) : ", "Ingrese solo (1 / 2 / 3). ", 1, 3, 2))
        {
            switch(option)
            {
            case 1:
                printf("\n> Seleccionar el orden del listado: [0] Ascendente - [1] Descendente\n");
                if(utn_getNumber(&order, "Ingresar el orden: ", "Error, ingresar (0 / 1).", 0, 1, 2) && sortEmployees(list, len, order))
                {
                    if(printEmployees(list, len))
                    {
                        ret = 1;
                        break;
                    }
                }
                break;
            case 2:
                if(promSalarys(list, len))
                {
                    ret = 1;
                }
                break;
            case 3:
                printf("\nSaliendo de informes.. \n");
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

/** \brief Permite modificar los campos de un empleados.
 *
 * \param list Employee* lista de Empleados.
 * \param len int tamaño maximo del array.
 * \return int Devuelve -1 caso de error, 0 se cancelo el proceso, 1 el proceso se finalizo con exito.
 *
 */
int front_modify(Employee* list, int len)
{
    int ret = -1;
    char confirm;
    int option;
    int index;
    int id;
    int flag = 0;
    Employee auxEmployee;

    system("cls");
    printf("\n>> Modificar un empleado\n");
    if(printEmployees(list, len) && list != NULL && len > 0 && utn_getNumber(&id, "\nIngresar ID del empleado :", "Error, fuera de rango.", 0, 2500, 3))
    {
        ret = 0;
        index = findEmployeeById(list, len, id);

        if(index != -1 && list[index].isEmpty == 0)
        {
            auxEmployee = list[index];
            printf("\n> Que dato desea modificar?\n[1] Nombre\n[2] Apellido\n[3] Sector\n[4] Salario\n[5] Volver al menu principal\n");
            if(utn_getNumber(&option, "\nIngresar una opcion: ", "Error. Dato invalido.", 0, 5, 3))
            {
                switch(option)
                {
                case 1:
                    if(utn_getString(auxEmployee.name, LEN_NAME, "Ingresar el nuevo nombre: ", "Error. Dato invalido.", 3))
                    {
                        flag = 1;
                    }
                    break;
                case 2:
                    if(utn_getString(auxEmployee.lastName, LEN_LASTNAME, "Ingresar el nuevo apellido: ", "Error. Dato invalido.", 3))
                    {
                        flag = 1;
                    }
                    break;
                case 3:
                    printf("\n> Sectores disponibles\n[0]%9s\n[1] %11s\n[2]%9s\n[3]%9s\n[4] SALIR", TXT_SECTORS[0], TXT_SECTORS[1], TXT_SECTORS[2], TXT_SECTORS[3]);
                    if(utn_getNumber(&option, "\nIngresar una opcion ( 0 / 1 / 2 / 3 / 4): ", "Error. Opcion incorrecta.", 0, 4, 3))
                    {
                        switch(option)
                        {
                        case 0:
                            auxEmployee.sector = option;
                            flag = 1;
                            break;
                        case 1:
                            auxEmployee.sector = option;
                            flag = 1;
                            break;
                        case 2:
                            auxEmployee.sector = option;
                            flag = 1;
                            break;
                        case 3:
                            auxEmployee.sector = option;
                            flag = 1;
                            break;
                        case 4:
                            printf("Volviendo al menu principal. ");
                            break;
                        }
                    }
                    break;
                case 4:
                    if(utn_getNumberFloat(&auxEmployee.salary, "Ingresar el nuevo salario: ", "Error. Dato invalido.",0, 1000000, 3))
                    {
                        flag = 1;
                    }
                    break;
                }
            }
        }
        else
        {
            printf("\nNo se pudo encontrar el ID. Vuelva a intentarlo.");
        }
    }

    if(flag == 1 && utn_getOnlyTwoChars(&confirm, "\nModificar el empleado? Ingresar [s] o [n] : ", "Ingresar solo [s] o [n].", 's', 'n', 2)
            && confirm == 's')
    {
        list[index] = auxEmployee;
        ret = 1;
    }
    return ret;
}

/** \brief Agrega un empleado al array, haciendo antes las verificaciones correspondientes
 *
 * \param list Employee* lista de Empleados.
 * \param len int tamaño maximo de la lista.
 * \param flag int* Puntero a flag que avisa al Main si se cargo un empleado.
 * \param id int* Puntero a id, modifica el valor del id de los empleados sumandole 1, en caso de que se cargue con exito.
 * \return int Devuelve -1 caso de error, 0  se cancelo el proceso, 1 el proceso se finalizo con exito.
 *
 */
int front_add(Employee* list, int len,int* flag, int* id)
{
    int ret = -1;
    char confirm;
    int option;
    Employee auxEmployee;
    system("cls");
    printf("\n>> Alta de un empleado\n");
    if(list != NULL && len > 0 && findIndexEmpty(list, len) != -1)
    {
        ret = 0;
        if(utn_getString(auxEmployee.name,LEN_NAME, "\nIngresar nombre: ", "Error. Fuera de rango.", 2) &&
                utn_getString(auxEmployee.lastName, LEN_LASTNAME, "\nIngresar apellido: ", "Error. Fuera de rango.", 2) &&
                utn_getNumberFloat(&auxEmployee.salary, "\nIngresar salario: ", "Error. Fuera de rango.", 0, 1000000, 2))
        {
            printf("\n> Sectores disponibles\n[0]%9s\n[1] %11s\n[2]%9s\n[3]%9s\n[4] SALIR", TXT_SECTORS[0], TXT_SECTORS[1], TXT_SECTORS[2], TXT_SECTORS[3]);
            if(utn_getNumber(&option, "\nIngresar una opcion ( 0 / 1 / 2 / 3 / 4): ", "Error. Opcion incorrecta.", 0, 4, 3))
            {
                if(option != 4)
                {
                    auxEmployee.sector = option;
                    printf("\nAgregar al empleado? [s] o [n]\n");
                    if(utn_getOnlyTwoChars(&confirm, "\nIngresar una opcion: ", "Ingresar solo (s / n).", 's', 'n', 2)
                            && confirm == 's'
                            && addEmployee(list, len, id, auxEmployee.name, auxEmployee.lastName, auxEmployee.salary, auxEmployee.sector))
                    {
                        ret = 1;
                        *flag = 1;
                    }
                }
            }
        }
    }
    return ret;
}

/** \brief Elimina un empleado del listado
 *
 * \param list Employee* lista de Empleados.
 * \param len int Tamaño maximo del array.
 * \return int Devuelve -1 caso de error, 0 se cancelo el proceso, 1 el proceso se finalizo con exito.
 *
 */
int front_remove(Employee* list, int len)
{
    int ret = -1;
    int id;
    system("cls");
    printf("\n>> Baja de un empleado\n");
    if(printEmployees(list, len) && list != NULL && len > 0 && utn_getNumber(&id, "\n\nIngresar ID: ", "Error, fuera de rango.", 0, 1500, 2))
    {
        ret = removeEmployee(list, len, id);
    }
    return ret;
}

/** \brief Verifica el valor de retorno de una Funcion 'X' y en base a ese dato, muestra un mensaje por pantalla.
 *
 * \param function int Funcion 'X'.
 * \param msgAllRight char* Mensaje cuando retorno vale 1, generalmente mensaje de exito.
 * \param msgCancelOp char* Mensaje cuando retorno vale 0, generalmente mensaje que anuncia la cancelacion del proceso.
 * \param msgError char* Mensaje cuando retorno vale -1, generalmente mensaje de error.
 * \return void
 *
 */
void front_checkReturnWithSwitch(int function, char* msgAllRight, char* msgCancelOp, char* msgError)
{
    switch(function)
    {
    case -1:
        printf("%s", msgError);
        break;

    case 0:
        printf("%s", msgCancelOp);
        break;

    case 1:
        printf("%s", msgAllRight);
        break;
    }
}

/** \brief Hardcodeo de datos.
 *
 * \param list Employee* lista de empleados.
 * \param len int tamaño maximo del array.
 * \return void
 *
 */
void front_hardcodeEmployees(Employee* list, int len)
{
    int i;
    Employee aux[9]=
    {
        {1,1,0,12000,"Roberto","Maximiliano"},
        {2,2,0,11000,"Franco","Roldan"},
        {3,0,0,12500,"Federico","Julen"},
        {4,3,0,20000, "Santiago","Barrionuevo"},
        {5,0,0,5000, "Mariana","Aquino"},
        {6,1,0,5300,"Hernesto","Rodriguez"},
        {7,0,0,11000,"Roberto","Bolanio"},
        {8,3,0,23300,"JuanPablo","Urrutia"},
        {9,2,0,50040,"Horacio","Oido"},
    };
    for(i=0; i<9; i++)
    {
        list[i] = aux[i];
    }
}
