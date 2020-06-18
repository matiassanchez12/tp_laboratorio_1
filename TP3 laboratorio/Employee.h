#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
#include "utn.h"
#define NAME_LEN 50

typedef struct
{
    int id;
    char name[NAME_LEN];
    int hoursWorked;
    float salary;
}Employee;
///PRINCIPALES
int employee_printArray(Employee* this,int lenght);
int employee_add(Employee* this, float salary, char* name, int id, int hoursWorked);
///SETS Y GETS
int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);
int employee_setName(Employee* this,char* name);
int employee_getName(Employee* this,char* name);
int employee_setHoursWorked(Employee* this,int hoursWorked);
int employee_getHoursWorked(Employee* this,int* hoursWorked);
int employee_setSalary(Employee* this,float salary);
int employee_getSalary(Employee* this,float* salary);
///COMPLEMENTARIAS
Employee* employee_new();
Employee* employee_newParameters(char* idStr,char* nameStr,char* hoursWorkedStr,char* salaryStr);
Employee* employee_newParametersBin(int id,char* name,int hoursWorked,float salary);
int employee_modifyEmployee(Employee* this);
int employee_delete(Employee* this);
void* employee_optionCompareForSort(void);
int employee_CompareByName(void* e1, void* e2);
int employee_CompareById(void* e1, void* e2);
int employee_CompareBySalary(void* employee1, void* employee2);
int employee_CompareByHoursWorked(void* employee1, void* employee2);
int employee_printOne(Employee* this);
#endif // employee_H_INCLUDED
