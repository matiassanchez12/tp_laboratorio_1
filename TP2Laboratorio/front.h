#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "ArrayEmployees.h"

int front_mainMenu(int* option);
int front_menuPrint(Employee* list, int len);
int front_modify(Employee* list, int len);
int front_add(Employee* list, int len,int* flag, int* id);
int front_remove(Employee* list, int len);

void front_hardcodeEmployees(Employee* list, int len);
void front_checkReturnWithSwitch(int function, char* msgAllRight, char* msgCancelOp, char* msgError);


