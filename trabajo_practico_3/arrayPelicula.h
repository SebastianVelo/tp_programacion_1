#include "pelicula.h"
/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
/** OPTIONS */
#define PELICULA_RAND 0
#define PELICULA_ADD 1
#define PELICULA_DEL 2
#define PELICULA_EDIT 3
#define PELICULA_SHOWL 4
#define PELICULA_RETURN 5
/** MESSAGE */
#define PELICULA_ASKID "Ingrese el ID de pelicula: "
#define PELICULA_ASKIDFAIL "Ingrese un ID de pelicula valido."
#define PELICULA_GENERICMSGFAIL "Agoto el limite de reintentos. Vuelva a intentar."
#define PELICULA_ENTITY "PELICULA"
#define PELICULA_SHWLMSGOK "¡Ve a html/index.html para ver el resultado!"
#define PELICULA_ADDMSGOK "¡Pelicula agregada correctamente!"
#define PELICULA_DELMSGOK "¡Pelicula borrada correctamente!"
#define PELICULA_EDITMSGOK "¡Pelicula editada correctamente!"
#define PELICULA_SHWLMSGF1 "¡Aun no hay peliculas en la lista!"
#define PELICULA_ADDMSGF1 "¡Ya esta el cupo de peliculas! Escriba opcion %d para borrar peliculas."
#define PELICULA_EDITDELMSGF1 "¡Aun no ingreso a esta pelicula! Escriba opcion %d para agregar peliculas."

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct ArrayPelicula {
   Pelicula * listPeliculas;
   int length;
} ArrayPelicula;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void arrayPelicula_init(ArrayPelicula * peliculas, int length);
void arrayPelicula_showOptions(void);
int arrayPelicula_add(ArrayPelicula * peliculas);
int arrayPelicula_del(ArrayPelicula * peliculas);
int arrayPelicula_edit(ArrayPelicula * peliculas);
int arrayPelicula_showList(ArrayPelicula peliculas);
int arrayPelicula_showResp(ArrayPelicula * peliculas, int option);
int arrayPelicula_getIndexOfID(ArrayPelicula peliculas, int id);
