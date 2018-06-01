#include "pelicula.h"

/* ------------------------------------------------------------------ */
/**                     HEADER                                        */
/* ------------------------------------------------------------------ */
static int nextId();
/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Reserva un espacio en memoria para Pelicula
 *
 * \param void
 * \return Pelicula*
 */
Pelicula* pelicula_new(void){
    Pelicula* pPelicula = (Pelicula*) malloc(sizeof(Pelicula));
    return pPelicula;
}
/** \brief Inicializa un id negativo y el campo isEmpty en true de la Pelicula parametrizada.
 *
 * \param pelicula Pelicula*
 * \return void
 *
 */
void pelicula_init(Pelicula * pelicula){
    pelicula->id = -1;
    pelicula->isEmpty = TRUE;
}
/* ------------------------------------------------------------------ */
/** \brief Inicializa con datos aleatorios a la Pelicula paramerizada.
 *
 * \param pelicula Pelicula*
 * \return void
 *
 */
void pelicula_randomInit(Pelicula * pelicula){
    pelicula_setId(pelicula, nextId());
    pelicula_setDuration(pelicula, PELICULA_DUR_MIN + rand() % (PELICULA_DUR_MAX - PELICULA_DUR_MIN));
    pelicula_setGender(pelicula, util_getWord(5));
    pelicula_setTitle(pelicula, util_getWord(13));
    pelicula_setDescription(pelicula, util_getWord(80));
    pelicula_setLink(pelicula, util_getWord(33));
    pelicula->isEmpty = FALSE;
}
/* ------------------------------------------------------------------ */
/** \brief
 *
 * \param pelicula Pelicula*
 * \param title char*
 * \param gender char*
 * \param desc char*
 * \param duration char*
 * \param link char*
 * \return int
 *
 */
int pelicula_forcedInit(Pelicula * pelicula, char *title, char *gender, char *desc, char *duration, char *link){
    if(pelicula_setDuration(pelicula, atoi(duration)) == SUCCESS &&  pelicula_setGender(pelicula, gender) == SUCCESS &&
       pelicula_setTitle(pelicula, title) == SUCCESS && pelicula_setDescription(pelicula, desc) == SUCCESS &&
       pelicula_setLink(pelicula, link) == SUCCESS){
           pelicula->isEmpty = FALSE;
           pelicula_setId(pelicula, nextId());
           return SUCCESS;
    }
    return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Pelicula.
 *
 * \param pelicula Pelicula*
 * \param addMode int
 * \return int
 *
 */
int pelicula_constructor(Pelicula * pelicula, int addMode){
    int ret = SUCCESS;
    char buffer[DESC_LENGTH];
    showSeparator(6);
    showSeparator(4);
    ret = util_getString(&buffer, "Ingrese titulo: ", NAME_LENGTH);

    if(ret == SUCCESS){
        pelicula_setTitle(pelicula, buffer);
        ret = util_getString(&buffer, "Ingrese genero: ", NAME_LENGTH);
    }
    if(ret == SUCCESS){
        pelicula_setGender(pelicula, buffer);
        ret = util_getString(&buffer, "Ingrese duracion en minutos: ", 4);
    }
    if(ret == SUCCESS){
        pelicula_setDuration(pelicula, atoi(buffer));
        ret = util_getString(&buffer, "Ingrese descripcion: ", DESC_LENGTH);
    }
    if(ret == SUCCESS){
        pelicula_setDescription(pelicula, buffer);
        ret = util_getString(&buffer, "Ingrese link: ", DESC_LENGTH);
    }
    if(ret == SUCCESS){
        pelicula_setLink(pelicula, buffer);
        pelicula->isEmpty = FALSE;
    }
    showSeparator(4);
    showSeparator(6);

    if(ret == SUCCESS && addMode)
		ret = pelicula_setId(pelicula, nextId());
    return ret;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una pelicula parametrizada.
 *
 * \param pelicula Pelicula
 * \return void
 *
 */
void pelicula_showData(Pelicula pelicula){
    showSeparator(4);
    printf("ID #%d \n\t", pelicula_getId(pelicula));
    printf("Titulo: %s\n\t", pelicula_getTitle(pelicula));
    printf("Descripcion: %s\n\t", pelicula_getDescription(pelicula));
    printf("Genero: %s\n\t", pelicula_getGender(pelicula));
    printf("Duracion: %d minutos\n\t", pelicula_getDuration(pelicula));
    printf("Calificacion: %d estrellas\n\t", pelicula_getStars(pelicula));
    printf("Link: %s \n", pelicula_getLink(pelicula));
}
/* ------------------------------------------------------------------ */
/** \brief Swapea el valor de dos Pelicula.
 *
 * \param stP Pelicula*
 * \param ndP Pelicula*
 * \return int
 *
 */
int pelicula_swap(Pelicula * stP, Pelicula * ndP){
    Pelicula auxiliar;
    auxiliar = *stP;
    *stP = *ndP;
    *ndP = auxiliar;
    return SUCCESS;
}
/* ------------------------------------------------------------------ */
/**                     GETTERS Y SETTERS                             */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/** \brief Le asigna un id a un Pelicula
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_setId(Pelicula * this, int id){
    if(this != NULL && id > -1){
		this->id = id;
		return SUCCESS;
	}
	return FAIL_1;
}
/** \brief Obtener el ID de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_getId(Pelicula this){
    if(!this.isEmpty)
		return this.id;

	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna una duracion a un Pelicula
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_setDuration(Pelicula * this, int duration){
    if(duration > PELICULA_DUR_MIN && duration < PELICULA_DUR_MAX ){
		this->duration = duration;
		return SUCCESS;
	}
	return FAIL_1;
}
/** \brief Obtener la duracion de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_getDuration(Pelicula this){
    if(!this.isEmpty)
		return this.duration;

	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna una duracion a un Pelicula
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_setStars(Pelicula * this, int stars){
    if(stars > PELICULA_STARS_MIN && stars < PELICULA_STARS_MAX ){
		this->stars = stars;
		return SUCCESS;
	}
	return FAIL_1;
}
/** \brief Obtener la duracion de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
int pelicula_getStars(Pelicula this){
    if(!this.isEmpty)
		return this.stars;

	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna un nombre a un Pelicula
 *
 * \param this Pelicula*
 * \param name char*
 * \return int
 *
 */
int pelicula_setTitle(Pelicula * this, char * title){
    if(this != NULL && title != NULL)
        strcpy(this->title, title);
	return SUCCESS;
}
/** \brief Obtener el nombre de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
char * pelicula_getTitle(Pelicula this){
    if(!this.isEmpty)
		return this.title;
	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna un apellido a un Pelicula
 *
 * \param this Pelicula*
 * \param name char*
 * \return int
 *
 */
int pelicula_setGender(Pelicula * this, char * gender){
    if(this != NULL && gender != NULL)
        strcpy(this->gender, gender);
	return SUCCESS;
}
/** \brief Obtener el apellido de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
char * pelicula_getGender(Pelicula this){
    if(!this.isEmpty)
		return this.gender;

	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna un apellido a un Pelicula
 *
 * \param this Pelicula*
 * \param name char*
 * \return int
 *
 */
int pelicula_setDescription(Pelicula * this, char * description){
    if(this != NULL && description != NULL)
        strcpy(this->description, description);
	return SUCCESS;
}
/** \brief Obtener el apellido de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
char * pelicula_getDescription(Pelicula this){
    if(!this.isEmpty)
		return this.description;
	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna un link a un Pelicula
 *
 * \param this Pelicula*
 * \param name char*
 * \return int
 *
 */
int pelicula_setLink(Pelicula * this, char * link){
    if(this != NULL && link != NULL)
        strcpy(this->link, link);
	return SUCCESS;
}
/** \brief Obtener el link de un pelicula si esta activo
 *
 * \param this Pelicula*
 * \param int id
 * \return int
 *
 */
char * pelicula_getLink(Pelicula this){
    if(!this.isEmpty)
		return this.link;

	return FAIL_1;
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
