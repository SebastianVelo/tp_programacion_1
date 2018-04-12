#include <stdio.h>
#include <stdlib.h>

int getInt(int *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    long resultadoAux = 0;
    int ret = 0;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%ld", &resultadoAux);
        if((resultadoAux >= minimo && resultadoAux <= maximo)){
            *resultado = (int) resultadoAux;
            ret = 1;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}

int getFloat(float *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    float resultadoAux = 0;
    int ret = 0;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%f", &resultadoAux);
        int isValid = (resultadoAux > minimo && resultadoAux < maximo);
        if(isValid) {
            *resultado = resultadoAux;
            ret = 1;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}
