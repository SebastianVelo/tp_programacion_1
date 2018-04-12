#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
/** |||||||||||||||||||||||||||||||||||  */
/** CONSTANTES:
/** |||||||||||||||||||||||||||||||||||  */
/*
Opciones minimas y maximas.
En caso de agregarse mas opciones, solo de modificaria esto
*/
#define OP_MIN 1
#define OP_MAX 6

/*
Operaciones
En caso de pedir mas operaciones, sólo se modificaría esto
*/

#define SUMA 1
#define RESTA 2
#define DIVISION 3
#define MULTIPLICACION 4
#define FACTORIAL 5
#define ALL 6
#define EXIT 7

/** |||||||||||||||||||||||||||||||||||  */

/** \brief simbolo: Devuelve un caracter que representa a la operacion pasada por parametro.
 *
 * \param opcion int
 * \return char
 *
 */
char simbolo(int opcion){
   switch(opcion){
        case SUMA:
                return '+';
                break;
        case RESTA:
                return '-';
                break;
        case DIVISION:
                return '/';
                break;
        case MULTIPLICACION:
                return '*';
                break;
        case FACTORIAL:
                return '!';
                break;
        case ALL:
                return 'T';
    }
}

/** |||||||||||||||||||||||||||||||||||  */

/** \brief resultadoFactorial: Recibe un operando por parametro y realiza su factorial. Este resultado es su retorno.
    Precondiciones: Para su uso debe estar validado su operando.
 *
 * \param operando int
 * \return unsigned long
 *
 */
unsigned long resultadoFactorial(int operando){
	unsigned long ret = 1;
    int i;
    for(i = 2; i <= operando; i++){
    	ret *= i;
    }
    return (unsigned) ret;
}


/** |||||||||||||||||||||||||||||||||||  */

/** \brief resultadoOperacion: Recibiendo dos operandos, realiza la operacion parametrizada y la devuelve en la funcion.
    Precondiciones para su uso: Ya deben estar validados los operandos.
 *
 * \param operandoA float
 * \param operandoB float
 * \param opcion int
 * \return float
 *
 */
float resultadoOperacion(float operandoA, float operandoB, int opcion){
    switch(opcion){
        case SUMA:
                return operandoA + operandoB;
                break;
        case RESTA:
                return operandoA - operandoB;
                break;
        case DIVISION:
                return (float) operandoA / operandoB;
                break;
        case MULTIPLICACION:
                return operandoA * operandoB;
                break;
    }
}

/** |||||||||||||||||||||||||||||||||||  */

/** \brief factorial: Recibe un operando por parametro y muestra en pantalla su factorial si es valido.
 *			
 * \param operando int
 * \return int
 *
 */
int calc_factorial(int operando){
    int esPosible = operando > 0 && operando < 12;
    if(esPosible){
        printf("%d! = %lu", operando, resultadoFactorial(operando));
	}
	return esPosible-1;
}
/** |||||||||||||||||||||||||||||||||||  */

/** \brief operacion; Recibiendo dos operandos, realiza la operacion pasada por parametro, si los operandos son validos (sin incluir el factorial)
 *
 * \param operandoA float
 * \param operandoB float
 * \param opcion int
 * \return itt
 *
 */
int calc_operacion(float operandoA, float operandoB, int opcion){
    int esPosible = !(opcion == DIVISION && operandoB == 0);
    if(esPosible){
        printf("Resultado de %c): %.2f%c%.2f = %.2f", simbolo(opcion), operandoA, simbolo(opcion), operandoB, resultadoOperacion(operandoA, operandoB, opcion));
	}
	return esPosible-1;
}

/** |||||||||||||||||||||||||||||||||||  */

/** \brief todasLasOperaciones; Recibiendo dos operandos, realiza todas las operaciones aritmeticas que se encuentran en el codigo.
        Nota: Realizara una vez cada operacion, a excepcion del factorial que la hara una vez con cada operando.
 *
 * \param operandoA float
 * \param operandoB float
 * \return void
 *
 */
int calc_todasLasOperaciones(float operandoA, float operandoB){
    int i;
    int ret = 0;
    for(i = OP_MIN; i < OP_MAX; i++){
        switch(i){
            case FACTORIAL:
                    calc_factorial(operandoA);
                    printf("\n");
                    calc_factorial(operandoB);
                    break;
            default:
                    calc_operacion(operandoA, operandoB, i);
                    printf("\n");
                    break;
        }
    }
    return ret;
}

#endif // FUNCIONES_H_INCLUDED
