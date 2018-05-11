#include "arrayPersona.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int firstIndexAvailable(ArrayPersona personas);
static int sortArray(ArrayPersona * personas);
static int * getAges(ArrayPersona personas);
static int showMsg(int option, int resp);

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */

/** \brief Inicializa en vacio el campo listaPersonas del ArrayPersonas parametrizado.
 *
 * \param personas ArrayPersona*
 * \return void
 *
 */
void arrayPersona_init(ArrayPersona * personas){
    ArrayPersona personasAux;
    personasAux.length = ARRAYPERSONA_LENGTH;
    int i;
    for(i = 0; i < personasAux.length; i++){
        persona_init(&personasAux.listPersonas[i]);
    }
    *personas = personasAux;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera aleatoria el campo listaPersonas del ArrayPersona parametrizado
 *
 * \param personas ArrayPersona*
 * \return void
 *
 */
void arrayPersona_randomInit(ArrayPersona * personas){
    ArrayPersona personasAux;
    personasAux.length = ARRAYPERSONA_LENGTH;
    int i;
    for(i = 0; i < personasAux.length; i++){
        persona_randomInit(&personasAux.listPersonas[i]);
    }
    *personas = personasAux;
}
/* ------------------------------------------------------------------ */
/** \brief Agrega una persona al campo listaPersonas del ArrayPersona parametrizado.
 *
 * \param personas ArrayPersona*
 * \return int
 *
 */
int arrayPersona_add(ArrayPersona * personas){
    ArrayPersona personasAux = *personas;
    int index = firstIndexAvailable(personasAux);
    if(index == FAIL_1)
        return FAIL_1;
    if(persona_constructor(&personasAux.listPersonas[index], TRUE) == FAIL_1)
        return FAIL_3;

    *personas = personasAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y borra una persona del campo listaPersonas del ArrayPersona parametrizado.
 *
 * \param personas ArrayPersona*
 * \return int
 *
 */
int arrayPersona_del(ArrayPersona * personas){
    ArrayPersona personasAux = *personas;
    if(arrayPersona_showList(personasAux) == FAIL_1)
        return FAIL_1;
    int id;
    if(util_getInt(&id, PERSONA_ASKID, PERSONA_ASKIDFAIL, 0, personasAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayPersona_getIndexOfID(personasAux, id);

    if(personasAux.listPersonas[index].isEmpty)
        return FAIL_2;
    else
        persona_init(&personasAux.listPersonas[index]);

    *personas = personasAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y edita los campos de esa persona que este en listaPersonas del ArrayPersona parametrizado.
 *
 * \param personas ArrayPersona*
 * \return int
 *
 */
int arrayPersona_edit(ArrayPersona * personas){
    ArrayPersona personasAux = *personas;
    if(arrayPersona_showList(personasAux) == FAIL_1)
        return FAIL_1;

    int id;
    if(util_getInt(&id, PERSONA_ASKID, PERSONA_ASKIDFAIL, 0, personasAux.length, 3) == FAIL_1)
        return FAIL_3;
    int index = arrayPersona_getIndexOfID(personasAux, id);

    if(personasAux.listPersonas[index].isEmpty)
        return FAIL_2;
    else if(persona_constructor(&personasAux.listPersonas[index], FALSE) == FAIL_1)
        return FAIL_3;

    *personas = personasAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las personas que esten activas en el listaPersonas del ArrayPersonas parametrizado.
 *
 * \param personas ArrayPersona
 * \return int
 *
 */
int arrayPersona_showList(ArrayPersona personas){
    int ret = FAIL_1;
    int i;
    sortArray(&personas);
    showSeparator(4);
    printf("%s\n", PERSONA_ENTITY);
    for(i = 0; i < personas.length; i++){
        if(!personas.listPersonas[i].isEmpty){
            persona_showData(personas.listPersonas[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra un grafico de edades de las personas cargadas en el campo listaPersonas del ArrayPersona parametrizado.
 *
 * \param personas ArrayPersona
 * \return int
 *
 */
int arrayPersona_showGraph(ArrayPersona personas){
    int * ages = getAges(personas);
    if(util_getMax(ages, 3) < 1)
        return FAIL_1;
    tab(TABSIZE);
    showSeparator(6);
    showGraph(ages, 3);
    tab(TABSIZE);
    printf("|Menos \t|Entre \t|Mas de |\n");
    tab(TABSIZE);
    printf("|de 18 \t|18 y 35|35     |\n");
    tab(TABSIZE);
    showSeparator(6);
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide una opcion por parametro y ejecuta esa accion, obteniendo la respuesta de cada uno y sus posibles errores
 *
 * \param personas ArrayPersona*
 * \param option int
 * \return int
 *
 */
int arrayPersona_showResp(ArrayPersona * personas, int option){
	int resp = 1;

	ArrayPersona personasAux = *personas;
	switch(option){
        case PERSONA_RAND:
			arrayPersona_randomInit(&personasAux);
            break;
        case PERSONA_SHOWL:
			resp = arrayPersona_showList(personasAux);
            break;
        case PERSONA_SHOWGR:
			resp = arrayPersona_showGraph(personasAux);
            break;
        case PERSONA_ADD:
            resp = arrayPersona_add(&personasAux);
            break;
        case PERSONA_DEL:
            resp = arrayPersona_del(&personasAux);
            break;
        case PERSONA_EDIT:
            resp = arrayPersona_edit(&personasAux);
            break;
		default:
			return FAIL_1;
	}
	*personas = personasAux;
	showMsg(option, resp);
	return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra las opciones que se pueden realizar sobre un ArrayPersona
 *
 * \param void
 * \return void
 *
 */
void arrayPersona_showOptions(void){
    tab(TABSIZE);
    printf("%d : CARGAR ALEATOREAMENTE %s \n", PERSONA_RAND, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : AGREGAR %s \n", PERSONA_ADD, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : BORRAR %s \n", PERSONA_DEL, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : EDITAR %s \n", PERSONA_EDIT, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR LISTA DE  %s \n", PERSONA_SHOWL, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR GRAFICO DE EDAD DE %s \n", PERSONA_SHOWGR, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("%d : VOLVER \n", PERSONA_RETURN);
    tab(TABSIZE);
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una persona parametrizada dentro del campo listaPersonas del ArrayPersona
 *
 * \param personas ArrayPersona
 * \param id int
 * \return int
 *
 */
int arrayPersona_getIndexOfID(ArrayPersona personas, int id){
    int i;
    for(i = 0; i < personas.length; i++){
        if(!personas.listPersonas[i].isEmpty && personas.listPersonas[i].id == id)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una personas parametrizada dentro del campo listaPersonas del ArrayProducto
 *
 * \param personas ArrayProducto
 * \param id int
 * \return int
 *
 */
int arrayPersona_getLastID(ArrayPersona personas){
    int i;
    int idMax = 0;
    for(i = 0; i < personas.length; i++){
        if(!personas.listPersonas[i].isEmpty && personas.listPersonas[i].id > idMax)
            idMax = personas.listPersonas[i].id;
    }
    return idMax;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Devuelve el primer indice que este disponible para cargar personas.
 *
 * \param personas ArrayPersona
 * \return int
 *
 */
static int firstIndexAvailable(ArrayPersona personas){
    int i;
    for(i = 0; i < personas.length; i++){
        if(personas.listPersonas[i].isEmpty)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Ordena el campo listaPersonas por el nombre de cada elemento, del ArrayPersona paramtrizado
 *
 * \param personas ArrayPersona*
 * \return int
 *
 */
static int sortArray(ArrayPersona * personas){
	ArrayPersona personasAux = *personas;
    int flagSwap;
    int i;
    if(personasAux.length < 1)
        return FAIL_1;
    do{
        flagSwap = FALSE;
        for(i=0; i < personasAux.length-1; i++) {
            if(strcmp(personasAux.listPersonas[i].name, personasAux.listPersonas[i+1].name) > 0){
                persona_swap(&personasAux.listPersonas[i], &personasAux.listPersonas[i+1]);
                flagSwap = TRUE;
            }
        }
    }while(flagSwap);
    *personas = personasAux;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Devuelve un vector de tres posiciones con la cantidad de ocurrencias de un rango de edad.
 *
 * \param personas ArrayPersona
 * \return int*
 *
 */
static int * getAges(ArrayPersona personas){
    int i;
    int contador[] = {0, 0, 0};
    for(i = 0; i < personas.length; i++){
        if(!personas.listPersonas[i].isEmpty){
            if(personas.listPersonas[i].edad < 18 )
                contador[0]++;
            else if(personas.listPersonas[i].edad > 17 && personas.listPersonas[i].edad < 36)
                contador[1]++;
            else if(personas.listPersonas[i].edad > 35)
                contador[2]++;
        }
    }
    return contador;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra el mensaje que haya respondido la funcion pedida.
 *
 * \param option int
 * \param resp int
 * \return int
 *
 */
static int showMsg(int option, int resp){
	switch(resp){
		case SUCCESS:
				if(option == PERSONA_SHOWL)
					printf(PERSONA_SHWLMSGOK);
				else if(option == PERSONA_ADD)
					printf(PERSONA_ADDMSGOK);
				else if(option == PERSONA_DEL)
					printf(PERSONA_DELMSGOK);
				else if(option == PERSONA_EDIT)
					printf(PERSONA_EDITMSGOK);
				else if(option == PERSONA_SHOWGR)
					printf(PERSONA_SHWGRMSGOK);
				else
					return FAIL_1;
				break;
		case FAIL_1:
				if(option == PERSONA_SHOWL || option == PERSONA_DEL ||option == PERSONA_EDIT || option == PERSONA_SHOWGR)
					printf(PERSONA_SHWLMSGF1);
				else if(option == PERSONA_ADD)
					printf(PERSONA_ADDMSGF1, PERSONA_DEL);
				else
					return FAIL_1;
				break;
		case FAIL_2:
				if(option == PERSONA_DEL || option == PERSONA_EDIT)
					printf(PERSONA_EDITDELMSGF1, PERSONA_ADD);
				else
					return FAIL_1;
				break;
		case FAIL_3:
				if(option == PERSONA_DEL || option == PERSONA_EDIT || option == PERSONA_ADD)
					printf(PERSONA_GENERICMSGFAIL);
				else
					return FAIL_1;
				break;
		default:
				return FAIL_1;
				break;
	}
	return SUCCESS;
}
