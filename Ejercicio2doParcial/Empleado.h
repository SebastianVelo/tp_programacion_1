#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"
#include "ArrayList.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define EMPLEADO_ID 0
/** MIN AND MAX VALUES */
#define LENGTH 30
#define id_MIN 0
#define horasTrabajadas_MIN 0
#define id_MAX 1000
#define horasTrabajadas_MAX 99999
/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Empleado {
   char     nombre[LENGTH];
   int      id;
   int      horasTrabajadas;
} Empleado;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
Empleado* empleado_new(void);
Empleado* empleado_newForced(char *nombre, char *id, char *horasTrabajadas);
Empleado* empleado_constructor(void);
int empleado_swap(Empleado* stP, Empleado * ndP);
void empleado_showData(Empleado* empleado);

char * empleado_getnombre(Empleado* this);
int empleado_getid(Empleado* this);;
int empleado_gethorasTrabajadas(Empleado* this);

int empleado_setnombre(Empleado* this, char* id);
int empleado_setid(Empleado* this, int id);
int empleado_sethorasTrabajadas(Empleado* this, int stars);
 int em_trabajaMasDe120Horas(Empleado* i);
