#include "persona.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int nextId();

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Inicializa un id negativo y el campo isEmpty en true de la Persona parametrizada.
 *
 * \param persona Persona*
 * \return void
 *
 */
void persona_init(Persona * persona){
    Persona personaAux;
    personaAux.id = -1;
    personaAux.isEmpty = TRUE;
    *persona = personaAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa con datos aleatorios a la Persona paramerizada.
 *
 * \param persona Persona*
 * \return void
 *
 */
void persona_randomInit(Persona * persona){
    Persona personaAux;
    personaAux.id = nextId();
    personaAux.isEmpty = FALSE;
    personaAux.DNI = PERSONA_DNI_MIN + rand() % (PERSONA_DNI_MAX - PERSONA_DNI_MIN);
    personaAux.edad = PERSONA_edad_MIN + rand() % (PERSONA_edad_MAX - PERSONA_edad_MIN);
    strcpy(personaAux.name, util_getWord());
    *persona = personaAux;
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Persona.
 *
 * \param persona Persona*
 * \param addMode int
 * \return int
 *
 */
int persona_constructor(Persona * persona, int addMode){
    Persona personaAux = *persona;

    showSeparator(6);
    showSeparator(4);
    if(util_getString(&personaAux.name, "Ingrese nombre: ", NAME_LENGTH) == FAIL_1)
        return FAIL_1;
    if(util_getInt(&personaAux.DNI, "Ingrese DNI: ", "Ingrese un DNI correcto. \n", PERSONA_DNI_MIN, PERSONA_DNI_MAX, 3) == FAIL_1)
        return FAIL_1;
    if(util_getInt(&personaAux.edad, "Ingrese edad: ", "Ingrese un edad correcto. \n", PERSONA_edad_MIN, PERSONA_edad_MAX, 3) == FAIL_1)
        return FAIL_1;
    showSeparator(4);
    showSeparator(6);

    personaAux.isEmpty = FALSE;
    if(addMode)
        personaAux.id = nextId();
    *persona = personaAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una persona parametrizada.
 *
 * \param persona Persona
 * \return void
 *
 */
void persona_showData(Persona persona){
    showSeparator(4);
    printf("ID #%d \n", persona.id);
    printf("Nombre: %s\n", persona.name);
    printf("DNI: %d \n", persona.DNI);
    printf("Edad: %d \n", persona.edad);
}
/* ------------------------------------------------------------------ */
/** \brief Swapea el valor de dos Persona.
 *
 * \param stP Persona*
 * \param ndP Persona*
 * \return int
 *
 */
int persona_swap(Persona * stP, Persona * ndP){
    Persona auxiliar;
    auxiliar = *stP;
    *stP = *ndP;
    *ndP = auxiliar;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
static int nextId(){
    static int id = -1;
    id++;
    return id;
}
/* ------------------------------------------------------------------ */
