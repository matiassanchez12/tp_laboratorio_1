int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee, int lastId);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);

LinkedList* controller_createCloneOfLinkedList(LinkedList* pArrayListEmployee);
LinkedList* controller_createCopieOfLinkedList(LinkedList* pArrayListEmployee);
int controller_verifyExistOfElement(LinkedList* pArrayListEmployee);
void* controller_deleteEmployeeAndGetHimElement(LinkedList* pArrayListEmployee);
int controller_insertEmployeInRequiredPosition(LinkedList* pArrayListEmployee, int lastId);
int controller_verifyListEmpty(LinkedList* pArrayListEmployee);
int controller_deleteLinkedList(LinkedList* pArrayListEmployee);
int controller_deleteAllEmployees(LinkedList* pArrayListEmployee);
