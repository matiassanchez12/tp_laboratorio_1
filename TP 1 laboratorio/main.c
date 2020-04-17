#include <stdio.h>
#include <stdlib.h>
#include "Funciones.h"
#include "utn.h"

int main()
{
    int opcion, rFactorial1, rFactorial2;
    float rSuma, rResta, rDivision, rMultiplicacion, numA, numB;
    int flag = 0, flag1 = 0, flag2 = 0, exit = 0;

    do
    {
        opcion = menuPrincipal(numA, numB, flag1, flag2);
        switch (opcion)
        {
        case 1 :
            numA = getFloat("Ingrese numero A: "); ///Se pide ingresar operando A
            flag1 = 1;
            break;
        case 2:
            numB = getFloat("Ingrese un numero B: "); ///Se pide ingresar operando B
            flag2 = 1;
            break;
        case 3:
            if(flag1 == 1 && flag2 == 1) ///Si se ingresaron numeros A Y B, entonces se calcularan los datos
            {
                rSuma = suma(numA, numB);

                rResta = resta(numA, numB);

                rDivision = division(numA, numB);

                rMultiplicacion = multiplicar(numA, numB);

                rFactorial1 = factorial(numA);
                rFactorial2 = factorial(numB);

                printf("\n*Operaciones calculadas con exito*\n");
                flag = 1;
            }
            else ///No hay datos para calcular, se muestra un mensaje de error
            {
                printf("\nError. No ingreso ningun operando o solo uno.\n");
            }
            break;
        case 4:
            if(flag != 1) ///Si no se ingresaron numeros A y B o no se ingreso calcular datos, no muestra calculos.
            {
                printf("\nError. No ingreso operandos o no ingreso a la opcion 3 para calcular.\n");
            }
            else    ///Si se ingresaron numeros, junto a la opcion - 3. calcular - ,se muestra menu de resultados
            {
                informarResultados(numA, numB, rSuma,rResta, rDivision, rMultiplicacion, rFactorial1, rFactorial2);
            }
            break;
        case 5:
            printf("\nSaliendo de la calculadora. Que tenga buen dia!\n");
            exit = 1;
            break;
        default:
            printf("\nError. Ingrese 1 opcion del menu.\n");
            break;
        }
        system("pause");
    }
    while(exit == 0);

    return 0;
}
