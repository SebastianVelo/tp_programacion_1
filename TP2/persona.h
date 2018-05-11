#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define PERSONA_ID 0
/** MIN AND MAX VALUES */
#define NAME_LENGTH 30
#define PERSONA_DNI_MIN 1000000
#define PERSONA_DNI_MAX 99999999
#define PERSONA_edad_MIN 0
#define PERSONA_edad_MAX 100

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Persona {
   int      isEmpty;
   int      id;
   char     name[NAME_LENGTH] ;
   int      DNI;
   int      edad;
} Persona;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void persona_randomInit(Persona * persona);
void persona_init(Persona * persona);
void persona_showData(Persona persona);
int persona_constructor(Persona * persona, int addMode);
int persona_swap(Persona * stP, Persona * ndP);
