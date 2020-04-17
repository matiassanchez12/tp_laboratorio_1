#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "funciones.h"

int menuPrincipal(float num1, float num2, int flag, int flag1)
{
    int opcion;
    system("cls");
    printf(">>Menu de Opciones de la calculadora:\n");

    if(flag == 1)
    {
        printf("\n 1. Ingresar 1er operando (A = %.2f)", num1);
    }
    else
    {
        printf("\n 1. Ingresar 1er operando (A = x)");
    }

    if(flag1 == 1)
    {
        printf("\n 2. Ingresar 2do operando (B = %.2f)", num2);
    }
    else
    {
        printf("\n 2. Ingresar 2do operando (B = y)");
    }

    printf("\n 3. Calcular todas las operaciones");
    printf("\n  a) Calcular la suma (A+B)");
    printf("\n  b) Calcular la resta (A-B)");
    printf("\n  c) Calcular la division (A/B)");
    printf("\n  d) Calcular la multiplicacion (A*B)");
    printf("\n  e) Calcular el factorial (A!) y (B!)");
    printf("\n 4. Informar resultados");
    printf("\n 5. Salir");

    fflush(stdin);
    opcion = getInt("\n\nIngrese una opcion: ");
    return opcion;
}

void informarResultados(float num1,float num2, float rSum, float rRest, float rDiv, float rMult, int rFact1, int rFact2)
{
    printf("\n\t a) El resultado de %.2f + %.2f es: %.2f", num1, num2, rSum);
    printf("\n\t b) El resultado de %.2f - %.2f es: %.2f", num1, num2, rRest);

    if (num2 != 0)
    {
        printf("\n\t c) El resultado de %.2f / %.2f es: %.2f", num1, num2, rDiv);
    }
    else
    {
        printf("\n\t No es posible dividir por cero");
    }

    printf("\n\t d) El resultado de %.2f * %.2f es: %.2f", num1, num2, rMult);

    if((num1 < 0 || num1 >= 32) || (num2 < 0 || num2 >= 32))
    {
        printf("\n \t No se pudo calcular factorial. Ingresar numeros enteros mayores a 0 y menores a 32 para esta operacion.");
    }
    else
    {
        printf("\n\t e) El resultado de %.2f! es: %d y %.2f! es: %d", num1, rFact1, num2, rFact2);
    }

    printf("\n\n");
}

float suma(float num1, float num2)
{
    float resultado;

    resultado = num1 + num2;

    return resultado;
}

float resta(float num1, float num2)
{
    float resultado;

    resultado = num1 - num2;

    return resultado;
}

float division(float num1, float num2)
{
    float resultado;

    resultado = num1 / num2;

    return resultado;
}

float multiplicar(float num1, float num2)
{
    float resultado;

    resultado = num1 * num2;

    return resultado;
}

int factorial(float a)
{
    int i, aux;
    int resultado = 1;
    aux = (int)a;

    if(a != aux || a < 0)
    {
        return -1;
    }
    else
    {

        for(i=1 ; i<=aux; i++)
        {
            resultado = resultado * i;
        }
        return resultado;
    }
}
