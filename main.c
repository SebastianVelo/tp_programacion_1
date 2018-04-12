#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "calc.h"
#include "util.h"

/** |||||||||||||||||||||||||||||||||||  */
/** CONSTANTES:
/** |||||||||||||||||||||||||||||||||||  */
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

/*
Boolean
*/

#define TRUE 1
#define FALSE 0

void mostarOpciones(void);
void calculadora(void);

int main()
{
    calculadora();
    return 0;
}
void mostarOpciones(void){
    /** Doy las opciones que otorga el enunciado */
	printf("\n///////////////////////////////////////////////////\n");
    printf("%d : SUMA \n", SUMA);
    printf("%d : RESTA \n", RESTA);
    printf("%d : DIVISION \n", DIVISION);
    printf("%d : MULTIPLICACION \n", MULTIPLICACION);
    printf("%d : FACTORIAL \n", FACTORIAL);
    printf("%d : TODAS LAS OPERACIONES \n", ALL);
    printf("%d : SALIR \n", EXIT);
    printf("\n///////////////////////////////////////////////////\n");
}

void calculadora(){
    mostarOpciones();

	//OPCION Y OPERANDOS
    float numeroA = 0;
    float numeroB = 0;
    int opcion = 0;
    //FLAGS
    int resultado = 0;
    int seguir = TRUE;
    int i = 1;
	while(seguir == TRUE){
        printf("\n||||||||||||||||||||||||||%d||||||||||||||||||||||||||||\n", i);
        i++;
        /** Flusheo el buffer de entrada. */
        fflush(stdin);

		/** Pido la operacion al usuario. Si despues de dos reintentos ingresa una operacion invalida, la opcion por default sera EXIT */
		if(getInt(&opcion, "Ingrese la operacion a realizar: ", "Ingrese una opcion valida. \n", SUMA, EXIT, 3) == FALSE)
            opcion = EXIT;
		/** VALIDACION DE OPCION: Si pidio salir, cambio el valor de control del bucle y también breakeo la iteración. */
		if(opcion == EXIT){
			seguir = FALSE;
			break;
		}
        /** Muestro por pantalla la opcion elegida por el usuario. */
        printf("Operacion elegida: %c\n", simbolo(opcion));

		/** Pido el primer operando. Si lo coloco incorrectamente tres veces, vuelve a pedirte la opcion */
		if(getFloat(&numeroA, "Ingresar operando A: ", "Fuera de rango o caracter invalido. [] \n", SHRT_MIN, SHRT_MAX, 3) == FALSE)
            continue;
        /** Switch: */
		switch(opcion){
            /** Si es RESTA, SUMA, DIVISION, MULTIPLICACION, ALL, pido el segundo operando y opero.
				@see operacion(float operandoA, float operandoB, int opcion) [funciones.h]
				@see todasLasOperaciones(float operandoA, float operandoB) [funciones.h] */
			case ALL:  case RESTA: 	case SUMA: case DIVISION: case MULTIPLICACION:
				/** Pido el segundo operando. Si lo coloco incorrectamente tres veces, vuelve a pedirte la opcion */
                if(getFloat(&numeroB, "Ingresar operando B: ", "Fuera de rango [] \n", SHRT_MIN, SHRT_MAX, 3) == FALSE)
                    continue;
                /** Realizo la operacion correcta, si salio bien. */
				if(opcion == ALL)
					resultado = calc_todasLasOperaciones(numeroA, numeroB);
				else
					resultado = calc_operacion(numeroA, numeroB, opcion);
				break;
			/** Si no ingresó ninguna opción de las constantes, le pido que ingrese una válida. */
			/** Si es FACTORIAL, opero sin pedir el segundo operando.
				@see factorial(int operando) [funciones.h]}*/
			case FACTORIAL:
				resultado = calc_factorial(numeroA);
				break;
			default:
				printf("Ingrese una opcion valida. \n");
				break;
		}

		if(resultado == -1)
            printf("Los datos de entrada ingresados no permiten realizar la operacion. Por favor, intente nuevamente.");
	}

    printf("\nHasta luego!");
}
