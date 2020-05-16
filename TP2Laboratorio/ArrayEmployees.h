#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"

#define LEN_NAME 51
#define LEN_LASTNAME 51

static const char TXT_SECTORS[4][15]={"MECANICA", "ELECTRONICA", "SISTEMAS", "ROBOTICA"};

typedef struct
{
    int id;
    int sector;
    int isEmpty;
    float salary;
    char name[LEN_NAME];
    char lastName[LEN_LASTNAME];
}Employee;

int initEmployees(Employee* list, int len);
int findEmployeeById(Employee* list, int len,int id);
int findIndexEmpty(Employee* list, int len);
int addEmployee(Employee* list, int len, int* id, char name[],char lastName[],float salary, int sector);
int removeEmployee(Employee* list, int len, int id);
int sortEmployees(Employee* list, int len, int order);
int printEmployees(Employee* list, int len);
