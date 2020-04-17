
/** \brief despliega el menu principal del programa y se indica al usuario elegir una opcion
 *
 * \param num1: se pasa el valor del operando A para ser informado en el menu
 * \param num2: se pasa el valor del operando B para ser informado en el menu
 * \param flag: bandera que indica si el usuario ingreso el operando A para ser mostrado
 * \param flag1: bandera que indica si el usuario ingreso el operando B para ser mostrado
 * \return int opcion: devuelve la opcion seleccionada
 *
 */
int menuPrincipal(float num1, float num2, int flag, int flag1);

/** \brief despliega un menu de resultados, se informan tambien las operaciones para llegar a estos resultados.
 *
 * \param num1: se llama al operando A, para ser mostrado.
 * \param num2: se llama al operando B, para ser mostrado.
 * \param rSum: variable que se le pasa el resultado obtenido de la funcion suma, utilizada en el main.
 * \param rRest: variable que se le pasa el resultado obtenido de la funcion resta, utilizada en el main.
 * \param rDiv: variable que se le pasa el resultado obtenido de la funcion dividir, utilizada en el main.
 * \param rMult: variable que se le pasa el resultado obtenido de la funcion multiplicar, utilizada en el main.
 * \param rFact1: variable que se le pasa el resultado obtenido de la funcion factorial de operando A, utilizada en el main.
 * \param rFact2: variable que se le pasa el resultado obtenido de la funcion factorial de operando B, utilizada en el main.
 * \return void
 *
 */
void informarResultados(float num1,float num2, float rSum, float rRest, float rDiv, float rMult, int rFact1, int rFact2);


/** \brief funcion para sumar
 *
 * \param num1: almacena el valor del operando A
 * \param num2: almacena el valor del operando B
 * \return resultado: resultado de la operacion entre ambos operandos
 *
 */
float suma(float num1, float num2);


/** \brief funcion para restar
 *
 * \param num1: almacena el valor del operando A
 * \param num2: almacena el valor del operando B
 * \return resultado: resultado de la operacion entre ambos operandos
 *
 */
float resta(float num1, float num2);


/** \brief funcion para dividir
 *
 * \param num1: almacena el valor del operando A
 * \param num2: almacena el valor del operando B
 * \return resultado: resultado de la operacion entre ambos operandos
 *
 */
float division(float num1, float num2);

/** \brief funcion para multiplicar
 *
 * \param num1: almacena el valor del operando A
 * \param num2: almacena el valor del operando B
 * \return resultado: resultado de la operacion entre ambos operandos
 *
 */
float multiplicar(float num1, float num2);

/** \brief funcion para factorizar
 *
 * \param a: almacena el valor de un operando
 * \return devuelve -1 en caso de error o el resultado del numero factorizado
 *
 */
int factorial(float a);
