#include <stdio.h>
#include <stdlib.h>
#include "utn.h"

int getInt (char mensaje[])
{
    int numero;

    printf(mensaje);

    fflush(stdin);
    scanf("%d", &numero);

    return numero;
}

float getFloat(char mensaje[])
{
    float num;

    printf(mensaje);
    fflush(stdin);
    scanf("%f", &num);

    return num;
}

char getChar(char mensaje[])
{
    char letra;

    printf(mensaje);
    fflush(stdin);
    scanf("%s", &letra);

    return letra;
}
