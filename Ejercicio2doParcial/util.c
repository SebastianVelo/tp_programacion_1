#include "util.h"

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
int util_getInt(int *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    long resultadoAux = 0;
    int ret = FAIL_1;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%ld", &resultadoAux);
        if((resultadoAux >= minimo && resultadoAux <= maximo)){
            *resultado = (int) resultadoAux;
            ret = SUCCESS;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}
/* ------------------------------------------------------------------ */
int util_getFloat(float *resultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos){
    float resultadoAux = 0;
    int ret = FAIL_1;
    do{
        fflush(stdin);

		printf("%s", mensaje);
        scanf("%f", &resultadoAux);
        int isValid = (resultadoAux > minimo && resultadoAux < maximo);
        if(isValid) {
            *resultado = resultadoAux;
            ret = SUCCESS;
            break;
        }
        printf("%s", mensajeError);
        reintentos--;
    }while(reintentos > 0);

    return ret;
}
/* ------------------------------------------------------------------ */
int util_getString(char *resultado, char* mensaje, int length){
    int ret = SUCCESS;
    fflush(stdin);
    printf("%s", mensaje);
    fgets(resultado, length, stdin);
    return ret;
}
/* ------------------------------------------------------------------ */
int util_getMax(int * arrayInt, int size){
    int max = arrayInt[0];
    int i;
    for(i = 0; i < size; i++){
        if(arrayInt[i] > max)
            max = arrayInt[i];
    }
    return max;
}
/* ------------------------------------------------------------------ */
int util_getMin(int * arrayInt, int size){
    int min = arrayInt[0];
    int i;
    for(i = 0; i < size; i++){
        if(arrayInt[i] < min)
            min = arrayInt[i];
    }
    return min;
}
/* ------------------------------------------------------------------ */
char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;

    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    strcpy(tmp, orig);
    return result;
}
/* ------------------------------------------------------------------ */
char util_getChar(int i, int n){
    return (i > n) ? ' ' : '*';
}
/* ------------------------------------------------------------------ */
char * util_getWord(int size){
    char consonante[] = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz ";
    char vocal[]      = "AEIOUaeiou ";
    char ret[size];
    int i;
    for(i = 0; i < size-1; i++){
        if(i % 2 == 0)
            ret[i] = consonante[rand() % sizeof(consonante)];
        else
            ret[i] = vocal[rand() % sizeof(vocal)];
    }
    return ret;
}
