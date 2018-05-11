#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "styles.h"
#include "arrayPersona.h"


/* ------------------------------------------------------------------ */
/**                     CONST                                         */
/* ------------------------------------------------------------------ */
#define EXIT 1

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static void showEntities(void);
static int showOptions(int entity);

/* ------------------------------------------------------------------ */
/**                     MAIN                                          */
/* ------------------------------------------------------------------ */
int main()
{
    int seguir = TRUE;
    int option = -1;
	int entity = -1;
	ArrayPersona personas;
	arrayPersona_init(&personas);

    while(seguir == TRUE){
        fflush(stdin);
		showEntities();
		if(util_getInt(&entity, "Ingrese que desea modificar: ", "Ingrese una opcion valida. \n", 0, EXIT, 1) == FAIL_1)
            continue;

		if(entity == EXIT){
			seguir = FALSE;
			break;
		}

		int volver = showOptions(entity);
		if(util_getInt(&option, "Ingrese la opcion a realizar: ", "Ingrese una opcion valida. \n", 0, volver, 1) == FAIL_1)
            continue;

		if(option == volver)
            continue;

		switch(entity){
			case PERSONA_ID:
                    arrayPersona_showResp(&personas, option);
					break;
		}
        printf("\n");
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/**                     PRIVADAS                                      */
/* ------------------------------------------------------------------ */
static void showEntities(void){
    showHeader(6);
    tab(TABSIZE);
    printf("#%d: %s \n", PERSONA_ID, PERSONA_ENTITY);
    tab(TABSIZE);
    printf("#%d: SALIR \n", EXIT);
    tab(TABSIZE);
}

static int showOptions(int entity){
    switch(entity){
		case PERSONA_ID:
				   arrayPersona_showOptions();
				   return PERSONA_RETURN;
				   break;

	}
	return FAIL_1;
}
