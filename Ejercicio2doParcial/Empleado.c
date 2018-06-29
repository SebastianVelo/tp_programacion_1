#include "empleado.h"

/* ------------------------------------------------------------------ */
/**                     PUBLICAS                                      */
/* ------------------------------------------------------------------ */
/** \brief Reserva un espacio en memoria para Empleado
 *
 * \param void
 * \return Empleado*
 */
Empleado* empleado_new(void){
    Empleado* pEmpleado = (Empleado*) malloc(sizeof(Empleado));
    return pEmpleado;
}
/* ------------------------------------------------------------------ */
/** \brief
 *
 * \param empleado Empleado*
 * \param ATR_3 char*
 * \param nombre char*
 * \param id char*
 * \param ATR_2 char*
 * \return int
 *
 */
Empleado* empleado_newForced(char *nombre, char *id, char *horasTrabajadas){
	Empleado* empleado = empleado_new();
    if(empleado_setid(empleado, atoi(id)) == SUCCESS && empleado_sethorasTrabajadas(empleado, atoi(horasTrabajadas)) == SUCCESS &&
	empleado_setnombre(empleado, nombre) == SUCCESS){
           return empleado;
    }
	free(empleado);
    return NULL;
}
/* ------------------------------------------------------------------ */
/** \brief
 *
 * \param empleado Empleado*
 * \param ATR_3 char*
 * \param nombre char*
 * \param id char*
 * \param ATR_2 char*
 * \return int
 *
 */
void empleados_newCVS(ArrayList* empleados, FILE * csv){
    char buffnombre[200];
    char buffid[200];
    char buffhorasTrabajadas[200];
    if(csv != NULL){
        fscanf(csv,"%[^,],%[^,],%[^\n]\n", buffid, buffnombre, buffhorasTrabajadas);
		int i;
        for(i = 0; !feof(csv); i++){
			fscanf(csv,"%[^,],%[^,],%[^\n]\n", buffid, buffnombre, buffhorasTrabajadas);
			al_add(empleados, empleado_newForced(buffnombre, buffid, buffhorasTrabajadas));
        }
    }
}
/* ------------------------------------------------------------------ */
/** \brief Pide al usuario los campos de una Empleado.
 *
 * \param empleado Empleado*
 * \param addMode int
 * \return int
 *
 */
Empleado* empleado_newPrompt(){
    int ret = SUCCESS;
    char nombre[LENGTH];
    char id[LENGTH];
    char horasTrabajadas[LENGTH];
	int i = 0;
    showSeparator(6);
    showSeparator(4);
    ret = util_getString(&nombre, "Ingrese nombre: ", LENGTH);
	i++;
    if(ret == SUCCESS){
		ret = util_getString(&id, "Ingrese id: ", LENGTH);
		i++;
    }
    if(ret == SUCCESS){
		ret = util_getString(&horasTrabajadas, "Ingrese horasTrabajadas: ", LENGTH);
    }
    showSeparator(4);
    showSeparator(6);
    if(ret == SUCCESS)
		return empleado_newForced(nombre, id, horasTrabajadas);
    return NULL;
}
/* ------------------------------------------------------------------ */
/** \brief Muestra los campos de una empleado parametrizada.
 *
 * \param empleado Empleado
 * \return void
 *
 */
void empleado_showData(Empleado* empleado){
    showSeparator(4);
    printf("nombre: %s\n\t", empleado_getnombre(empleado));
    printf("id: %d\n\t", empleado_getid(empleado));
    printf("horasTrabajadas: %d\n\t", empleado_gethorasTrabajadas(empleado));
}
/* ------------------------------------------------------------------ */
/** \brief Devuelve si el empleado trabajo menos de 120 horas.
 *
 * \param empleado Empleado
 * \return void
 *
 */
 int em_trabajaMasDe120Horas(Empleado* i){
    if(i != NULL && empleado_gethorasTrabajadas(i) > 120)
        return 1;
    else
        return 0;
 }
/* ------------------------------------------------------------------ */
/**                     GETTERS Y SETTERS                             */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/* ------------------------------------------------------------------ */
/** \brief Le asigna una duracion a un Empleado
 *
 * \param this Empleado*
 * \param int id
 * \return int
 *
 */
int empleado_setid(Empleado * this, int id){
    if(id > id_MIN  && id < id_MAX ){
		this->id = id;
		return SUCCESS;
	}
	return FAIL_1;
}
/** \brief Obtener la duracion de un empleado si esta activo
 *
 * \param this Empleado*
 * \param int id
 * \return int
 *
 */
int empleado_getid(Empleado* this){
    if(this != NULL)
		return this->id;
	return FAIL_1;
}
/** \brief Le asigna una duracion a un Empleado
 *
 * \param this Empleado*
 * \param int id
 * \return int
 *
 */
int empleado_sethorasTrabajadas(Empleado * this, int horasTrabajadas){
    if(horasTrabajadas > horasTrabajadas_MIN  && horasTrabajadas < horasTrabajadas_MAX ){
		this->horasTrabajadas = horasTrabajadas;
		return SUCCESS;
	}
	return FAIL_1;
}
/** \brief Obtener la duracion de un empleado si esta activo
 *
 * \param this Empleado*
 * \param int id
 * \return int
 *
 */
int empleado_gethorasTrabajadas(Empleado* this){
    if(this != NULL)
		return this->horasTrabajadas;
	return FAIL_1;
}
/* ------------------------------------------------------------------ */
/** \brief Le asigna un apellido a un Empleado
 *
 * \param this Empleado*
 * \param name char*
 * \return int
 *
 */
int empleado_setnombre(Empleado * this, char * nombre){
    if(this != NULL && nombre != NULL)
        strcpy(this->nombre, nombre);
	return SUCCESS;
}
/** \brief Obtener el apellido de un empleado si esta activo
 *
 * \param this Empleado*
 * \param int id
 * \return int
 *
 */
char * empleado_getnombre(Empleado* this){
    if(this != NULL)
		return this->nombre;
	return FAIL_1;
}
