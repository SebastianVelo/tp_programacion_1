#include "persona.h"

/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define ARRAYPERSONA_LENGTH 7
/** OPTIONS */
#define PERSONA_RAND 0
#define PERSONA_ADD 1
#define PERSONA_DEL 2
#define PERSONA_EDIT 3
#define PERSONA_SHOWL 4
#define PERSONA_SHOWGR 5
#define PERSONA_RETURN 6
/** MESSAGE */
#define PERSONA_ASKID "Ingrese el ID de persona: "
#define PERSONA_ASKIDFAIL "Ingrese un ID de persona valido."
#define PERSONA_GENERICMSGFAIL "Agoto el limite de reintentos. Vuelva a intentar."
#define PERSONA_ENTITY "PERSONA"
#define PERSONA_SHWLMSGOK "¡Aqui esta la lista!"
#define PERSONA_SHWGRMSGOK "¡Aqui esta el grafico!"
#define PERSONA_ADDMSGOK "¡Persona agregada correctamente!"
#define PERSONA_DELMSGOK "¡Persona borrada correctamente!"
#define PERSONA_EDITMSGOK "¡Persona editada correctamente!"
#define PERSONA_SHWLMSGF1 "¡Aun no hay personas en la lista!"
#define PERSONA_ADDMSGF1 "¡Ya esta el cupo de personas! Escriba opcion %d para borrar personas."
#define PERSONA_EDITDELMSGF1 "¡Aun no ingreso a esta persona! Escriba opcion %d para agregar personas."

/* ------------------------------------------------------------------ */
/**                     STRUCT                                        */
/* ------------------------------------------------------------------ */
typedef struct ArrayPersona {
   Persona listPersonas[ARRAYPERSONA_LENGTH];
   int length;
} ArrayPersona;


/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
void arrayPersona_init(ArrayPersona * personas);
void arrayPersona_showOptions(void);
int arrayPersona_add(ArrayPersona * personas);
int arrayPersona_del(ArrayPersona * personas);
int arrayPersona_edit(ArrayPersona * personas);
int arrayPersona_showList(ArrayPersona personas);
int arrayPersona_showResp(ArrayPersona * personas, int option);
int arrayPersona_getIndexOfID(ArrayPersona personas, int id);
