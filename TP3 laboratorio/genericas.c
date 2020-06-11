
#include "genericas.h"
/** \brief Imprime el menu principal del programa
 *
 * \param option int* opcion elegida por el usuario
 * \return int Devuelve 1 opcion tomada exitosamente, caso contrario 0.
 *
 */
int gen_mainMenu(int* option)
{
    int retorno = 0;
    if(option != NULL)
    {
        printf(">> Bienvenido al menu principal<<\n");
        printf("\n1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).");
        printf("\n2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).");
        printf("\n3. Alta de empleado");
        printf("\n4. Modificar datos de empleado");
        printf("\n5. Baja de empleado");
        printf("\n6. Listar empleados");
        printf("\n7. Ordenar empleados");
        printf("\n8. Guardar los datos de los empleados en el archivo data.csv (modo texto).");
        printf("\n9. Guardar los datos de los empleados en el archivo data.csv (modo binario).");
        printf("\n10. Salir");
        if(utn_getNumber(option, "\n\nSeleccionar una opcion: ", "Error, fuera de rango.", 1, 10, 2))
        {
            retorno = 1;
        }
        else
        {
            printf("\n\nERROR: Intentos agotados, el programa se cerrara..\n");
            *option = 10;
        }
    }
    return retorno;
}

/** \brief Verifica el valor que retorna una funcion y imprime un mensaje por pantalla
 *
 * \param function int funcion a verificar
 * \param msgAllRight char* Mensaje de exito (1)
 * \param msgError char* Mensaje de Error (0)
 * \return void
 *
 */
void gen_checkReturnWithIf(int function, char* msgAllRight, char* msgError)
{
    if(function)
    {
        printf("%s", msgAllRight);
    }
    else
    {
        printf("%s", msgError);
    }
}

/** \brief Verifica el valor que retorna una funcion y imprime un mensaje por pantalla
 *
 * \param function int funcion a verificar su retorno
 * \param msgAllRight char* Mensaje de exito (1)
 * \param msgError char* Mensaje de Error (-1)
 * \param msgCancelOp char* Mesaje de cancelacion(0)
 * \return void
 *
 */
void gen_checkReturnWithSwitch(int function, char* msgAllRight, char* msgCancelOp, char* msgError)
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
