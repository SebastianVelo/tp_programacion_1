#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"
#include "styles.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define PELICULA_ID 0
/** MIN AND MAX VALUES */
#define NAME_LENGTH 30
#define DESC_LENGTH 400
#define PELICULA_DUR_MIN 60
#define PELICULA_DUR_MAX 350
#define PELICULA_STARS_MIN 0
#define PELICULA_STARS_MAX 11
/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct Pelicula {
   int      isEmpty;
   int      id;
   char     title[NAME_LENGTH];
   char     gender[NAME_LENGTH];
   char     description[DESC_LENGTH];
   char     link[DESC_LENGTH];
   int      duration;
   int      stars;
} Pelicula;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void pelicula_randomInit(Pelicula * pelicula);
void pelicula_init(Pelicula * pelicula);
void pelicula_showData(Pelicula pelicula);
int pelicula_constructor(Pelicula * pelicula, int addMode);
int pelicula_swap(Pelicula * stP, Pelicula * ndP);

char * pelicula_getDescription(Pelicula this);
char * pelicula_getLink(Pelicula this);
char * pelicula_getTitle(Pelicula this);
char * pelicula_getGender(Pelicula this);
int pelicula_getDuration(Pelicula this);;
int pelicula_getStars(Pelicula this);

int pelicula_setDescription(Pelicula * this, char* description);
int pelicula_setLink(Pelicula * this, char* link);
int pelicula_setTitle(Pelicula * this, char* title);
int pelicula_setGender(Pelicula * this, char* gender);
int pelicula_setDuration(Pelicula * this, int duration);
int pelicula_setStars(Pelicula * this, int stars);
