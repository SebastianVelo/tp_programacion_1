#include "ArrayList.h"
#include "Empleado.h"

int parser_parseEmpleados(char* fileName, ArrayList* listaEmpleados)
{
    FILE* csv = fopen(fileName,"r");
    if(csv != NULL){
        empleados_newCVS(listaEmpleados, csv);
        return 1;
    }
    return 0; // FALLO
}

