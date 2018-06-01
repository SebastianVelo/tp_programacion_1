#include "arrayPelicula.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int firstIndexAvailable(ArrayPelicula peliculas);
static int sortArray(ArrayPelicula * peliculas);
static int showMsg(int option, int resp);
static int askId(ArrayPelicula * peliculas);

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */

/** \brief Inicializa en vacio el campo listaPeliculas del ArrayPeliculas parametrizado.
 *
 * \param peliculas ArrayPelicula*
 * \return void
 *
 */
void arrayPelicula_init(ArrayPelicula * peliculas, int length){
    peliculas->length = length;
    peliculas->listPeliculas = malloc ( length*sizeof(Pelicula));
    int i;
    for(i = 0; i < peliculas->length; i++)
        pelicula_init(&peliculas->listPeliculas[i]);
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera aleatoria el campo listaPeliculas del ArrayPelicula parametrizado
 *
 * \param peliculas ArrayPelicula*
 * \return void
 *
 */
void arrayPelicula_randomInit(ArrayPelicula * peliculas){
    int i;
    for(i = 0; i < peliculas->length; i++)
        pelicula_randomInit(&peliculas->listPeliculas[i]);
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa de manera forzada el campo listaPeliculas del ArrayPelicula parametrizado
 *
 * \param peliculas ArrayPelicula*
 * \return void
 *
 */
void arrayPelicula_forcedInit(FILE * csv, ArrayPelicula * peliculas){
    int retorno = -1;
    int i;
    char buffTitle[4096];
    char buffDesc[4096];
    char buffGender[4096];
    char buffLink[4096];
    char buffDuration[4096];
    if(csv != NULL){
        retorno = 0;
        fscanf(csv,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",buffTitle, buffGender, buffDesc, buffDuration, buffLink);
        for(i = 0; !feof(csv); i++){
            fscanf(csv,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", buffTitle, buffGender, buffDesc, buffDuration, buffLink);
            pelicula_forcedInit(&peliculas->listPeliculas[i], buffTitle, buffGender, buffDesc, buffDuration, buffLink);
        }
    }
    return retorno;
}
/* ------------------------------------------------------------------ */
/** \brief Agrega una pelicula al campo listaPeliculas del ArrayPelicula parametrizado.
 *
 * \param peliculas ArrayPelicula*
 * \return int
 *
 */
int arrayPelicula_add(ArrayPelicula * peliculas){
    int index = firstIndexAvailable(*peliculas);
    if(index == FAIL_1)
        return FAIL_1;
    if(pelicula_constructor(&peliculas->listPeliculas[index], TRUE) == FAIL_1)
        return FAIL_3;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y borra una pelicula del campo listaPeliculas del ArrayPelicula parametrizado.
 *
 * \param peliculas ArrayPelicula*
 * \return int
 *
 */
int arrayPelicula_del(ArrayPelicula * peliculas){
    int index = askId(peliculas);
    if(peliculas->listPeliculas[index].isEmpty)
        return FAIL_2;
    pelicula_init(&peliculas->listPeliculas[index]);
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Pide un ID y edita los campos de esa pelicula que este en listaPeliculas del ArrayPelicula parametrizado.
 *
 * \param peliculas ArrayPelicula*
 * \return int
 *
 */
int arrayPelicula_edit(ArrayPelicula * peliculas){
    int index = askId(peliculas);
    if(peliculas->listPeliculas[index].isEmpty)
        return FAIL_2;
    if(pelicula_constructor(&peliculas->listPeliculas[index], FALSE) == FAIL_1)
        return FAIL_3;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las peliculas que esten activas en el listaPeliculas del ArrayPeliculas parametrizado.
 *
 * \param peliculas ArrayPelicula
 * \return int
 *
 */
int arrayPelicula_showList(ArrayPelicula peliculas){
    int ret = FAIL_1;
    int i;
    sortArray(&peliculas);
    showSeparator(4);
    printf("%s\n", PELICULA_ENTITY);
    for(i = 0; i < peliculas.length; i++){
        if(!peliculas.listPeliculas[i].isEmpty){
            pelicula_showData(peliculas.listPeliculas[i]);
            ret = SUCCESS;
        }
    }
    showSeparator(4);
    return ret;
}/* ------------------------------------------------------------------ */
/** \brief Muestra los datos de todas las peliculas que esten activas en el listaPeliculas del ArrayPeliculas parametrizado.
 *
 * \param peliculas ArrayPelicula
 * \return int
 *
 */
int arrayPelicula_showHtml(ArrayPelicula peliculas){
    FILE *htmlNuevo = fopen ("html/index.html", "w+");
    FILE *templateList = fopen ("html/template.txt", "r");
    FILE *templateHeader = fopen ("html/header.txt", "r");
    FILE *templateFoooter = fopen ("html/footer.txt", "r");
    char tempTxt[800];
    int ret = FAIL_1;
    int i;
    sortArray(&peliculas);
    strcpy(tempTxt, "");

    /** ESCRIBO EL HEADER.TXT EN EL INDEX.HTML */
    for(i = 0; !feof(templateHeader); i++)
      fprintf(htmlNuevo, "%c", fgetc(templateHeader));

    /** GUARDO EL TEMPLATE.TXT EN UNA VARIABLE */
    for(i = 0; !feof(templateList); i++)
      tempTxt[i] = fgetc(templateList);
    /** ESCRIBO CADA PELICULA ACTIVA EN EL INDEX.HTML CON EL TEMPLATE.TXT, REEMPLAZANDO LOS MACROS */
    for(i = 0; i < peliculas.length; i++){
        if(!peliculas.listPeliculas[i].isEmpty){
            char auxTemp[2000];
            char durBuff[10];
            itoa(peliculas.listPeliculas[i].duration, durBuff, 10);
            strcpy(auxTemp, tempTxt);
            strcpy(auxTemp, str_replace(auxTemp, "GENDER", peliculas.listPeliculas[i].gender));
            strcpy(auxTemp, str_replace(auxTemp, "DESCRIPTION", peliculas.listPeliculas[i].description));
            strcpy(auxTemp, str_replace(auxTemp, "URL", peliculas.listPeliculas[i].link));
            strcpy(auxTemp, str_replace(auxTemp, "TITLE", peliculas.listPeliculas[i].title));
            strcpy(auxTemp, str_replace(auxTemp, "DURATION", durBuff));
            fprintf(htmlNuevo, auxTemp);
            //fwrite(auxTemp, 1, sizeof(auxTemp), htmlNuevo);
            ret = SUCCESS;
        }
    }

   /** ESCRIBO EL FOOTER.TXT EN EL INDEX.HTML */
   for(i = 0; !feof(templateFoooter); i++)
      fprintf(htmlNuevo, "%c", fgetc(templateFoooter));

   fclose(htmlNuevo);
   fclose(templateList);
   fclose(templateHeader);
   fclose(templateFoooter);
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Pide una opcion por parametro y ejecuta esa accion, obteniendo la respuesta de cada uno y sus posibles errores
 *
 * \param peliculas ArrayPelicula*
 * \param option int
 * \return int
 *
 */
int arrayPelicula_showResp(ArrayPelicula * peliculas, int option){
	int resp = 1;
	switch(option){
        case PELICULA_RAND:
			arrayPelicula_randomInit(peliculas);
            break;
        case PELICULA_SHOWL:
			resp = arrayPelicula_showHtml(*peliculas);
            break;
        case PELICULA_ADD:
            resp = arrayPelicula_add(peliculas);
            break;
        case PELICULA_DEL:
            resp = arrayPelicula_del(peliculas);
            break;
        case PELICULA_EDIT:
            resp = arrayPelicula_edit(peliculas);
            break;
		default:
			return FAIL_1;
	}
	showMsg(option, resp);
	return SUCCESS;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra las opciones que se pueden realizar sobre un ArrayPelicula
 *
 * \param void
 * \return void
 *
 */
void arrayPelicula_showOptions(void){
    tab(TABSIZE);
    printf("%d : CARGAR ALEATOREAMENTE %s \n", PELICULA_RAND, PELICULA_ENTITY);
    tab(TABSIZE);
    printf("%d : AGREGAR %s \n", PELICULA_ADD, PELICULA_ENTITY);
    tab(TABSIZE);
    printf("%d : BORRAR %s \n", PELICULA_DEL, PELICULA_ENTITY);
    tab(TABSIZE);
    printf("%d : EDITAR %s \n", PELICULA_EDIT, PELICULA_ENTITY);
    tab(TABSIZE);
    printf("%d : MOSTRAR HTML DE  %s \n", PELICULA_SHOWL, PELICULA_ENTITY);
    tab(TABSIZE);
    printf("%d : VOLVER \n", PELICULA_RETURN);
    tab(TABSIZE);
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una pelicula parametrizada dentro del campo listaPeliculas del ArrayPelicula
 *
 * \param peliculas ArrayPelicula
 * \param id int
 * \return int
 *
 */
int arrayPelicula_getIndexOfID(ArrayPelicula peliculas, int id){
    int i;
    for(i = 0; i < peliculas.length; i++){
        if(!peliculas.listPeliculas[i].isEmpty && peliculas.listPeliculas[i].id == id)
            return i;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Se obtiene la posicion de una peliculas parametrizada dentro del campo listaPeliculas del ArrayProducto
 *
 * \param peliculas ArrayProducto
 * \param id int
 * \return int
 *
 */
int arrayPelicula_getLastID(ArrayPelicula peliculas){
    int i;
    int idMax = 0;
    for(i = 0; i < peliculas.length; i++){
        if(!peliculas.listPeliculas[i].isEmpty && peliculas.listPeliculas[i].id > idMax)
            idMax = peliculas.listPeliculas[i].id;
    }
    return idMax;
}
/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Devuelve el primer indice que este disponible para cargar peliculas.
 *
 * \param peliculas ArrayPelicula
 * \return int
 *
 */
static int firstIndexAvailable(ArrayPelicula peliculas){
    int i;
    for(i = 0; i < peliculas.length; i++){
        if(peliculas.listPeliculas[i].isEmpty)
            return i;
    }
    return FAIL_1;
}
/** \brief Pide el indice y devuelve el id
 *
 */
static int askId(ArrayPelicula * peliculas){
    int id;
    if(arrayPelicula_showList(*peliculas) == FAIL_1)
        return FAIL_1;
    if(util_getInt(&id, PELICULA_ASKID, PELICULA_ASKIDFAIL, 0, &peliculas->length, 3) == FAIL_1)
        return FAIL_3;
    return arrayPelicula_getIndexOfID(*peliculas, id);
}
/* ------------------------------------------------------------------ */
/** \brief Ordena el campo listaPeliculas por el nombre de cada elemento, del ArrayPelicula paramtrizado
 *
 * \param peliculas ArrayPelicula*
 * \return int
 *
 */
static int sortArray(ArrayPelicula * peliculas){
    int flagSwap;
    int i;
    if(peliculas->length < 1)
        return FAIL_1;
    do{
        flagSwap = FALSE;
        for(i = 0; i < peliculas->length-1; i++) {
            if(strcmp(peliculas->listPeliculas[i].title, peliculas->listPeliculas[i+1].title) > 0){
                pelicula_swap(&peliculas->listPeliculas[i], &peliculas->listPeliculas[i+1]);
                flagSwap = TRUE;
            }
        }
    }while(flagSwap);
    return SUCCESS;
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
				if(option == PELICULA_SHOWL)
					printf(PELICULA_SHWLMSGOK);
				else if(option == PELICULA_ADD)
					printf(PELICULA_ADDMSGOK);
				else if(option == PELICULA_DEL)
					printf(PELICULA_DELMSGOK);
				else if(option == PELICULA_EDIT)
					printf(PELICULA_EDITMSGOK);
				else
					return FAIL_1;
				break;
		case FAIL_1:
				if(option == PELICULA_SHOWL || option == PELICULA_DEL ||option == PELICULA_EDIT)
					printf(PELICULA_SHWLMSGF1);
				else if(option == PELICULA_ADD)
					printf(PELICULA_ADDMSGF1, PELICULA_DEL);
				else
					return FAIL_1;
				break;
		case FAIL_2:
				if(option == PELICULA_DEL || option == PELICULA_EDIT)
					printf(PELICULA_EDITDELMSGF1, PELICULA_ADD);
				else
					return FAIL_1;
				break;
		case FAIL_3:
				if(option == PELICULA_DEL || option == PELICULA_EDIT || option == PELICULA_ADD)
					printf(PELICULA_GENERICMSGFAIL);
				else
					return FAIL_1;
				break;
		default:
				return FAIL_1;
				break;
	}
	return SUCCESS;
}
